#include <algorithm>
#include <fcntl.h>

#include "executor.h"

void Executor::execute_command(const std::vector<std::string>& tokens) {
    childPids_.clear();
    
    auto pipePos = std::find(tokens.begin(), tokens.end(), "|");

    if (pipePos == tokens.end()) { // No pipe - simple command
        int pid = execute_simple_command(tokens, input_, out_, error_);

        if (!background_) {
            waitpid(pid, &status_, 0);
        }
        else {
            std::cout << "Process work, PID: " << pid << '\n';
            backgroundPids_.push_back(pid);
        }
    }
    else { // Yes pipe - separating commands
        std::vector<std::string> cmdLeft(tokens.begin(), pipePos);
        std::vector<std::string> cmdRight(pipePos + 1, tokens.end());

        execute_pipeline_command(cmdLeft, cmdRight);

        if (!background_) {
            for (pid_t pid : childPids_) {
                waitpid(pid, &status_, 0);
            }
        }
        else {
            for (pid_t pid : childPids_) {
                std::cout << "Background process started, PID: " << pid << '\n';
                backgroundPids_.push_back(pid);
            }
        }
    }

    // Reset redirection state for each new command
    inputFile_.clear();
    outputFile_.clear();
    errorFile_.clear();
    appendOutput_ = false;
    background_ = false;
}

pid_t Executor::execute_simple_command(const std::vector<std::string>& tokens, int inputfd, int outfd, int errorfd) {
    if (tokens.empty()) return -1;

    // converting vector to a array char*
    std::vector<char*> args{};
    for (const auto& token : tokens) {
        args.push_back(const_cast<char*>(token.c_str()));
    }
    args.push_back(nullptr); // end array the null

    pid_t pid = fork(); // create process
    childPids_.push_back(pid);
    if (pid == -1) { // error fork()
        perror("fork failed");
        return -1;
    }
    else if (pid == 0) { // child process
        if (!inputFile_.empty()) { // >
            int fd = open(inputFile_.c_str(), O_RDONLY);

            if (fd < 0) {
                perror("open input file");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (inputfd != STDIN_FILENO) {
            dup2(inputfd, STDIN_FILENO);
            close(inputfd);
        }

        if (!outputFile_.empty()) { // <
            int flags = O_WRONLY | O_CREAT;
            flags |= appendOutput_ ? O_APPEND : O_TRUNC;

            int fd = open(outputFile_.c_str(), flags, 0644);

            if (fd < 0) {
                perror("open output file");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (outfd != STDOUT_FILENO) {
            dup2(outfd, STDOUT_FILENO);
            close(outfd);
        }

        if (!errorFile_.empty()) { // 2>
            int fd = open(errorFile_.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd < 0) {
                perror("open error file");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDERR_FILENO);
            close(fd);
        }
        else if (errorfd != STDERR_FILENO) {
            dup2(errorfd, STDERR_FILENO);
            close(errorfd);
        }
        execvp(args[0], args.data());

        // if execvp return control, then an error has occurred
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    else { // parent process
        if (inputfd != STDIN_FILENO) close(inputfd);
        if (outfd != STDOUT_FILENO) close(outfd);
        if (errorfd != STDERR_FILENO) close(errorfd);

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
    pid_t leftPid = execute_simple_command(left, input_, pipefd[1], error_);
    if (leftPid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }
    close(pipefd[1]); // Close the unused end of the pipe for writing
    
    // Start the right command
    pid_t rightPid = execute_simple_command(right, pipefd[0], out_, error_);
    if (rightPid == -1) {
        close(pipefd[0]);
        return;
    }
    close(pipefd[0]);
}

void Executor::execute_background(const std::vector<std::string>& tokens) {
    background_ = true;
    execute_command(tokens);
    background_ = false;
}

void Executor::check_background_processes() {
    auto iter = backgroundPids_.begin();

    while (iter != backgroundPids_.end()) {
        pid_t result = waitpid(*iter, &status_, WNOHANG);

        if (result > 0) {
            std::cout << "Background process " << *iter << " finished\n";
            iter = backgroundPids_.erase(iter);
        } 
        else if (result == 0) {
            ++iter;
        } 
        else {
            perror("waitpid failed");
            iter = backgroundPids_.erase(iter);
        }
    }
}