#include <cstddef>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <wordexp.h>
#include <regex>

#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "history.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <absl/strings/str_cat.h>
#include <absl/strings/numbers.h>

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
        if (getcwd(bufferCWD_, sizeof(bufferCWD_)) != nullptr) {
            stringCWD_ = bufferCWD_;

            if (homeDir_ != nullptr) {
                std::string homeStr(homeDir_);

                if(stringCWD_.find(homeStr) == 0) {
                    stringCWD_.replace(0, homeStr.length(), "~");
                }
            }
        } 
        else {
            stringCWD_ = "Unknown";
        }

        // Read
        std::string promt = CYAN_ + distName_ + RESET_ + ":" + GREEN_ + stringCWD_ + RESET_ + ":" + BLUE_ + "moser> " + RESET_;
        char* input = readline(promt.c_str());

        if (!input) break; // If EOF (Ctrl + D)

        if (*input) {
            std::string processed_input = input; // Handle history expansion
            
            // Handle history expansion
            if (processed_input == "!!") { // last command exec
                auto command_last = history.last();
                if (!command_last.ok()) {
                    std::cerr << command_last.status().message() << '\n';
                    free(input);
                    continue;
                }

                processed_input = *command_last;
                std::cout << processed_input << '\n';
            }
            else if (processed_input.size() > 1 && processed_input[0] == '!' && std::isdigit(processed_input[1])) { // command n exec
                int n{};

                if (absl::SimpleAtoi(processed_input.substr(1), &n)) {
                    auto command_history = history.get(n);

                    if (!command_history.ok()) {
                        std::cerr << command_history.status().message() << '\n';
                        free(input);
                        continue;
                    }

                    processed_input = *command_history;
                    std::cout << processed_input << '\n';
                }
            }

            // Add to history
            if (strlen(input) > 0) {
                add_history(processed_input.c_str());
                history.add(processed_input);
            }
            std::cin.clear();

            // Parsing
            std::vector<std::string> tokens = pars.tokenize(processed_input);

            // Execute
            if (tokens[0] == "byemoser") break;
            else if (tokens[0] == "cd") { // Change directory
                if (tokens.size() < 2) std::cerr << "cd: missing argument" << '\n';
                else {
                    std::string path = tokens[1];
                    
                    // Expand tilde to home directory
                    if (path[0] == '~') {
                        wordexp_t exptresult{};

                        if (wordexp(path.c_str(), &exptresult, 0) == 0) {
                            path = exptresult.we_wordv[0];
                            wordfree(&exptresult);
                        }
                    }
                    
                    if (chdir(path.c_str()) != 0) perror("cd failed");
                }
                continue; // No move to fork/exec
            }
            else if (tokens[0] == "history") {
                history.print();
                continue;
            }
            else { // Execute
                bool isBackground = false;

                if (!tokens.empty() && tokens.back() == "&") {
                    isBackground = true;
                    tokens.pop_back(); // Remove the &
                }

                pars.process_redirection(tokens, exec);

                if (!tokens.empty()) {
                    if (isBackground) {
                        exec.execute_background(tokens);
                    }
                    else {
                        exec.execute_command(tokens);
                    }
                }
            }
        }
        exec.check_background_processes();
        free(input);
    }
    write_history(".moser_history");
    return;
}

std::string Shell::get_distribution_name() {
    std::ifstream file("/etc/os-release");
    if (!file.is_open()) {
        return "Unknown";
    }

    std::string line{};
    std::regex nameRegex("NAME=\"([^\"]+)\"");
    std::smatch match{};

    while (std::getline(file, line)) {
        if (std::regex_match(line, match, nameRegex)) {
            if (match.size() > 1) {
                return match[1].str(); // Return the captured group
            }
        }
    }
    return "Unknown";
}