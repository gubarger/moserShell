#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

#include "shell.h"
#include "parser.h"
#include "executor.h"

Parser pars;
Executor exec;

void Shell::REPL() {
    // Read-Eval-Print loop
    while (true) {
        // Print
        std::cout << "moser> " << std::flush;

        // Read
        if(!std::getline(std::cin, input)) {
            break; // If EOF (Ctrl + D)
        }
        if(input.empty()) continue;

        // Parsing
        std::vector<std::string> tokens = pars.tokenize(input);

        // Execute
        if(tokens[0] == "byemoser") {
            break;
        }
        else {
            // std::cout << "tokens:\n";
            // for(const auto& token : tokens) {
            //     std::cout << "[" << token << "] ";
            // }
            // std::cout << "\n\n\n";

            // TODO: add command execution logic here
            exec.execute_command(tokens);
        }
    }
    return;
}
