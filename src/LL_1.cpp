#include "LL_1.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>


auto LL1::reader(const std::string &path) noexcept(false) -> void {
  std::ifstream in(path);
  if (!in.is_open()) {
    //�ļ�δ�����׳��쳣
    throw std::runtime_error(path + ":·������\n");
  }
  std::string line;   //�ļ���
  std::string temp;   //���ʶ����Ƶ�ʽ
  std::set<char> all; //�������ʶ����ַ�
  char V{};
  while (!in.eof()) {
    //���ж�ȡ
    std::getline(in, line);
    if (this->s == 0) {
      s = line.at(0);
    }
    // vΪ�����ַ� Ϊ���ս��
    V = line.at(0);
    // V������ս����
    this->vn.insert(V);
    // V�����ķ��ֵ�
    this->G.insert({V, {}});
    //����V���Ƶ�
    for (auto iter = line.begin() + 3; iter < line.end(); iter++) {
      temp.push_back(*iter);
      all.insert(*iter);
      if (*iter == '|' || iter + 1 == line.end()) {
        //ɾ���Ƶ�ʽ�е�'|'
        if (*iter == '|') {
          temp.pop_back();
        }
        this->G.at(V).insert(temp);
        temp.clear();
      }
    }
  }

  //ȫ�ַ���ɾ��'|'
  all.erase('|');
  all.erase('@');
  //�ս������ȫ�ַ�����ս���Ĳ
  std::set_difference(all.begin(), all.end(), this->vn.begin(), this->vn.end(),
                      std::inserter(this->vt, this->vt.begin()));
}

auto LL1::sub_getfirst(char c) -> std::set<char> {
  if (this->vn.count(c) == 0) {
    return {c};
  }
  //��first������c��������ֱ�ӷ���c��first��
  if (this->first.count(c) != 0) {
    return this->first.at(c);
  }
  //��������������������first���м���c����������ʼ��c����first��
  this->first.insert({c, {}});
  std::set<char> temp;

  //����c���Ƶ�ʽE
  for (auto const &E : this->G.at(c)) {
    //�����Ƶ�ʽ�е�ÿ���ַ�e
    for (auto const &e : E) {
      //���e���ս����ֱ�ӽ������c��first��
      if (this->vn.count(e) == 0) {
        this->first.at(c).insert(e);
        break;
      }
      //���򣬻�ȡe��first��
      temp = this->sub_getfirst(e);
      //���ҽ���eΪ����ʽE��β�ַ�ʱ����ɾ������@
      if (E.find(e) != E.length() - 1) {
        temp.erase('@');
      }
      //��e��first������c��first��
      this->first.at(c).insert(temp.begin(), temp.end());
      //���e����ʽû�п���@�����˳���E�ķ���
      if (this->G.at(e).count("@") == 0) {
        break;
      }
    }
  }
  return this->first.at(c);
}

auto LL1::sub_getfollow(char A) -> std::set<char> {
  std::set<char> temp;
  //����A�Ĳ���ʽ
  for (auto const &E : this->G.at(A)) {
    //��������ʽ���ַ�
    for (auto const &B : E) {
      //�����ս��
      if (this->vn.count(B) == 0) {
        continue;
      }
      //�������A->aB
      if (E.find(B) == E.length() - 1) {
        // A��follow����B��follow

        this->follow.at(B).insert(this->follow.at(A).begin(),
                                  this->follow.at(A).end());
        break;
      }
      //������A->aBb
      //��ȡb��first
      temp = this->sub_getfirst(E.at(E.find(B) + 1));
      //ȥ������@
      temp.erase('@');
      // b��first����B��follow
      this->follow.at(B).insert(temp.begin(), temp.end());
      // bΪ�ս����������һ��ѭ��
      if (this->vn.count(E.at(E.find(B) + 1)) == 0) {
        continue;
      }
      //�����������b->@(����)
      if (this->G.at(E.at(E.find(B) + 1)).count("@") != 0) {
        // A��follow����B��follow
        this->follow.at(B).insert(this->follow.at(A).begin(),
                                  this->follow.at(A).end());
      }
    }
  }
  return this->follow.at(A);
}

auto LL1::mulfirst(std::string const &str) -> std::set<char> {
  std::set<char> temp1;
  std::set<char> temp2;

  for (auto const &e : str) {
    temp1 = this->sub_getfirst(e);
    temp2.insert(temp1.begin(), temp1.end());
    if (temp1.count('@') == 0) {
      break;
    }
  }
  return temp2;
}

auto LL1::table_creater() -> void {
  for (auto const &E : this->vn) {
    this->table.insert({E, {}});
    for (auto const &e : this->vt) {
      this->table.at(E).insert({e, {}});
    }
    this->table.at(E).insert({'#', {}});
  }
  // EΪ���ս����Ӧ���е��Ƶ�ʽ
  for (auto &E : this->G) {
    // eΪ�Ƶ�ʽ
    for (auto const &e : E.second) {
      //����E��Ӧ���ķ��������е�ÿһ��
      for (auto &ee : this->table.at(E.first)) {
        if (this->mulfirst(e).count(ee.first) != 0) {
          ee.second = e;
        }
        if (this->mulfirst(e).count('@') != 0) {
          for (auto eee : this->follow.at(E.first)) {
            this->table.at(E.first).at(eee) = e;
          }
        }
      }
    }
  }
  for (auto &E : this->table) {
    for (auto &e : E.second) {
      if (e.second.empty()) {
        e.second = "Error";
      }
    }
  }
}

auto LL1::analyse(std::string &str) -> void {
  std::string S("#");
  S.push_back(this->s);
  char temp{};
  int i = 0;
  this->output("����ʽ", "����ջ", "���봮", i);
  this->output("", S, str, i++);
  while (true) {

    temp = S.at(S.length() - 1);

    if (temp == str.at(0)) {
      if (temp == '#') {
        this->output("", S, str, i++);
        break;
      }
      str.erase(str.begin());
      S.pop_back();
      this->output("", S, str, i++);
      continue;
    }

    if (this->vn.count(str.at(0)) == 0 && this->vt.count(str.at(0)) == 0 &&
        str.at(0) != '#') {
      this->output(/*std::string(temp, 1) + "->"*/ "Error", S, str, i++);
      break;
    }
    auto const &m = this->table.at(temp).at(str.at(0));
    S.pop_back();
    if (m == "Error") {
      this->output(/*std::string(temp, 1) + "->"*/ m, S, str, i++);
      break;
    }
    // S.pop_back();
    if (m != "@") {
      S += std::string(m.rbegin(), m.rend());
    }
    this->output(/*std::string(temp, 1) + "->"*/ m, S, str, i++);
  }
}

void LL1::output(std::string const &css, std::string const &S,
                 std::string const &str, int i) const {
  std::cout << std::setw(3) << i << std::setw(30) << S << std::setw(30) << str
            << std::setw(30) << css << std::endl;
}

auto LL1::tout() -> void {
  std::cout << std::setw(15) << " ";
  for (auto const &e : this->vt) {
    std::cout << std::setw(15) << e;
  }
  std::cout << std::setw(15) << '#' << std::endl;
  for (auto const &E : this->table) {
    std::cout << std::setw(15) << E.first;
    for (auto const &e : E.second) {
      std::cout << std::setw(15) << e.second;
    }
    std::cout << std::endl;
  }
}