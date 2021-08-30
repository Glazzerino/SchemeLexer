#include <iostream>
#include <vector>
#include "Lexer.h"
#include <chrono>
int main() {
   std::cout << "**Scheme Lexer**\n";
   Lexer lexer;
   //benchmark lexer using timer
   auto start = std::chrono::high_resolution_clock::now();
   lexer.lexerScheme("./testfile.sch");
   auto end = std::chrono::high_resolution_clock::now();
   std::cout << "Tiempo de ejecución: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds\n";
}
