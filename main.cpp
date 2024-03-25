#include <iostream>
#include <string>
// #include "parser.h"
// #include "lexer.h"

// Declare the Flex and Bison functions and variables
// extern int yylex();
// extern int yyparse();
extern FILE* yyin;

// Custom error handling function
void yyerror(const char* s) {
    std::cerr << "Parse error: " << s << std::endl;
}

int main() {
    std::string input;

    //std::cout << "Enter J code (press Ctrl+D or Ctrl+Z to end):" << std::endl;

    // Read input from the user
    //std::string line;
    //while (std::getline(std::cin, line)) {
    //    input += line + "\n";
    //}

    input = "1 + 2";

    // Open the input string as a file stream
    FILE* inputStream = fmemopen(const_cast<char*>(input.c_str()), input.size(), "r");
    if (inputStream == nullptr) {
        std::cerr << "Failed to open input stream." << std::endl;
        return 1;
    }

    // Set the input stream for Flex
    //yyin = inputStream;

    // Parse the input
    //int parseResult = yyparse();
    int parseResult = 1;
    
    // Close the input stream
    fclose(inputStream);

    if (parseResult == 0) {
        std::cout << "Parsing successful." << std::endl;
    } else {
        std::cerr << "Parsing failed." << std::endl;
    }

    return 0;
}