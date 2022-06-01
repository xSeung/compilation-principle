#include "LR_1.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void LR1::init() {
  std::ifstream in(R"(F:\Code\VSCode\BY.cpp\data\3\1.txt)");
  if (!in.is_open()) {
    std::exit(1);
  }
  for (int i = 0; i < sNum; ++i) {
    for (int j = 1; j <= tNum + nNum; ++j) {
      in >> table.at(i).at(j);
    }
  }
}

void LR1::fun(std::string &str) {
  std::cout << "       步骤   状态栈     符号栈     输入串     动作说明"
            << std::endl;
  int i = 1; // i记录步骤
  int s = 0; // s为当前状

  aStack.push_back('#');
  std::string outStack; // outStack存储状态栈内容
  sStack.push_back(0);

  while (table.at(sStack.back()).at(tSet.at(str.at((0)))) != "acc") {
    std::string tableContent = table.at(sStack.back()).at(tSet.at(str.at(0)));
    if (tableContent == "_") {
      std::cout << "出错" << std::endl;
      std::cout << str << "为非法符号串" << std::endl;
      return;
    }
    //获取状态
    s = std::stoi(tableContent.data() + 1);
    //如果是移进
    if (tableContent.at(0) == 's') {
      outStack.clear();

      for (int i : sStack) {
        outStack += std::to_string(i);
      }
      std::cout << std::setw(10) << i << std::setw(10) << outStack
                << std::setw(10) << std::string(aStack.begin(), aStack.end())
                << std::setw(10) << str << std::setw(10) << "        ACTION["
                << sStack.back() << "," << str.at(0) << "]=S" << s << ","
                << "状态" << s << "入栈" << std::endl;
      aStack.push_back(str.at(0));
      sStack.push_back(s);
      str.erase(str.begin(), str.begin() + 1);
    }
    //如果是归约
    else if (tableContent.at(0) == 'r') {
      outStack.clear();
      for (int i : sStack) {
        outStack += std::to_string(i);
      }
      std::cout << std::setw(10) << i << std::setw(10) << outStack
                << std::setw(10) << std::string(aStack.begin(), aStack.end())
                << std::setw(10) << str;
      //获取产生式
      std::string mygeneratice = g.at(s);
      //符号栈和状态栈出栈
      for (int i = 0; i < g.at(s).length() - 3; i++) {
        aStack.pop_back();
        sStack.pop_back();
      }
      std::string oldstate = std::to_string(sStack.back());
      //入栈栈变动
      aStack.push_back(mygeneratice[0]);
      sStack.push_back(
          std::stoi(table.at(sStack.back()).at(nSet[mygeneratice[0]] + tNum)));
      std::cout << std::setw(10) << tableContent << ":" << mygeneratice
                << "归约,GOTO(" << oldstate << "," << mygeneratice.at(0)
                << ")=" << s << "入栈" << std::endl;
    }
    i++;
  }

  outStack.clear();
  for (int i : sStack) {
    outStack += std::to_string(i);
  }

  std::cout << std::setw(10) << i << std::setw(10) << outStack << std::setw(10)
            << std::string(aStack.begin(), aStack.end()) << std::setw(10) << str
            << "        ACC";
}