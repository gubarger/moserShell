#include "parser.h"
#include "executor.h"

std::vector<std::string> Parser::tokenize(const std::string& input) {
    std::vector<std::string> tokens{};
    std::string currentToken{};

    bool quote = false;
    char quoteShar = '\0';

    for (size_t i = 0; i < input.length(); i++) {
        char symbol = input[i];

        if (quote) {
            if (symbol == quoteShar) {
                quote = false;
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            } 
            else {
                currentToken += symbol;
            }
        } 
        else {
            if (symbol == '\'' || symbol == '"') {
                quote = true;
                quoteShar = symbol;
            
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            }
            else if (std::isspace(symbol)) {
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            }
            else {
                if (i + 1 < input.length()) {
                    std::string doubleChars = std::string(1, symbol) + input[i + 1];

                    if (doubleChars == ">>" || doubleChars == "2>") {
                        if (!currentToken.empty()) {
                            tokens.push_back(currentToken);
                            currentToken.clear();
                        }
                        tokens.push_back(doubleChars);

                        i++; // Skip next char
                        continue;
                    }
                }

                if (symbol == '|' || symbol == '>' || symbol == '<') {
                    if (!currentToken.empty()) {
                        tokens.push_back(currentToken);
                        currentToken.clear();
                    }
                    tokens.push_back(std::string(1, symbol));
                } 
                else {
                    currentToken += symbol;
                }
            }
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

void Parser::process_redirection(std::vector<std::string>& tokens, Executor& executor) {
    for (auto iter = tokens.begin(); iter != tokens.end(); ) {
        if (*iter == ">") {
            if (std::next(iter) != tokens.end()) {
                std::string filename = *std::next(iter);

                executor.set_output_redirection(filename, false);

                iter = tokens.erase(iter); // Remove ">"
                iter = tokens.erase(iter); // Remove fillname
            }
            else {
                std::cerr << "Syntax error: > without filename" << '\n';
                ++iter;
            }
        }
        else if (*iter == ">>") {
            if (std::next(iter) != tokens.end()) {
                std::string filename = *std::next(iter);

                executor.set_output_redirection(filename, true);

                iter = tokens.erase(iter);
                iter = tokens.erase(iter);
            }
            else {
                std::cerr << "Syntax error: >> without filename" << '\n';
                ++iter;
            }
        }
        else if (*iter == "<") {
            if (std::next(iter) != tokens.end()) {
                std::string filename = *std::next(iter);

                executor.set_input_redirection(filename);

                iter = tokens.erase(iter);
                iter = tokens.erase(iter);
            }
            else {
                std::cerr << "Syntax error: < without filename" << '\n';
                ++iter;
            }
        }
        else if (*iter == "2>") {
            if (std::next(iter) != tokens.end()) {
                std::string filename = *std::next(iter);

                executor.set_error_redirection(filename);

                iter = tokens.erase(iter);
                iter = tokens.erase(iter);
            }
            else {
                std::cerr << "Syntax error: 2> without filename" << '\n';
                ++iter;
            }
        }
        else {
            ++iter;
        }
    }
}