#include "LL_1.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

auto LL1::reader(const std::string &path) noexcept(false) -> void {
  std::ifstream in(path);
  if (!in.is_open()) {
    //�ļ�δ�����׳��쳣
    throw std::runtime_error(path + ":·������\n");
  }
  std::string line; //�ļ���
  std::string temp; //���ʶ����Ƶ�ʽ
  // std::set<char> all; //�������ʶ����ַ�
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
      // all.insert(*iter);
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

  // //ȫ�ַ���ɾ��'|'
  // all.erase('|');
  // //�ս������ȫ�ַ�����ս���Ĳ
  // std::set_difference(all.begin(), all.end(), this->vn.begin(),
  // this->vn.end(), std::inserter(this->vt, this->vt.begin()));
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
  // follow����c������
  if (this->follow.count(A) != 0) {
    //ֱ�ӷ���c��follow��
    return this->follow.at(A);
  }
  //����A��follow��
  this->follow.insert({A, {}});
  std::set<char> temp;
  //����c�Ĳ���ʽ
  for (auto const &E : this->G.at(A)) {

    //��������ʽ���ַ�
    for (auto const &B : E) {
      //�����ս��
      if (this->vn.count(B) == 0) {
        continue;
      }
      //�������A->aB
      this->sub_getfollow(B);
      if (E.find(B) == E.length() - 1) {
        // A��follow����B��follow
        this->follow.at(B).insert(this->follow.at(A).begin(),
                                  this->follow.at(A).end());
        break;

        // this->follow.insert(e, {});
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
      //�������b->@
      if (this->G.at(E.at(E.find(B) + 1)).count("@") != 0) {
        // A��follow����B��follow
        this->follow.at(B).insert(this->follow.at(A).begin(),
                                  this->follow.at(A).end());
      }
    }
  }
  return this->follow.at(A);
}