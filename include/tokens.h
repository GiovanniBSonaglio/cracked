#pragma once

#include <string>

enum class TokenType {
    EOF_TOKEN, // End of file

    // Literals
    NUMBER,
	STRING,
	IDENTIFIER,

    // Brackets
    OPEN_BRACKET,
	CLOSE_BRACKET,
	OPEN_CURLY,
	CLOSE_CURLY,
	OPEN_PAREN,
	CLOSE_PAREN,

    /**** Keywords ****/

    // Program structure
    FUNCTION,
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
    
    // Data types
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    BOOL,
    VOID,
    STRING_TYPE,
    STRUCT,

    // Variable management
    CLASS,
    NEW,
    DELETE,
    CONST,

    // Boolean literals
    TRUE,
    FALSE,

    // Null
    NULLPTR,
    NULL_VALUE,

    /**** ******** ****/
    
    // Operators
    PLUS,
	DASH,
	SLASH,
	STAR, // Also used for pointers
    CARET, // Exponentiation
	PERCENT,

    // Comparison
    EQUALS,
	NOT,
	NOT_EQUALS,
	LESS,
	LESS_EQUALS,
	GREATER,
	GREATER_EQUALS,

    // Assignment
    ASSIGN,
    ASSIGN_AND,

    // Delimiters
    COMMA,
    SEMICOLON,
    DOT,
    ARROW,

    // Logical
    OR,
	AND,
};

typedef struct {
    TokenType type;
    std::string value;
} Token;

std::string tokenTypeToString(TokenType type);
Token createToken(TokenType type, const std::string& value);
void printToken(Token token);