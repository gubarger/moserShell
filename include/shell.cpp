#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <wordexp.h>

#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "history.h"

#include <readline/readline.h>
#include <readline/history.h>

Parser pars;
Executor exec;
History history;

void Shell::REPL() {
    chdir(getenv("HOME")); // Default start directory

    using_history();
    read_history(".moser_history");

    // Read-Eval-Print loop
    while (true) {
        // Print
        char* input = readline("moser> ");
        
        // Read
        if(!input) break; // If EOF (Ctrl + D)

        if(*input) {
            add_history(input);
            
            // Parsing
            std::vector<std::string> tokens = pars.tokenize(input);

            // Execute
            if(tokens[0] == "byemoser") break;
            else if(tokens[0] == "cd") { // Change directory
                if(tokens.size() < 2) std::cerr << "cd: missing argument" << '\n';
                else {
                    std::string path = tokens[1];
                    
                    // Expand tilde to home directory
                    if(path[0] == '~') {
                        wordexp_t exptresult{};

                        if(wordexp(path.c_str(), &exptresult, 0) == 0) {
                            path = exptresult.we_wordv[0];
                            wordfree(&exptresult);
                        }
                    }
                    
                    if (chdir(path.c_str()) != 0) perror("cd failed");
                }
                continue; // No move to fork/exec
            }

            // TODO: add command execution logic here
            exec.execute_command(tokens);
        }
        free(input);
    }
    write_history(".moser_history");
    return;
}
