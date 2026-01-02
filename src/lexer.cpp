#include <iostream>
#include <cstdio>
#include <regex>

#include <lexer.h>

void Lexer::tokenize(void) {
    while(!atEOF()) {
        bool matched = false;

        // Let's try each one of the available patterns
        for(const translator& t : translatorList) {
            std::smatch match;
            std::string remainder = getRemainder();

            if(!std::regex_search(remainder, match, t.regex))
                continue; // go to next regex right away if did not find
            
            if(match.position(0) != 0)
                continue; // go to next regex if found but not in pos 0
            
            matched = true;
            (this->*(t.regex_cb))(t.token_type, match);
            break;
        }

        if(!matched)
        goto err;
    }
    tokenList.push_back({TokenType::EOF_TOKEN, "EOF"});
    printTokenList();
    return;
err:
    fprintf(stderr, "Lexer Error: Unrecognized Token at pos=%d, remainder=%s\n", pos, getRemainder().c_str());
    printTokenList();
}