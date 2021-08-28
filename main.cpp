#include <iostream>
#include <vector>
#include "Lexer.h"

int main() {
   std::cout << "**Scheme Lexer**\n";
   Lexer lexer;
   std::string teststr = "1";
   lexer.tokenize(teststr);
   // lexer.print_tokens();   
}
