#include "parser.h"


std::shared_ptr<ASTNode> Parser::parse_expression() {
    auto node = parse_term(); // 5
    while (pos < tokens.size() && (current_token().type == TokenType::Plus || current_token().type == TokenType::Minus)){
        auto op_node = std::make_shared<ASTNode>();
        op_node->type = current_token().type;
        op_node->value = current_token().value;
        next_token();
        op_node->children.push_back(node);
        op_node->children.push_back(parse_term());
        node = op_node;
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_term() {
    auto node = parse_factor(); // 4
    while (pos < tokens.size() && (current_token().type == TokenType::Asterisk || current_token().type == TokenType::Slash)) {
        auto op_node = std::make_shared<ASTNode>();
        op_node->type = current_token().type;
        op_node->value = current_token().value;
        next_token();
        op_node->children.push_back(node);
        op_node->children.push_back(parse_factor());
        node = op_node;
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

std::shared_ptr<ASTNode> Parser::parse_assignment() {
    if (current_token().type != TokenType::Identifier) throw std::runtime_error("expected identifier before assigment");

    auto identifier_node = std::make_shared<ASTNode>();
    identifier_node->type = TokenType::Identifier;
    identifier_node->value = current_token().value;
    next_token();

    if (current_token().type != TokenType::Assignment) throw std::runtime_error("Expected '=' after identifier");

    auto assignment_node = std::make_shared<ASTNode>();
    assignment_node->type = TokenType::Assignment;
    assignment_node->value = "=";
    next_token();

    auto expression_node = parse_expression();
    assignment_node->children.push_back(identifier_node);
    assignment_node->children.push_back(expression_node);

    return assignment_node;
}

std::shared_ptr<ASTNode> Parser::parse() {
    if (current_token().type == TokenType::Identifier) return parse_assignment();
    return parse_expression();
}