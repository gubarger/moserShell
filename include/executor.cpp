#include <algorithm>
#include <fcntl.h>

#include "executor.h"

void Executor::execute_command(const std::vector<std::string>& tokens) {
    auto pipePos = std::find(tokens.begin(), tokens.end(), "|");

    if (pipePos == tokens.end()) { // No pipe - simple command
        execute_simple_command(tokens, input, out);
    }
    else { // Yes pipe - separating commands
        std::vector<std::string> cmdLeft(tokens.begin(), pipePos);
        std::vector<std::string> cmdRight(pipePos + 1, tokens.end());

        execute_pipeline_command(cmdLeft, cmdRight);
    }

    for (pid_t pid : childPids) { // Waiting the pids
        waitpid(pid, &status, 0);
    }
}

pid_t Executor::execute_simple_command(const std::vector<std::string>& tokens, int inputfd, int outfd) {
    if(tokens.empty()) return -1;

    // converting vector to a array char*
    std::vector<char*> args{};
    for (const auto& token : tokens) {
        args.push_back(const_cast<char*>(token.c_str()));
    }
    args.push_back(nullptr); // end array the null

    pid_t pid = fork(); // create process
    childPids.push_back(pid);
    if(pid == -1) { // error fork()
        perror("fork failed");
        return -1;
    }
    else if(pid == 0) { // child process
        if (inputfd != STDIN_FILENO) {
            dup2(inputfd, STDIN_FILENO);
            close(inputfd);
        }

        if (outfd != STDOUT_FILENO) {
            dup2(outfd, STDOUT_FILENO);
            close(outfd);
        }
        execvp(args[0], args.data());

        // if execvp return control, then an error has occurred
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    else { // parent process
        waitpid(pid, &status, 0);

        if(inputfd != STDIN_FILENO) close(inputfd);
        if(outfd != STDOUT_FILENO) close(outfd);

        return pid;
    }
}

void Executor::execute_pipeline_command(const std::vector<std::string>& left, const std::vector<std::string> right) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return;
    }

    // Start the left command
    pid_t leftPid = execute_simple_command(left, input, pipefd[1]);
    childPids.push_back(leftPid);
    if (leftPid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }
    
    close(pipefd[1]); // Close the unused end of the pipe for writing
    int saveSTDIN = input;
    input = pipefd[0];

    // Start the right command
    pid_t rightPid = execute_simple_command(right, input, out);
    childPids.push_back(rightPid);

    input = saveSTDIN; // Recover original input
    close(pipefd[0]);

    // Waiting for both commands to complete
    waitpid(leftPid, &status, 0);
    waitpid(rightPid, &status, 0);
}