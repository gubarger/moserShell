#ifndef INCLUDE_EXECUTOR_H_
#define INCLUDE_EXECUTOR_H_

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

/** @brief Replacing the current process with a new image. It works after fork() */
class Executor {
public:
    /*---base family---*/
    void execute_command(const std::vector<std::string>& tokens); // base execute func

private:
    pid_t execute_simple_command(const std::vector<std::string>& tokens, int inputfd, int outfd);
    void execute_pipeline_command(const std::vector<std::string>& left, const std::vector<std::string> right);

private:
    int input = STDIN_FILENO;
    int out = STDOUT_FILENO;
};

#endif // INCLUDE_EXECUTOR_H_