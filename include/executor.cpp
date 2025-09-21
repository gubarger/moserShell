#include "executor.h"

void Executor::execute_command(const std::vector<std::string>& tokens) {
    if(tokens.empty()) return;

    // converting vector to a array char*
    std::vector<char*> args{};
    for (const auto& token : tokens) {
        args.push_back(const_cast<char*>(token.c_str()));
    }
    args.push_back(nullptr); // end array the null

    pid_t pid = fork(); // create process
    if(pid == -1) { // error fork()
        perror("fork failed");
        return;
    }
    else if(pid == 0) { // child process
        execvp(args[0], args.data());

        // if execvp return control, then an error has occurred
        perror("execvp failed");
        exit(1);
    }
    else { // parent process
        int status{};
        
        waitpid(pid, &status, 0);
    }
}