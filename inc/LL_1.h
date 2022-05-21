#pragma once
#include <map>
#include <set>
//
using CS = std::map<char, std::set<char>>;
//
class LL1 {
private:
  CS first;          // first��
  CS follow;         // follow��
  CS G;              //�ķ�
  std::set<char> vt; //�ս��
  std::set<char> vn; //���ս��

public:
  auto G_reader() -> void;
};
