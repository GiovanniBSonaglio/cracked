#pragma once

#include <regex>
#include <string>
#include <vector>
#include <unordered_map>

#include <tokens.h>

class Lexer;
using RegexCallback = void (Lexer::*)(const TokenType token_type, const std::smatch&);

typedef struct {
    TokenType token_type;
    std::regex regex;
    RegexCallback regex_cb;
} translator;

class Lexer {
    public:
    std::string source;
    std::vector<Token> tokenList;
    
    Lexer(std::string s) {
        source = s;
    }

    void tokenize(void);
private:
    // Order of translatorList matters
    std::vector<translator> translatorList = {
        {TokenType::IDENTIFIER,         std::regex(R"([A-Za-z_][A-Za-z0-9_]*)"),                                   &Lexer::symbolHandler},
        {TokenType::NUMBER,             std::regex(R"((0x[0-9A-Fa-f]+|[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?))"),     &Lexer::defaultHandler},
        {TokenType::STRING,             std::regex(R"("([^"\\]|\\.)*")"),                                          &Lexer::stringHandler},
        {TokenType::CHAR_VAL,           std::regex(R"('(\\)?.{1}')"),                                              &Lexer::stringHandler},
        {TokenType::COMMENT,            std::regex(R"(\/\/.*)"),                                                   &Lexer::skipHandler},
        {TokenType::WHITESPACE,         std::regex(R"(\s+)"),                                                      &Lexer::skipHandler},
        {TokenType::OPEN_BRACKET,       std::regex(R"(\[)"),                                                       &Lexer::defaultHandler},
        {TokenType::CLOSE_BRACKET,      std::regex(R"(\])"),                                                       &Lexer::defaultHandler},
        {TokenType::OPEN_CURLY,         std::regex(R"(\{)"),                                                       &Lexer::defaultHandler},
        {TokenType::CLOSE_CURLY,        std::regex(R"(\})"),                                                       &Lexer::defaultHandler},
        {TokenType::OPEN_PAREN,         std::regex(R"(\()"),                                                       &Lexer::defaultHandler},
        {TokenType::CLOSE_PAREN,        std::regex(R"(\))"),                                                       &Lexer::defaultHandler},
        {TokenType::ADDRESS,            std::regex(R"(\&)"),                                                       &Lexer::defaultHandler},
        {TokenType::PLUS,               std::regex(R"(\+)"),                                                       &Lexer::defaultHandler},
        {TokenType::ARROW,              std::regex(R"(->)"),                                                       &Lexer::defaultHandler},
        {TokenType::DASH,               std::regex(R"(\-)"),                                                       &Lexer::defaultHandler},
        {TokenType::SLASH,              std::regex(R"(\/)"),                                                       &Lexer::defaultHandler},
        {TokenType::STAR,               std::regex(R"(\*)"),                                                       &Lexer::defaultHandler},
        {TokenType::CARET,              std::regex(R"(\^)"),                                                       &Lexer::defaultHandler},
        {TokenType::MODULE,             std::regex(R"(\%)"),                                                       &Lexer::defaultHandler},
        {TokenType::QUESTION,           std::regex(R"(\?)"),                                                       &Lexer::defaultHandler},
        {TokenType::COMMA,              std::regex(R"(,)"),                                                        &Lexer::defaultHandler},
        {TokenType::COLON,              std::regex(R"(:)"),                                                        &Lexer::defaultHandler},
        {TokenType::SEMICOLON,          std::regex(R"(;)"),                                                        &Lexer::defaultHandler},
        {TokenType::DOT,                std::regex(R"(\.)"),                                                       &Lexer::defaultHandler},
        {TokenType::EQUALS,             std::regex(R"(==)"),                                                       &Lexer::defaultHandler},
        {TokenType::NOT_EQUALS,         std::regex(R"(!=)"),                                                       &Lexer::defaultHandler},
        {TokenType::NOT,                std::regex(R"(\!)"),                                                       &Lexer::defaultHandler},
        {TokenType::LESS_EQUALS,        std::regex(R"(<=)"),                                                       &Lexer::defaultHandler},
        {TokenType::LESS,               std::regex(R"(<)"),                                                        &Lexer::defaultHandler},
        {TokenType::GREATER_EQUALS,     std::regex(R"(>=)"),                                                       &Lexer::defaultHandler},
        {TokenType::GREATER,            std::regex(R"(>)"),                                                        &Lexer::defaultHandler},
        {TokenType::ASSIGN,             std::regex(R"(=)"),                                                        &Lexer::defaultHandler},
        {TokenType::OR,                 std::regex(R"(\|\|)"),                                                     &Lexer::defaultHandler},
        {TokenType::AND,                std::regex(R"(&&)"),                                                       &Lexer::defaultHandler},
    };
    int pos = 0;
    
    inline bool atEOF() {
        return pos >= source.size();
    }

    inline std::string getRemainder() {
        return source.substr(pos);
    }

    inline void advanceN(std::size_t N) {
        pos += N;
    }

    void defaultHandler(const TokenType token_type, const std::smatch& match) {
        advanceN(match.length(0));
        tokenList.push_back({token_type, match.str()});
    }

    void skipHandler(const TokenType token_type, const std::smatch& match) {
        advanceN(match.length(0));
    }

    void stringHandler(const TokenType token_type, const std::smatch& match) {
        advanceN(match.length(0));
        std::string inner = match.str().substr(1, match.str().size() - 2);
        tokenList.push_back({token_type, inner});
    }

    void symbolHandler(const TokenType token_type, const std::smatch& match) {
        auto it = reserved_identifiers_lu.find(match.str());

        if(it != reserved_identifiers_lu.end()) {
            tokenList.push_back({it->second, it->first});
        } else {
            tokenList.push_back({token_type, match.str()});
        }
        advanceN(match.length(0));
    }

    inline void printTokenList() {
        for(auto t : tokenList)
            printf("\nToken %s (%s)", tokenTypeToString(t.type).c_str(), t.value.c_str());
    }
};