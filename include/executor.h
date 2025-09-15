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

    // nullptr or (char*)nullptr will be specified at the end of all incoming arguments
    void execl   (const char* path, const char* arg0, const char* arg1, ...) {}
    void execlp  (const char* file, const char* arg0, const char* arg1, ...) {}
    void execle  (const char* path, const char* arg0, const char* arg1, ...) {}
    void execv   (const char* path, char* const argv[]) {}
    void execvp  (const char* file, char* const argv[]) {}
    void execvpe (const char* file, char* const argv[], char* const envp[])  {}

    void execute_command(const std::vector<std::string>& tokens); // base test func
};

#endif // INCLUDE_EXECUTOR_H_