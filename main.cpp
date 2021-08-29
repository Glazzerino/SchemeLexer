#include <iostream>
#include <vector>
#include "Lexer.h"
int main() {
   std::cout << "**Scheme Lexer**\n";
   Lexer lexer;
   std::string teststr = "123123.123 test - > lmao"; 
   lexer.tokenize(teststr);
   lexer.print_tokens();   
}
