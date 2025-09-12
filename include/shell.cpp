#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

#include "shell.h"
#include "parser.h"

Parser pars;

void Shell::REPL() {
    // Read-Eval-Print loop
    while (true) {
        // Print
        std::cout << "moser> " << std::flush;

        // Read
        if(!std::getline(std::cin, input)) {
            break; // If EOF (Ctrl + D)
        }

        // ---- Parsing ---- Reset parser state for new input
        pars.iss_.clear(); // Reset failes
        pars.iss_.str(input); // Set a new line to the stream
        pars.args_.clear(); // Clear old args

        while (pars.iss_ >> pars.arg_) {
            pars.args_.push_back(pars.arg_);
        }

        if(pars.args_.empty()) continue;

        // Execute (not yet separately)
        if(pars.args_[0] == "byemoser") {
            break;
        }
        else {
            // TODO: does not execute commands yet. Not fork/exec
            std::cout << "Command: " << pars.args_[0] << '\n';
            std::cout << "Args: ";
            for(size_t i = 0; i < pars.args_.size(); i++) {
                std::cout << pars.args_[i] << " ";
            }
            std::cout << '\n';
        }
    }
    return;
}
