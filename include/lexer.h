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
    std::vector<translator> translatorList = {
        {TokenType::IDENTIFIER,         std::regex(R"([A-Za-z_][A-Za-z0-9_]*)"),                                   &symbolHandler},
        {TokenType::NUMBER,             std::regex(R"((0x[0-9A-Fa-f]+|[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?))"),     &defaultHandler},
        {TokenType::STRING,             std::regex(R"("([^"\\]|\\.)*")"),                                          &stringHandler},
        {TokenType::CHAR_VAL,           std::regex(R"('(\\)?.{1}')"),                                              &stringHandler},
        {TokenType::COMMENT,            std::regex(R"(\/\/.*)"),                                                   &skipHandler},
        {TokenType::WHITESPACE,         std::regex(R"(\s+)"),                                                      &skipHandler},
        {TokenType::OPEN_BRACKET,       std::regex(R"(\[)"),                                                       &defaultHandler},
        {TokenType::CLOSE_BRACKET,      std::regex(R"(\])"),                                                       &defaultHandler},
        {TokenType::OPEN_CURLY,         std::regex(R"(\{)"),                                                       &defaultHandler},
        {TokenType::CLOSE_CURLY,        std::regex(R"(\})"),                                                       &defaultHandler},
        {TokenType::OPEN_PAREN,         std::regex(R"(\()"),                                                       &defaultHandler},
        {TokenType::CLOSE_PAREN,        std::regex(R"(\))"),                                                       &defaultHandler},
        {TokenType::ADDRESS,            std::regex(R"(\&)"),                                                       &defaultHandler},
        {TokenType::PLUS,               std::regex(R"(\+)"),                                                       &defaultHandler},
        {TokenType::DASH,               std::regex(R"(\-)") ,                                                      &defaultHandler},
        {TokenType::SLASH,              std::regex(R"(\/)"),                                                       &defaultHandler},
        {TokenType::STAR,               std::regex(R"(\*)"),                                                       &defaultHandler},
        {TokenType::CARET,              std::regex(R"(\^)") ,                                                      &defaultHandler},
        {TokenType::MODULE,             std::regex(R"(\%)") ,                                                      &defaultHandler},
        {TokenType::QUESTION,           std::regex(R"(\?)"),                                                       &defaultHandler},
        {TokenType::COMMA,              std::regex(R"(,)"),                                                        &defaultHandler},
        {TokenType::COLON,              std::regex(R"(:)"),                                                        &defaultHandler},
        {TokenType::SEMICOLON,          std::regex(R"(;)"),                                                        &defaultHandler},
        {TokenType::DOT,                std::regex(R"(\.)"),                                                       &defaultHandler},
        {TokenType::ARROW,              std::regex(R"(->)"),                                                       &defaultHandler},
        {TokenType::EQUALS,             std::regex(R"(==)"),                                                       &defaultHandler},
        {TokenType::NOT_EQUALS,         std::regex(R"(!=)"),                                                       &defaultHandler},
        {TokenType::NOT,                std::regex(R"(\!)"),                                                       &defaultHandler},
        {TokenType::LESS_EQUALS,        std::regex(R"(<=)"),                                                       &defaultHandler},
        {TokenType::LESS,               std::regex(R"(<)"),                                                        &defaultHandler},
        {TokenType::GREATER_EQUALS,     std::regex(R"(>=)"),                                                       &defaultHandler},
        {TokenType::GREATER,            std::regex(R"(>)"),                                                        &defaultHandler},
        {TokenType::ASSIGN,             std::regex(R"(=)"),                                                        &defaultHandler},
        {TokenType::OR,                 std::regex(R"(\|\|)"),                                                     &defaultHandler},
        {TokenType::AND,                std::regex(R"(&&)"),                                                       &defaultHandler},
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