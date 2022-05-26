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
    //文件未打开则抛出异常
    throw std::runtime_error(path + ":路径错误\n");
  }
  std::string line;   //文件行
  std::string temp;   //存放识别的推导式
  std::set<char> all; //存放所有识别的字符
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
      all.insert(*iter);
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

  //全字符中删除'|'
  all.erase('|');
  all.erase('@');
  //终结符就是全字符与非终结符的差集
  std::set_difference(all.begin(), all.end(), this->vn.begin(), this->vn.end(),
                      std::inserter(this->vt, this->vt.begin()));
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
  std::set<char> temp;
  //遍历A的产生式
  for (auto const &E : this->G.at(A)) {
    //遍历产生式的字符
    for (auto const &B : E) {
      //跳过终结符
      if (this->vn.count(B) == 0) {
        continue;
      }
      //如果满足A->aB
      if (E.find(B) == E.length() - 1) {
        // A的follow插入B的follow

        this->follow.at(B).insert(this->follow.at(A).begin(),
                                  this->follow.at(A).end());
        break;
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
      //否则，如果含有b->@(空字)
      if (this->G.at(E.at(E.find(B) + 1)).count("@") != 0) {
        // A的follow插入B的follow
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
  // E为非终结符对应所有的推导式
  for (auto &E : this->G) {
    // e为推导式
    for (auto const &e : E.second) {
      //遍历E对应的文法表所在行的每一列
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
  this->output("产生式", "符号栈", "输入串", i);
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