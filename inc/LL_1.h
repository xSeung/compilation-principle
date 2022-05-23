#pragma once
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
//
using CS = std::map<char, std::set<std::string>>;
//
class LL1 {
private:
  CS first;          // first��
  CS follow;         // follow��
  CS G;              // �ķ�
  std::set<char> vt; // �ս��
  std::set<char> vn; // ���ս��

public:
  auto getfollow() -> void;
  auto getfirst() -> void;
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
