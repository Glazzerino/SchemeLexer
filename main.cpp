#include <iostream>
#include <vector>
#include "Lexer.h"
int main() {
   std::cout << "**Scheme Lexer**\n";
   Lexer lexer;
   std::string teststr = "this is a test 112233"; 
   lexer.tokenize(teststr);
   // lexer.print_tokens();   
}
