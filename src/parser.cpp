#include "parser.h"


std::shared_ptr<ASTNode> Parser::parse_expression() {
    auto node = parse_term();
    while (pos < tokens.size() && (current_token().value == "+" || current_token().value == "-")){
        auto op_node = std::make_shared<ASTNode>();
        op_node->type = current_token().value == "+"
            ? TokenType::Plus
            : TokenType::Minus;
        op_node->value = current_token().value;
        next_token();
        op_node->children.push_back(node);
        op_node->children.push_back(parse_term());
        node = op_node;
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_term() {
    auto node = parse_factor();
    while (pos < tokens.size() && (current_token().value == "*" || current_token().value == "/")) {
        auto op_node = std::make_shared<ASTNode>();
        op_node->type = current_token().value == "*"
            ? TokenType::Asterisk
            : TokenType::Slash;
        op_node->value = current_token().value;
        next_token();
        op_node->children.push_back(node);
        op_node->children.push_back(parse_factor());
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_factor() {
    auto node = std::make_shared<ASTNode>();
    if (current_token().type == TokenType::Number || current_token().type == TokenType::Identifier) {
        node->type = current_token().type;
        node->value = current_token().value;
        next_token();
    } else if (current_token().value == "(") {
        next_token();
        node = parse_expression();
        if (current_token().value == ")") {
            throw std::runtime_error("unexpected token type: " + current_token().value);
        }
        next_token();
    } else {
        throw std::runtime_error("unexpected token type: " + current_token().value);
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse() {
    return parse_expression();
}