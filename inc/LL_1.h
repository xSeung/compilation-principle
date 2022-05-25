#pragma once
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <set>
#include <stack>
#include <string>
//
class LL1 {
private:
  char s{0};                                         //文法开始符号
  std::map<char, std::set<char>> first;              // first集
  std::map<char, std::set<char>> follow;             // follow集
  std::map<char, std::set<std::string>> G;           // 文法
  std::set<char> vt;                                 // 终结符
  std::set<char> vn;                                 // 非终结符
  std::map<char, std::map<char, std::string>> table; //分析表
  /*
  功能：从c开始向下计算各非终结符的first集
  输入：文法非终结符
  */
  auto sub_getfirst(char c) -> std::set<char>;

  auto sub_getfollow(char A) -> std::set<char>;
  auto mulfirst(std::string const &str) -> std::set<char>;

public:
  auto table_creater() -> void;
  inline auto getfollow() -> void {
    for (auto const &e : this->vn) {
      this->follow.insert({e, {}});
    }
    int len = static_cast<int>(this->vn.size());
    int *p = new int[len]{0};
    int i{};
    this->follow.at(this->s).insert('#');
    while (true) {
      i = 0;
      bool temp = true;
      for (auto iter = this->follow.begin(); iter != this->follow.end();
           iter++, i++) {
        if (p[i] != iter->second.size()) {
          p[i] = static_cast<int>(iter->second.size());
          temp = false;
        }
      }
      if (temp) {
        break;
      }
      for (auto const &e : this->vn) {
        this->sub_getfollow(e);
      }
    }
    std::cout << std::endl;
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
  auto tout() -> void;
  void output(std::string const &css, std::string const &S,
              std::string const &str, int i) const;
  auto analyse(std::string &str) -> void;
};
