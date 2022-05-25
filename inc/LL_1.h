#pragma once
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
//
class LL1 {
private:
  std::map<char, std::set<char>> first;    // first集
  std::map<char, std::set<char>> follow;   // follow集
  std::map<char, std::set<std::string>> G; // 文法
  // std::set<char> vt; // 终结符
  std::set<char> vn; // 非终结符

public:
  auto getfollow() -> void;

  auto getfirst(char c) -> std::set<char>;
  /*
  功能：从文件中读取文法
  输入：文件路径
  异常：抛出文件路径错误的异常
   */
  auto reader(std::string const &path) noexcept(false) -> void;

  void test() {
    for (auto &e : this->G) {
      std::cout << e.first << std::endl;
      for (const auto &a : e.second) {
        std::cout << a << "  ";
      }
      std::cout << "\n\n\n\n";
    }
  }
};
