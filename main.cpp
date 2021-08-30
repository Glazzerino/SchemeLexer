#include <iostream>
#include <vector>
#include "Lexer.h"
int main() {
   std::cout << "**Scheme Lexer**\n";
   Lexer lexer;
   std::string teststr = "";
   // load strings from testfile
   std::string line;
   std::ifstream myfile ("testfile.sch");
   while(std::getline(myfile, line)) {
      teststr += line;
   }
   myfile.close();
   lexer.tokenize(teststr);
   lexer.print_tokens();   
}
