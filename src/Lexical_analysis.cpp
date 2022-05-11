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

// auto Analyser::fun() -> void {}
auto Analyser::is_number(char c) -> bool { return (c >= '0' && c <= '9'); }
auto Analyser::is_character(char c) -> bool {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

auto Analyser::readline(char const *p, std::string &str) -> bool {
  if (!in.is_open()) {
    in.open(p);
    if (!this->in.is_open()) {
      throw std::runtime_error("\"" + std::string(p) + "\" not found");
    }
  }
  if (this->in.eof()) {
    return false;
  }
  std::getline(this->in, str);
  return true;
}

auto Analyser::read_k(const char *p) -> void {

  try {
    std::string temp;
    while (this->readline(p, temp)) {
      std::regex r(R"(([a-zA-Z0-9\+\-\*/<>=&*]+)( *, *)(\d+))");
      std::smatch sm;
      std::regex_match(temp, sm, r);
      this->k.insert({sm[1], std::stoi(sm[3])});
    }
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  this->in.close();
}

auto Analyser::read_p(const char *p) -> void {
  try {
    std::string temp;
    while (this->readline(p, temp)) {
      std::regex r(R"(([\[\]\(\),;\{\}]+)( *, *)(\d+))");
      std::smatch sm;
      std::regex_match(temp, sm, r);
      this->p.insert({sm[1], std::stoi(sm[3])});
    }

  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  this->in.close();
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
    p_ = {"keword", pos->second};
  } else if ((pos = this->i.find(temp)) != this->i.end()) {
    p_ = {"identifier", pos->second};
  } else {
    p_ = {"identifier", this->i.size() + 1};
    this->i.insert({temp, p_.second});
  }
  return {temp, {p_.first, p_.second}};
}
//------------------------------------------
auto Analyser::sub_program2(std::string::iterator &iter,
                            std::string::iterator &end)
    -> std::pair<std::string, int> {
  std::string temp;
  // char q = *iter;
  while (this->p.find(std::string(1, *iter)) == this->p.end() &&
         this->arit.find(std::string(1, *iter)) == this->arit.end() &&
         this->rela.find(std::string(1, *iter)) == this->rela.end() &&
         *iter != ' '&&*iter!='\"') {
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
    }
  }
  if (error) {
    return {temp, 0};
  }

  if (pos != this->c.end()) {
    id = pos->second;
  } else {
    this->c.insert({temp, this->c.size() + 1});
    id = static_cast<int>(this->c.size());
  }
  return {temp, id};
} //----------------------------------------
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
      return {temp, {"arithmetic operator", pos->second}};
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
      return {temp, {"relational operator", pos->second}};
    }
    return {temp, {"", 0}};
  }
  // std::cout << std::string(1, *iter);
  if ((pos = this->p.find(std::string(1, *iter))) != this->p.end()) {
    iter++;
    return {pos->first, {"delimiter", pos->second}};
  }
  char c = *iter;
  iter++;
  return {std::string(1, c), {"", 0}};
}
//----------------------------------------
auto Analyser::analyse(char const *p) -> void {
  std::string line;
  int rows = 0;
  int clumns = 1;
  std::string::iterator iter;
  std::string::iterator end;
  std::cout.fill(' ');
  try {
    while (this->readline(p, line)) {
      rows++;
      iter = line.begin();
      end = line.end();
      while (iter != end) {
        if (*iter == ' ') {
          iter++;
          continue;
        }
        if (this->is_character(*iter)) {
          auto s = this->sub_program1(iter, end);

          std::cout << std::left << std::setw(25) << s.first << std::setw(25)
                    << std::string("(" + std::to_string(s.second.second) + "," +
                                   s.first + ")")
                    << std::setw(25) << s.second.first << "(" << rows << ","
                    << clumns << ")" << std::endl;
        } else if (this->is_number(*iter)) {
          auto s = this->sub_program2(iter, end);
          std::cout << std::left << std::setw(25) << s.first << std::setw(25)
                    << (s.second == 0
                            ? "Error"
                            : std::string("(" + std::to_string(s.second) + "," +
                                          s.first + ")"))
                    << std::setw(25) << (s.second == 0 ? "Error" : "constans")
                    << "(" << rows << "," << clumns << ")" << std::endl;
        } else {
          auto s = this->sub_program3(iter, end);
          std::cout << std::left << std::setw(25) << s.first << std::setw(25)
                    << (s.second.second == 0
                            ? "Error"
                            : std::string("(" +
                                          std::to_string(s.second.second) +
                                          "," + s.first + ")"))
                    << std::setw(25)
                    << (s.second.second == 0 ? "Error" : s.second.first) << "("
                    << rows << "," << clumns << ")" << std::endl;
        }
        clumns++;
      }
      clumns = 1;
    }
  } catch (std::exception &e) {
    std::cout << e.what();
  }
  this->in.close();
}