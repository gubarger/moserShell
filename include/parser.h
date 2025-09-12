#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <string>
#include <vector>
#include <sstream>

struct Parser {
    std::istringstream iss_{};
    std::vector<std::string> args_{};
    std::string arg_{};
};

#endif // INCLUDE_PARSER_H_
