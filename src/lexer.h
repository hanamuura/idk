#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <vector>
#include <string>

class Lexer {
public:
    explicit Lexer(const std::string &source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t position;

    std::string read_number();
    std::string read_identifier();
};

#endif // LEXER_H
