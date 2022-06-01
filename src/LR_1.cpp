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
  std::cout << "       ����   ״̬ջ     ����ջ     ���봮     ����˵��"
            << std::endl;
  int i = 1; // i��¼����
  int s = 0; // sΪ��ǰ״

  aStack.push_back('#');
  std::string outStack; // outStack�洢״̬ջ����
  sStack.push_back(0);

  while (table.at(sStack.back()).at(tSet.at(str.at((0)))) != "acc") {
    std::string tableContent = table.at(sStack.back()).at(tSet.at(str.at(0)));
    if (tableContent == "_") {
      std::cout << "����" << std::endl;
      std::cout << str << "Ϊ�Ƿ����Ŵ�" << std::endl;
      return;
    }
    //��ȡ״̬
    s = std::stoi(tableContent.data() + 1);
    //������ƽ�
    if (tableContent.at(0) == 's') {
      outStack.clear();

      for (int i : sStack) {
        outStack += std::to_string(i);
      }
      std::cout << std::setw(10) << i << std::setw(10) << outStack
                << std::setw(10) << std::string(aStack.begin(), aStack.end())
                << std::setw(10) << str << std::setw(10) << "        ACTION["
                << sStack.back() << "," << str.at(0) << "]=S" << s << ","
                << "״̬" << s << "��ջ" << std::endl;
      aStack.push_back(str.at(0));
      sStack.push_back(s);
      str.erase(str.begin(), str.begin() + 1);
    }
    //����ǹ�Լ
    else if (tableContent.at(0) == 'r') {
      outStack.clear();
      for (int i : sStack) {
        outStack += std::to_string(i);
      }
      std::cout << std::setw(10) << i << std::setw(10) << outStack
                << std::setw(10) << std::string(aStack.begin(), aStack.end())
                << std::setw(10) << str;
      //��ȡ����ʽ
      std::string mygeneratice = g.at(s);
      //����ջ��״̬ջ��ջ
      for (int i = 0; i < g.at(s).length() - 3; i++) {
        aStack.pop_back();
        sStack.pop_back();
      }
      std::string oldstate = std::to_string(sStack.back());
      //��ջջ�䶯
      aStack.push_back(mygeneratice[0]);
      sStack.push_back(
          std::stoi(table.at(sStack.back()).at(nSet[mygeneratice[0]] + tNum)));
      std::cout << std::setw(10) << tableContent << ":" << mygeneratice
                << "��Լ,GOTO(" << oldstate << "," << mygeneratice.at(0)
                << ")=" << s << "��ջ" << std::endl;
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