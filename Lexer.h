#pragma once
#include <vector>
#include "sym.hpp"
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "LexemeType.hpp"
#include <string>

class Lexer {
public:
   Lexer();
   void tokenize(std::string input);
   void scan(std::string test);
   void print_tokens();
private:
   std::vector<std::pair<LexemeType, std::string>> tokens;
   Sym classify_item(char c);
   std::vector<std::vector<int>> trans_matrix;
   std::unordered_set<std::string> special_ops;
   std::unordered_set<std::string> reserved_words;
   void load_from_file(std::string filename, std::unordered_set<std::string>& collection);
   void load_special_ops();
   void load_reserved_words();
   Sym scan_char(char c);
   std::unordered_map<int, std::string> acceptor_decode;
};

Lexer::Lexer() {
   tokens.reserve(100);
   trans_matrix = {
      // digit, special, dot, char
      {1, 100, -1, 3},
      {1, 100, 2, 3},
      {2, 102, -1, -1},
      {3, 101, -1, 3} 
   };
   acceptor_decode.insert(std::make_pair(100, "Entero"));
   acceptor_decode.insert(std::make_pair(101, "Identificador"));
   acceptor_decode.insert(std::make_pair(102, "Decimal"));
   acceptor_decode.insert(std::make_pair(103, "Operador"));
   load_special_ops();
   load_from_file();
}

void Lexer::tokenize(std::string input) {
   std::string token = "";
   int state = 0;
   std::cout << "input: " << input << "\n"; 
   for (char c : input) {
      Sym sym = scan_char(c);
      // Handle accepting and error state
      if (state >= 100 || state == -1) {
         LexemeType type = LexemeType::error;
         switch(state) {
            case 100:
              type = LexemeType::integer;
              break;
            case 101:
               type = LexemeType::identifier;
               break;
            case 102:
               type = LexemeType::decimal;
               break;
            case 103:
               type = LexemeType::special;
               break;
            case -1:
               type = LexemeType::error;
               break;
         }
         tokens.push_back(std::make_pair(type, token));
         tokens.push_back(std::make_pair(type, std::string(1, c)));
         // std::cout << acceptor_decode[state] << " " << token << "\n";
         token = " ";
         state = 0;
      }
      std::cout << "sym:" << sym << std::endl;

      state = trans_matrix[state][sym];
      token += c;
      // Print state
      std::cout << "STATE:" << std::to_string(state) << "\n";
   }
}

void Lexer::print_tokens() {

}

inline void Lexer::load_from_file(std::string filename, std::unordered_set<std::string>& collection) {
   std::ifstream file(filename);
   std::string line;
   std::cout << "Loading file " << filename << "\n";
   while (std::getline(file, line)) {
      collection.insert(line);
      std::cout << line << "\n";
   }
}

void Lexer::load_special_ops() {
   load_from_file("./special_operators.txt", special_ops);
}

void Lexer::load_reserved_words() {
   load_from_file("./reserved_words.txt", reserved_words);
}

Sym Lexer::scan_char(char c) {
   if (isdigit(c))
      return Sym::DIGIT;
   if (isalpha(c))
      return Sym::CHAR;
   std::string s = "";
   s += c;
   if (special_ops.find(s) != special_ops.end())
      return Sym::SPECIAL;
   return Sym::ERROR;
}