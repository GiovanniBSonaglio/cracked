#pragma once

#include <string>
#include <unordered_map>

enum class TokenType {
    EOF_TOKEN, // End of file

    // Literals
	IDENTIFIER,
    NUMBER,
	STRING,
    CHAR_VAL,

    // Ignoreds
    COMMENT,
    WHITESPACE,

    // Brackets
    OPEN_BRACKET,
	CLOSE_BRACKET,
	OPEN_CURLY,
	CLOSE_CURLY,
	OPEN_PAREN,
	CLOSE_PAREN,

    /**** Reserved Keywords ****/
    // Data types
    INT,
    FLOAT,
    CHAR,
    BOOL,
    VOID,
    STRING_TYPE,
    STRUCT,
    ENUM,
    UNION,

    // Program structure
    RETURN,
    IF,
    ELSE,

    // Loops
    WHILE,
    FOR,
    FOREACH,
    CONTINUE,
    BREAK,

    // Switch case
    SWITCH,
    CASE,
    DEFAULT,

    // Boolean literals
    TRUE,
    FALSE,

    // Null
    NULLPTR,
    NULL_VALUE,

    // Try-except
    TRY,
    EXCEPT,
    THROW,

    INCLUDE,

    /**** ******** ****/
    
    // Operators
    ADDRESS,
    PLUS,
	DASH,
	SLASH,
	STAR, // Also used for pointers
    CARET, // Exponentiation
	MODULE,

    // Delimiters
    QUESTION,
    COMMA,
    COLON,
    SEMICOLON,
    DOT,
    ARROW,

    // Comparison
    EQUALS,
	NOT_EQUALS,
	NOT,
	LESS_EQUALS,
	LESS,
	GREATER_EQUALS,
	GREATER,

    // Assignment
    ASSIGN,

    // Logical
    OR,
	AND,
};

inline std::unordered_map<std::string, TokenType> reserved_identifiers_lu = {
    {"int", TokenType::INT},
    {"float", TokenType::FLOAT},
    {"char", TokenType::CHAR},
    {"bool", TokenType::BOOL},
    {"void", TokenType::VOID},
    {"string", TokenType::STRING_TYPE},
    {"struct", TokenType::STRUCT},
    {"enum", TokenType::ENUM},
    {"return", TokenType::RETURN},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"for", TokenType::FOR},
    {"foreach", TokenType::FOREACH},
    {"continue", TokenType::CONTINUE},
    {"break", TokenType::BREAK},
    {"switch", TokenType::SWITCH},
    {"case", TokenType::CASE},
    {"default", TokenType::DEFAULT},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"nullptr", TokenType::NULLPTR},
    {"NULL", TokenType::NULL_VALUE},
    {"try", TokenType::TRY},
    {"except", TokenType::EXCEPT},
    {"throw", TokenType::THROW},
};

typedef struct {
    TokenType type;
    std::string value;
} Token;

std::string tokenTypeToString(TokenType type);
Token createToken(TokenType type, const std::string& value);
void printToken(Token token);

inline bool isIgnoreToken(TokenType type) {
    return (type == TokenType::COMMENT || type == TokenType::WHITESPACE);
}