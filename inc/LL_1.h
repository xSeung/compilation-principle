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
  char s{0};                                         //�ķ���ʼ����
  std::map<char, std::set<char>> first;              // first��
  std::map<char, std::set<char>> follow;             // follow��
  std::map<char, std::set<std::string>> G;           // �ķ�
  std::set<char> vt;                                 // �ս��
  std::set<char> vn;                                 // ���ս��
  std::map<char, std::map<char, std::string>> table; //������
  /*
  ���ܣ���c��ʼ���¼�������ս����first��
  ���룺�ķ����ս��
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
  ���ܣ����ļ��ж�ȡ�ķ�
  ���룺�ļ�·��
  �쳣���׳��ļ�·��������쳣
   */
  auto reader(std::string const &path) noexcept(false) -> void;
  auto tout() -> void;
  void output(std::string const &css, std::string const &S,
              std::string const &str, int i) const;
  auto analyse(std::string &str) -> void;
};
