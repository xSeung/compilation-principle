#include "Lexical_analysis.h"
#include <algorithm>
#include <exception>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

auto Analyser::is_number(char c) -> bool { return (c >= '0' && c <= '9'); }
auto Analyser::is_character(char c) -> bool {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

auto Analyser::read_k(const char *p) -> void {
  std::string temp;
  std::ifstream in(p);
  if (!in.is_open()) {
    throw std::runtime_error(std::string(p) + "：文件未打开");
  }
  while (!in.eof()) {
    std::getline(in, temp);
    std::regex r(R"(([a-z\*&]+)( *, *)(\d+))");
    std::smatch sm;
    std::regex_match(temp, sm, r);
    this->k.insert({sm[1], std::stoi(sm[3])});
  }
  in.close();
}

auto Analyser::read_p(const char *p) -> void {
  std::ifstream in(p);
  std::string temp;
  if (!in.is_open()) {
    throw std::runtime_error(std::string(p) + "：文件未打开");
  }
  while (!in.eof()) {
    std::getline(in, temp);
    std::regex r(R"((.)( *, *)(\d+))");
    std::smatch sm;
    std::regex_match(temp, sm, r);
    this->p.insert({sm[1], std::stoi(sm[3])});
  }
  in.close();
}

auto Analyser::sub_program1(std::string::iterator &iter,
                            std::string::iterator &end)
    -> std::pair<std::string, std::pair<std::string, int>> {
  std::string temp;
  while (this->is_character(*iter) || this->is_number(*iter) || *iter == '_') {
    temp.push_back(*iter);
    if (++iter == end) {
      break;
    }
  }

  std::map<std::string, int>::iterator pos;
  std::pair<std::string, int> p_;

  if ((pos = this->k.find(temp)) != this->k.end()) {
    p_ = {"关键字", pos->second};
  } else if ((pos = this->i.find(temp)) != this->i.end()) {
    p_ = {"标识符", pos->second};
  } else {
    p_ = {"标识符", this->i.size() + 1};
    this->i.insert({temp, p_.second});
  }
  return {temp, {p_.first, p_.second}};
}
//------------------------------------------
auto Analyser::sub_program2(std::string::iterator &iter,
                            std::string::iterator &end)
    -> std::pair<std::string, std::pair<std::string, int>> {
  std::string temp;
  // char q = *iter;
  while (this->p.count(std::string(1, *iter)) == 0 &&
         this->arit.count(std::string(1, *iter)) == 0 &&
         this->rela.count(std::string(1, *iter)) == 0 && *iter != ' ') {
    temp.push_back(*iter);
    if (++iter == end) {
      break;
    }
  }
  auto pos = this->c.find(temp);
  bool error = false;
  int id = 0;

  if (std::count(temp.begin(), temp.end(), '.') > 1) {
    error = true;
  }
  for (auto e : temp) {
    if (this->is_character(e)) {
      error = true;
      break;
    }
  }
  if (error) {
    return {temp, {"常量", 0}};
  }

  if (pos != this->c.end()) {
    id = pos->second;
  } else {
    this->c.insert({temp, this->c.size() + 1});
    id = static_cast<int>(this->c.size());
  }
  return {temp, {"常量", id}};
}

//----------------------------------------
auto Analyser::sub_program3(std::string::iterator &iter,
                            std::string::iterator &end)
    -> std::pair<std::string, std::pair<std::string, int>> {
  std::string temp;
  std::map<std::string, int>::const_iterator pos;
  if (this->arit.find(std::string(1, *iter)) != this->arit.end()) {
    while (this->arit.find(std::string(1, *iter)) != this->arit.end() &&
           iter != end) {
      temp.push_back(*iter);
      iter++;
    }
    if ((pos = this->arit.find(temp)) != this->arit.end()) {
      return {temp, {"算术运算符", pos->second}};
    }
    return {temp, {"", 0}};
  }
  if (this->rela.find(std::string(1, *iter)) != this->rela.end()) {
    while (this->rela.find(std::string(1, *iter)) != this->rela.end() &&
           iter != end) {
      temp.push_back(*iter);
      iter++;
    }
    if ((pos = this->rela.find(temp)) != this->rela.end()) {
      return {temp, {"关系运算符", pos->second}};
    }
    return {temp, {"", 0}};
  }
  if ((pos = this->p.find(std::string(1, *iter))) != this->p.end()) {
    iter++;
    return {pos->first, {"界符", pos->second}};
  }
  char c = *iter;
  iter++;
  return {std::string(1, c), {"界符", 0}};
}

//----------------------------------------
auto Analyser::analyse(char const *p) -> void {
  std::string line;
  int rows = 0;
  int clumns = 1;
  std::string::iterator iter;
  std::string::iterator end;
  std::ifstream in(p);
  if (!in.is_open()) {
    throw std::runtime_error(std::string(p) + "：文件未打开");
  }
  while (!in.eof()) {
    std::getline(in, line);
    rows++;
    iter = line.begin();
    end = line.end();
    while (iter != end) {
      if (*iter == ' ') {
        iter++;
        continue;
      }
      //用于跳过注释
      if (*iter == '/' && iter + 1 != end) {
        if (*(iter + 1) == '/') {
          break;
        }
      }
      if (this->is_character(*iter)) {
        this->print(this->sub_program1(iter, end), rows, clumns);
      } else if (this->is_number(*iter)) {
        this->print(this->sub_program2(iter, end), rows, clumns);
      } else {
        this->print(this->sub_program3(iter, end), rows, clumns);
      }
      clumns++;
    }
    clumns = 1;
  }
  in.close();
}
