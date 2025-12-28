#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <tokens.h>
#include <lexer.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Please provide a .ced file to compile. Ex: " << argv[0] << " <path_to_file.ced>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    
    if(!file.good()) {
        std::cerr << "Could not open the provided file: " << argv[1] << std::endl;
        return 1;
    }
    
	std::stringstream buffer;
	buffer << file.rdbuf();
    std::string file_content = buffer.str();

    Token token = createToken(TokenType::EOF_TOKEN, "aaa");
    printToken(token);

    return 0;
}