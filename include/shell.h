#ifndef INCLUDE_SHELL_H_
#define INCLUDE_SHELL_H_

#include <iostream>
#include <string.h>
#include <limits.h>

class Parser;
class Executor;
class History;

class Shell {
public:
    explicit Shell() noexcept = default;
    ~Shell() noexcept = default;

    /**
     * @brief main cycle of the program
     * 
     * @note Uses REPL - Read-Eval-Print Loop.
     * Enter a command, the program reads it 
     * and the command is executed
     *
     * @return none
     * 
     */
    void REPL(); // main work loop

    std::string getLinuxDistributionName();

private:
    char bufferCWD_[PATH_MAX];
    std::string stringCWD_{};
    const char* homeDir_ = getenv("HOME");
    std::string distName_ = getLinuxDistributionName();

    // Colors
    static constexpr const char* RESET_ = "\033[0m";
    static constexpr const char* CYAN_ = "\033[36m";
    static constexpr const char* GREEN_ = "\033[32m";
    static constexpr const char* RED_ = "\033[31m";
    static constexpr const char* YELLOW_ = "\033[33m";
    static constexpr const char* BLUE_ = "\033[34m";
};

#endif // INCLUDE_SHELL_H_
