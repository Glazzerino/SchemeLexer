#pragma once
#include <vector>
#include "sym.hpp"
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <string>

class Lexer {
public:
   Lexer();
   void tokenize(std::string input);
   void scan(std::string test);
   void print_tokens();
private:
   std::vector<std::string> tokens;
   SYM classify_item(char c);
   std::vector<std::vector<int>> trans_matrix;
   std::unordered_set<std::string> special_ops;
   void load_special_ops();
   SYM scan_char(char c);
};

Lexer::Lexer() {
   tokens.reserve(100);
   trans_matrix = {
      
   };
   load_special_ops();
}

void Lexer::tokenize(std::string input) {
   std::string token = "";
   int state = 0;
   for (char c : input) {
      std::cout << c << std::endl;
      SYM sym = scan_char(c);
      int state = trans_matrix[state][sym];
      if (state == 100 || state == SYM::ERROR)
         return;
      
      // Print state
      std::cout << "STATE:" << std::to_string(state) << "\n";
   }
}

void Lexer::print_tokens() {
}

void Lexer::load_special_ops() {
   //Load strings from file into set
   std::ifstream file("./special_operators.txt");
   std::string line;
   std::cout << "Loading special operators...\n";
   while (std::getline(file, line)) {
      special_ops.insert(line);
      std::cout << line << "\n";
   }
}

SYM Lexer::scan_char(char c) {
   if (isdigit(c))
      return SYM::DIGIT;

   std::string s = "";
   s += c;
   if (special_ops.find(s) != special_ops.end())
      return SYM::SPECIAL;
   return SYM::ERROR;
}