#pragma once
#include <array>
#include <map>
#include <string>
#include <vector>

class LR1 {
private:
  static const int maxSize = 15; //定义分析表的最大大小
  std::array<std::array<std::string, LR1::maxSize>, LR1::maxSize>
      table;     //分析表的具体的内容
  int tNum = 6;  //输入终结符的数量
  int nNum = 3;  //输入非终结符的数量
  int sNum = 12; //输入状态数

  std::map<char, int> tSet{
      {'i', 1}, {'+', 2}, {'*', 3}, {'(', 4},
      {')', 5}, {'#', 6}}; //终结符的集合，用map 映射表示在分析表的第几列

  std::map<char, int> nSet{
      {'E', 1},
      {'T', 2},
      {'F', 3}}; //非终结符的集合，用map 映射表示在分析表的第几行

  std::map<int, std::string> g{{1, "E->E+T"}, {2, "E->T"},
                               {3, "T->T*F"}, {4, "T->F"},
                               {5, "F->(E)"}, {6, "F->i"}}; //产生式集合
  
  std::vector<char> aStack;                                 //分析栈
  std::vector<int> sStack;                                  //状态栈

public:
  void fun(std::string &str); //对输入的语言用LL1预测分析表进行分析
  void init();                //数据分析表初始化
};