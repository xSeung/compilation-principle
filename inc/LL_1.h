#pragma once
#include <map>
#include <set>
//
using CS = std::map<char, std::set<char>>;
//
class LL1 {
private:
  CS first;          // first集
  CS follow;         // follow集
  CS G;              //文法
  std::set<char> vt; //终结符
  std::set<char> vn; //非终结符

public:
  auto G_reader() -> void;
};
