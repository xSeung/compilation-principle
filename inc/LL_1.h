#pragma once
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
//
class LL1 {
private:
  char s{0};                               //�ķ���ʼ����
  std::map<char, std::set<char>> first;    // first��
  std::map<char, std::set<char>> follow;   // follow��
  std::map<char, std::set<std::string>> G; // �ķ�
  // std::set<char> vt; // �ս��
  std::set<char> vn; // ���ս��
  /*
  ���ܣ���c��ʼ���¼�������ս����first��
  ���룺�ķ����ս��
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
  ���ܣ����ļ��ж�ȡ�ķ�
  ���룺�ļ�·��
  �쳣���׳��ļ�·��������쳣
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
