#pragma once
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
//
class LL1 {
private:
  char s{0};                               //文法开始符号
  std::map<char, std::set<char>> first;    // first集
  std::map<char, std::set<char>> follow;   // follow集
  std::map<char, std::set<std::string>> G; // 文法
  // std::set<char> vt; // 终结符
  std::set<char> vn; // 非终结符
  /*
  功能：从c开始向下计算各非终结符的first集
  输入：文法非终结符
  */
  auto sub_getfirst(char c) -> std::set<char>;

  auto sub_getfollow(char A) -> std::set<char>;

public:
  inline auto getfollow() -> void {
    for (auto const &e : this->vn) {
      this->follow.insert({e, {}});
    }
    this->follow.at(this->s).insert('#');
  };

  inline auto getfirst() -> void {

    for (auto const &e : this->vn) {
      this->sub_getfirst(e);
    }
  };
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
