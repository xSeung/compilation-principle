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
    //文件未打开则抛出异常
    throw std::runtime_error(path + ":路径错误\n");
  }
  std::string line; //文件行
  std::string temp; //存放识别的推导式
  // std::set<char> all; //存放所有识别的字符
  char V{};
  while (!in.eof()) {
    //逐行读取
    std::getline(in, line);
    if (this->s == 0) {
      s = line.at(0);
    }
    // v为行首字符 为非终结符
    V = line.at(0);
    // V加入非终结符表
    this->vn.insert(V);
    // V加入文法字典
    this->G.insert({V, {}});
    //分析V的推导
    for (auto iter = line.begin() + 3; iter < line.end(); iter++) {
      temp.push_back(*iter);
      // all.insert(*iter);
      if (*iter == '|' || iter + 1 == line.end()) {
        //删除推导式中的'|'
        if (*iter == '|') {
          temp.pop_back();
        }
        this->G.at(V).insert(temp);
        temp.clear();
      }
    }
  }

  // //全字符中删除'|'
  // all.erase('|');
  // //终结符就是全字符与非终结符的差集
  // std::set_difference(all.begin(), all.end(), this->vn.begin(),
  // this->vn.end(), std::inserter(this->vt, this->vt.begin()));
}

auto LL1::sub_getfirst(char c) -> std::set<char> {
  if (this->vn.count(c) == 0) {
    return {c};
  }
  //若first集存在c的索引，直接返回c的first集
  if (this->first.count(c) != 0) {
    return this->first.at(c);
  }
  //上述条件不成立，则在first集中加入c的索引，开始对c构造first集
  this->first.insert({c, {}});
  std::set<char> temp;

  //遍历c的推导式E
  for (auto const &E : this->G.at(c)) {
    //遍历推导式中的每个字符e
    for (auto const &e : E) {
      //如果e是终结符，直接将其加入c的first集
      if (this->vn.count(e) == 0) {
        this->first.at(c).insert(e);
        break;
      }
      //否则，获取e的first集
      temp = this->sub_getfirst(e);
      //当且仅当e为产生式E的尾字符时，不删除空字@
      if (E.find(e) != E.length() - 1) {
        temp.erase('@');
      }
      //将e的first集插入c的first集
      this->first.at(c).insert(temp.begin(), temp.end());
      //如果e产生式没有空字@，则退出此E的分析
      if (this->G.at(e).count("@") == 0) {
        break;
      }
    }
  }
  return this->first.at(c);
}

auto LL1::sub_getfollow(char A) -> std::set<char> {
  // follow存在c的索引
  if (this->follow.count(A) != 0) {
    //直接返回c的follow集
    return this->follow.at(A);
  }
  //创建A的follow集
  this->follow.insert({A, {}});
  std::set<char> temp;
  //遍历c的产生式
  for (auto const &E : this->G.at(A)) {

    //遍历产生式的字符
    for (auto const &B : E) {
      //跳过终结符
      if (this->vn.count(B) == 0) {
        continue;
      }
      //如果满足A->aB
      this->sub_getfollow(B);
      if (E.find(B) == E.length() - 1) {
        // A的follow插入B的follow
        this->follow.at(B).insert(this->follow.at(A).begin(),
                                  this->follow.at(A).end());
        break;

        // this->follow.insert(e, {});
      }
      //若满足A->aBb
      //获取b的first
      temp = this->sub_getfirst(E.at(E.find(B) + 1));
      //去除空字@
      temp.erase('@');
      // b的first插入B的follow
      this->follow.at(B).insert(temp.begin(), temp.end());
      // b为终结符，进入下一个循环
      if (this->vn.count(E.at(E.find(B) + 1)) == 0) {
        continue;
      }
      //如果含有b->@
      if (this->G.at(E.at(E.find(B) + 1)).count("@") != 0) {
        // A的follow插入B的follow
        this->follow.at(B).insert(this->follow.at(A).begin(),
                                  this->follow.at(A).end());
      }
    }
  }
  return this->follow.at(A);
}