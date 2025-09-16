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
};

#endif // INCLUDE_EXECUTOR_H_