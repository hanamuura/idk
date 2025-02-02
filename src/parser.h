#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "token.h"


struct ASTNode {
    TokenType type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {};
    std::shared_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens;
    size_t pos = 0;

    Token current_token() { return tokens[pos]; };
    void next_token() { if ((tokens.size() - 1) > pos) pos++; };
    std::shared_ptr<ASTNode> parse_expression();
    std::shared_ptr<ASTNode> parse_term();
    std::shared_ptr<ASTNode> parse_factor();
};

#endif
