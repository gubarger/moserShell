#ifndef INCLUDE_SHELL_H_
#define INCLUDE_SHELL_H_

#include <iostream>
#include <string.h>

class Shell {
public:
    explicit Shell() = default;
    ~Shell() noexcept = default;
    /**
     * @brief main cycle of the program
     * 
     * @note Uses REPL - Read-Eval-Print Loop.
     * Enter a command, the program reads it 
     * and the command is executed
     *
     * @return none
     * */
    void REPL(); // main work loop

private:
    std::string input{};
};

#endif // INCLUDE_SHELL_H_
