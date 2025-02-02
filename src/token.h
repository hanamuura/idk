#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    Number,
    Identifier,
    Plus,
    Minus,
    Asterisk,
    Slash,
    Assignment,
    Print,
    OpenParent,
    CloseParent,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

#endif