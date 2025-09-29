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

    void set_input_redirection(const std::string& file) { inputFile_ = file; }
    void set_output_redirection(const std::string& file, bool append = false) { 
        outputFile_ = file; 
        appendOutput_ = append;
    }
    void set_error_redirection(const std::string& file) { errorFile_ = file; }

public:
    // for <, >, 2>, &, >>
    std::string inputFile_, outputFile_, errorFile_;
    bool appendOutput_ = false, background_ = false;

private:
    pid_t execute_simple_command(const std::vector<std::string>& tokens, int inputfd, int outfd, int errorfd);
    void execute_pipeline_command(const std::vector<std::string>& left, const std::vector<std::string> right);

private:
    int status_{};
    
    int input_ = STDIN_FILENO;
    int out_ = STDOUT_FILENO;
    int error_ = STDERR_FILENO;

    std::vector<pid_t> childPids_{};
    std::vector<std::string> args_{};
};

#endif // INCLUDE_EXECUTOR_H_