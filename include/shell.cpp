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
            // TODO: add command execution logic here
            exec.execute_command(tokens);
        }
    }
    return;
}
