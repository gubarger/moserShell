#include "parser.h"

std::vector<std::string> Parser::tokenize(const std::string& input) {
    std::vector<std::string> tokens{};
    std::string currentToken{};
    bool quote = false;
    char quoteShar = '\0';


    for (char symbol : input) {
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
            } else if (std::isspace(symbol)) {
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            } else if (symbol == '|' || symbol == '>' || symbol == '<') {
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                tokens.push_back(std::string(1, symbol));
            } else {
                currentToken += symbol;
            }
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}