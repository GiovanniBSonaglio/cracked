#include <tokens.h>

std::string tokenTypeToString(TokenType type) {
    switch(type) {
        case TokenType::EOF_TOKEN: return "EOF_TOKEN";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::STRING: return "STRING";
        case TokenType::CHAR_VAL: return "CHAR_VAL";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::WHITESPACE: return "WHITESPACE";
        case TokenType::OPEN_BRACKET: return "OPEN_BRACKET";
        case TokenType::CLOSE_BRACKET: return "CLOSE_BRACKET";
        case TokenType::OPEN_CURLY: return "OPEN_CURLY";
        case TokenType::CLOSE_CURLY: return "CLOSE_CURLY";
        case TokenType::OPEN_PAREN: return "OPEN_PAREN";
        case TokenType::CLOSE_PAREN: return "CLOSE_PAREN";
        case TokenType::INT: return "INT";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::CHAR: return "CHAR";
        case TokenType::BOOL: return "BOOL";
        case TokenType::VOID: return "VOID";
        case TokenType::STRING_TYPE: return "STRING_TYPE";
        case TokenType::STRUCT: return "STRUCT";
        case TokenType::ENUM: return "ENUM";
        case TokenType::UNION: return "UNION";
        case TokenType::RETURN: return "RETURN";
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::WHILE: return "WHILE";
        case TokenType::FOR: return "FOR";
        case TokenType::FOREACH: return "FOREACH";
        case TokenType::CONTINUE: return "CONTINUE";
        case TokenType::BREAK: return "BREAK";
        case TokenType::SWITCH: return "SWITCH";
        case TokenType::CASE: return "CASE";
        case TokenType::DEFAULT: return "DEFAULT";
        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::NULLPTR: return "NULLPTR";
        case TokenType::NULL_VALUE: return "NULL_VALUE";
        case TokenType::TRY: return "TRY";
        case TokenType::EXCEPT: return "EXCEPT";
        case TokenType::THROW: return "THROW";
        case TokenType::INCLUDE: return "INCLUDE";
        case TokenType::ADDRESS: return "ADDRESS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::DASH: return "DASH";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";
        case TokenType::CARET: return "CARET";
        case TokenType::MODULE: return "MODULE";
        case TokenType::QUESTION: return "QUESTION";
        case TokenType::COMMA: return "COMMA";
        case TokenType::COLON: return "COLON";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::DOT: return "DOT";
        case TokenType::ARROW: return "ARROW";
        case TokenType::EQUALS: return "EQUALS";
        case TokenType::NOT_EQUALS: return "NOT_EQUALS";
        case TokenType::NOT: return "NOT";
        case TokenType::LESS_EQUALS: return "LESS_EQUALS";
        case TokenType::LESS: return "LESS";
        case TokenType::GREATER_EQUALS: return "GREATER_EQUALS";
        case TokenType::GREATER: return "GREATER";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::OR: return "OR";
        case TokenType::AND: return "AND";
        default: return "UNKNOWN_TOKEN";
    }
}

Token createToken(TokenType type, const std::string& value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

void printToken(Token token) {
    printf("%s (%s)\n", tokenTypeToString(token.type).c_str(), token.value.c_str());
}