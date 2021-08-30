#include <iostream>
#include <vector>
#include "Lexer.h"
int main() {
   std::cout << "**Scheme Lexer**\n";
   Lexer lexer;
   lexer.lexerScheme("./testfile.sch");
}
