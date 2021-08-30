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
   void lexerScheme(std::string filename);
private:
   std::vector<std::pair<LexemeType, std::string>> tokens;
   Sym classify_item(char c);
   std::vector<std::vector<int>> trans_matrix;
   std::unordered_map<std::string,std::string> special_ops;
   std::unordered_set<std::string> reserved_words;
   void load_from_file(std::string filename, std::unordered_set<std::string>& collection);
   void load_special_ops();
   void load_reserved_words();
   Sym scan_char(char c);
   std::unordered_map<int, std::string> acceptor_decode;
   LexemeType classify_lexeme(int state);
};

Lexer::Lexer() {
   tokens.reserve(100);
   trans_matrix = {
      // digit, special, dot, char
      {1, 103, -1, 3},
      {1, 100, 2, 3},
      {2, 102, -1, -1},
      {3, 101, -1, 3} 
   };
   load_special_ops();
   load_reserved_words();
}

void Lexer::tokenize(std::string input) {
   std::string token = "";
   int state = 0;
   std::cout << "input: " << input << "\n"; 
   bool is_comment = false;
   size_t counter = 0;

   for (char c : input) {
      Sym sym = scan_char(c);
      // If comment char is found, ignore everything until newline
      if (c == ';')
         is_comment = true;
      if (is_comment) {
         if (c == '\n' || counter == input.size() - 1) {
            is_comment = false;
            tokens.push_back(std::make_pair(LexemeType::comment, token));
            token = "";
         } else {
            token += c;
         }
         continue;
      }

      // Handle accepting and error state
      if (state >= 100 || state == -1) {
         LexemeType type = classify_lexeme(state);
         if (reserved_words.find(token) != reserved_words.end()) 
            type = LexemeType::reserved;
         tokens.push_back(std::make_pair(type, token));
         token = "";
         state = 0;
      } 
      if (c != ' ')
         token += c;
      state = trans_matrix[state][sym];
      counter++;
   }

   // manage final token
   if (state <= 100 || state != -1) {
      state = trans_matrix[Sym::SPECIAL][state];
      LexemeType type = classify_lexeme(state);
      if (reserved_words.find(token) != reserved_words.end())
         type = LexemeType::reserved;
      tokens.push_back(std::make_pair(type, token));
      state = 0;
   }
}

void Lexer::print_tokens() {
   for (auto pair : tokens) {
      if (pair.second == " " || pair.second == "\n")
         continue;
      std::cout << pair.second << " ";
      switch (pair.first)  {
         case LexemeType::decimal:
            std::cout << "constante de punto flotante " << pair.second << "\n";
            break;
         case LexemeType::error:
            std::cout << "valor erróneo\n";
            break;
         case LexemeType::identifier:
            std::cout << "identificador\n";
            break;
         case LexemeType::integer:
            std::cout << "constante entera " << pair.second << "\n";
            break;
         case LexemeType::reserved:
            std::cout << "palabra reservada " << pair.second << "\n";
            break;
         case LexemeType::special:
            std::cout << "operador especial " << special_ops[pair.second] << "\n";
            break;
         case LexemeType::comment:
            std::cout << "comentario\n";
            break;
      }
   }
}

void Lexer::load_special_ops() {
   std::ifstream file("./special_operators.txt");
   std::string line;
   while (std::getline(file, line)) {
      unsigned int separator = line.find(',');
      if (separator == -1) {
         std::cout << "separator not found in operator file\n";
      } 
      std::string op = line.substr(0, separator);
      // std::cout << "op: " << op << "\n";
      std::string desc = line.substr(separator);
      special_ops.insert(std::make_pair(op, desc));
   }
}

void Lexer::load_reserved_words() {
   std::ifstream file("./reserved_word.txt");
   std::string line;
   while (std::getline(file, line)) {
      reserved_words.insert(line);
   }
}

Sym Lexer::scan_char(char c) {
   if (isdigit(c))
      return Sym::DIGIT;
   if (isalpha(c))
      return Sym::CHAR;
   if (c == '.')
      return Sym::DOT;
   if (c == ' ' || c == '\n' || c == '\t')
      return Sym::SPECIAL;
   std::string s = "";
   s += c;
   if (special_ops.find(s) != special_ops.end())
      return Sym::SPECIAL;
   return Sym::ERROR;
}

LexemeType Lexer::classify_lexeme(int state) {
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
   return type;
}

void Lexer::lexerScheme(std::string filename) {
   std::ifstream file(filename);
   std::string line;
   while (std::getline(file, line)) {
      std::cout << line << "\n";
      tokenize(line);
      print_tokens();
   }
}