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
    throw std::runtime_error(path + ":·������");
  }
  std::string line;   //�ļ���
  std::string temp;   //���ʶ����Ƶ�ʽ
  std::set<char> all; //�������ʶ����ַ�
  char V{};
  while (!in.eof()) {
    //���ж�ȡ
    std::getline(in, line);
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
        if (*iter == '|') {
          temp.pop_back();
        }
        this->G[V].insert(temp);
        temp.clear();
      }
    }
  }
  //ȫ�ַ���ɾ��'|'
  all.erase('|');
  //�ս������ȫ�ַ�����ս���Ĳ
  std::set_difference(all.begin(), all.end(), this->vn.begin(), this->vn.end(),
                      std::inserter(this->vt, this->vt.begin()));
}

auto LL1::getfirst() -> void {
}
