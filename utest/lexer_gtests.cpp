#include <gtest/gtest.h>

#include <lexer.h>
#include <tokens.h>

#include <vector>
#include <string>

static std::vector<Token> withoutEOF(const std::vector<Token>& v) {
    if(v.empty()) return v;
    if(v.back().type == TokenType::EOF_TOKEN) {
        return std::vector<Token>(v.begin(), v.end() - 1);
    }
    return v;
}

TEST(Lexer, IdentifiersAndReservedKeywords) {
    Lexer lx("int foo");
    lx.tokenize();

    auto tokens = withoutEOF(lx.tokenList);
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].type, TokenType::INT);
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[1].value, "foo");
}

TEST(Lexer, NumberLiterals_Variety) {
    Lexer lx("42 0x2A 3.14 1e-3");
    lx.tokenize();

    auto tokens = withoutEOF(lx.tokenList);
    ASSERT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[0].value, "42");
    EXPECT_EQ(tokens[1].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[1].value, "0x2A");
    EXPECT_EQ(tokens[2].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[2].value, "3.14");
    EXPECT_EQ(tokens[3].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[3].value, "1e-3");
}

TEST(Lexer, StringAndCharLiterals_Escapes) {
    Lexer lx(R"("hello \"world\"" 'a' '\\n')");
    lx.tokenize();

    auto tokens = withoutEOF(lx.tokenList);
    ASSERT_GE(tokens.size(), 2);
    EXPECT_EQ(tokens[0].type, TokenType::STRING);
    EXPECT_EQ(tokens[0].value, "hello \\\"world\\\"");
    // char tests: depending on the parser behaviour, char may be 'a' or '\n'
    bool sawChar = false;
    for(size_t i=1;i<tokens.size();++i) {
        if(tokens[i].type == TokenType::CHAR_VAL) {
            sawChar = true;
            EXPECT_TRUE(tokens[i].value == "a" || tokens[i].value == "\\n");
        }
    }
    EXPECT_TRUE(sawChar);
}

TEST(Lexer, CommentsAndWhitespaceAreSkipped) {
    Lexer lx("foo // this is a comment\n  bar");
    lx.tokenize();

    auto tokens = withoutEOF(lx.tokenList);
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[0].value, "foo");
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[1].value, "bar");
}

TEST(Lexer, OperatorsAndPunctuation_Concatenation) {
    Lexer lx("a->b==c+d");
    lx.tokenize();

    auto tokens = withoutEOF(lx.tokenList);
    std::vector<TokenType> expected = {TokenType::IDENTIFIER, TokenType::ARROW, TokenType::IDENTIFIER,
                                       TokenType::EQUALS, TokenType::IDENTIFIER, TokenType::PLUS, TokenType::IDENTIFIER};
    ASSERT_EQ(tokens.size(), expected.size());
    
    for(size_t i=0; i < expected.size(); i++)
        EXPECT_EQ(tokens[i].type, expected[i]);
}

TEST(Lexer, ComplexMixedInput) {
    Lexer lx("if(true){return 0;} // done");
    lx.tokenize();

    auto tokens = withoutEOF(lx.tokenList);
    std::vector<TokenType> expected = {TokenType::IF, TokenType::OPEN_PAREN, TokenType::TRUE, TokenType::CLOSE_PAREN,
                                       TokenType::OPEN_CURLY, TokenType::RETURN, TokenType::NUMBER, TokenType::SEMICOLON,
                                       TokenType::CLOSE_CURLY};

    ASSERT_EQ(tokens.size(), expected.size());
    
    for(size_t i=0; i < expected.size(); i++)
        EXPECT_EQ(tokens[i].type, expected[i]);
    
    EXPECT_EQ(tokens.back().value, "}");
}

TEST(Lexer, ErrorOnUnrecognizedToken) {
    Lexer lx("foo @ bar");
    lx.tokenize();

    // On error, lexer does NOT push EOF token; ensure final token is not EOF
    ASSERT_FALSE(lx.tokenList.empty());
    EXPECT_NE(lx.tokenList.back().type, TokenType::EOF_TOKEN);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
