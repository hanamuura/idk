#include "lexer.h"
#include "cctype"
#include <stdexcept>

Lexer::Lexer(const std::string &source) : source(source), position(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while(position < source.size()) {
        if (isspace(source[position])) {
            position++;
            continue;
        }

        if (isdigit(source[position])) {
            tokens.push_back(Token {TokenType::Number, read_number()});
        } else if (isalpha(source[position])) {
            std::string identifier = read_identifier();
            if (identifier == "print") {
                tokens.push_back(Token {TokenType::Print, identifier});
            } else {
                tokens.push_back(Token {TokenType::Identifier, identifier});
            }
        } else {
            char cur = source[position];

            switch (cur) {
                case '+': tokens.push_back(Token {TokenType::Plus, "+"}); break;
                case '-': tokens.push_back(Token {TokenType::Minus, "-"}); break;
                case '/': tokens.push_back(Token {TokenType::Slash, "/"}); break;
                case '*': tokens.push_back(Token {TokenType::Asterisk, "*"}); break;
                case '=': tokens.push_back(Token {TokenType::Assignment, "="}); break;
                case '(': tokens.push_back(Token {TokenType::OpenParent, "("}); break;
                case ')': tokens.push_back(Token {TokenType::CloseParent, ")"}); break;

            default:
                throw std::runtime_error("Unknown character: " + std::string(1, cur));
            }

            position++;
        }
    }

    tokens.push_back(Token {TokenType::EndOfFile, ""});
    return tokens;
}

std::string Lexer::read_number() {
    size_t start = position;

    while (position < source.size() && isdigit(source[position])) {
        position++;
    }

    return source.substr(start, position - start);
}

std::string Lexer::read_identifier() {
    size_t start = position;

    while (position < source.size() && isalnum(source[position])) {
        position++;
    }

    return source.substr(start, position - start);
}