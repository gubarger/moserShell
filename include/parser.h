#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <string>
#include <vector>

class Executor;

class Parser {
public:
    /**
     * @brief Splitting commands into tokens
     * 
     * @return array of commands
     */
    static std::vector<std::string> tokenize(const std::string& input);
    void process_redirection(std::vector<std::string>& tokens, Executor& executor);
};

#endif // INCLUDE_PARSER_H_
