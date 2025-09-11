#include <iostream>
#include <ostream>
#include <string>

#include "shell.h"

void Shell::REPL() {
    // Read-Eval-Print loop
    while (true) {
        // Print
        std::cout << "moser> " << std::flush;

        // Read
        if(!std::getline(std::cin, input)) {
            break; // If EOF (Ctrl + D)
        }

        // Execute (not yet separately)
        if(input == "byemoser") {
            break;
        }
        else {
            // TODO: does not execute commands yet
            std::cout << "You text: " << input << '\n';
        }
    }
    return;
}
