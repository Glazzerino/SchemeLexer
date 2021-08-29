#include <iostream>
#include <vector>
#include "Lexer.h"
int main() {
   std::cout << "**Scheme Lexer**\n";
   Lexer lexer;
   std::string teststr = "123123.123 test - > lambda"; 
   lexer.tokenize(teststr);
   lexer.print_tokens();   
}
