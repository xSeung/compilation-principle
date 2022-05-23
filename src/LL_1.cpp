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
    throw std::runtime_error(path + ":路径错误");
  }
  std::string line;   //文件行
  std::string temp;   //存放识别的推导式
  std::set<char> all; //存放所有识别的字符
  char V{};
  while (!in.eof()) {
    //逐行读取
    std::getline(in, line);
    // v为行首字符 为非终结符
    V = line.at(0);
    // V加入非终结符表
    this->vn.insert(V);
    // V加入文法字典
    this->G.insert({V, {}});
    //分析V的推导
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
  //全字符中删除'|'
  all.erase('|');
  //终结符就是全字符与非终结符的差集
  std::set_difference(all.begin(), all.end(), this->vn.begin(), this->vn.end(),
                      std::inserter(this->vt, this->vt.begin()));
}

auto LL1::getfirst() -> void {
}
