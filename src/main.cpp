#include <iostream>
#include "lexer.h"
#include "parser.h"

std::string as_string(TokenType type) {
    switch (type)
    {
    case TokenType::Assignment:
        return "=";
    case TokenType::Asterisk:
        return "*";
    case TokenType::CloseParent:
        return ")";
    case TokenType::OpenParent:
        return "(";
    case TokenType::EndOfFile:
        return "eof";
    case TokenType::Identifier:
        return "identifier";
    case TokenType::Minus :
        return "-";
    case TokenType::Plus:
        return "+";
    case TokenType::Print:
        return "print";
    case TokenType::Slash:
        return "/";
    case TokenType::Number:
        return "number";
    default:
        return "hz";
    }
}

void print_ast(const std::shared_ptr<ASTNode>& node, int depth = 0) {
    if (!node) return;
    std::cout << std::string(depth * 2, ' ') << as_string(node->type) << " (" << node->value << " )" << std::endl;
    for (const auto& child : node->children) {
        print_ast(child, depth + 1);
    }
}

int main() {
#if 0 // lexer test
    std::string source = "print(10 + 5)";

    Lexer lexer(source);

    auto tokens = lexer.tokenize();

    std::cout << "tokens: " << std::endl;

    for (const auto &token : tokens) {
        std::cout << token.value << " (" << static_cast<int>(token.type) << ")" << std::endl;
    }
#endif
    std::vector<Token> tokens = {
        {TokenType::Identifier, "x"}, {TokenType::Assignment, "="}, {TokenType::Number, "5"},
        {TokenType::Plus, "+"}, {TokenType::Number, "4"}, {TokenType::Asterisk, "*"},
        {TokenType::Number, "2"}
    };
    auto parser = new Parser(tokens);
    auto ast = parser->parse();

    print_ast(ast);

    return 0;
}