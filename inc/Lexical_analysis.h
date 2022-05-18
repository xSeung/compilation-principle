#pragma once
#include <fstream>
#include <map>
#include <string>
#include <utility>
class Analyser;

class Analyser {
private:
  std::ifstream in;
  std::map<std::string, int> k;             //关键字表
  std::map<std::string, int> p;             //分界符表
  std::map<std::string, int> c;             //常量表
  std::map<std::string, int> i;             //标识符表
  std::map<std::string, int> const arit = { //算术运算符表
      {"+", 1},  {"-", 2},  {"*", 3},  {"/", 4},   {"++", 5},  {"==", 6},
      {"+=", 7}, {"-=", 8}, {"*=", 9}, {"/=", 10}, {"--", 11}, {"=", 12}};
  std::map<std::string, int> const rela = { //关系运算符表
      {">", 1},
      {"<", 2},
      {">=", 3},
      {"<=", 4},
      {"==", 5}};
  /*逐行读文件
  输入：p文件地址，str读出存放
  返回值：代表文件有没有读成功
  */
  auto readline(char const *p, std::string &str) -> bool;
  auto is_number(char c) -> bool;
  auto is_character(char c) -> bool;
  /*
  输入：
    字符串的迭代器
  返回值：
    三元组：<字符串本身，种类，表内码>
  */
  auto sub_program1(std::string::iterator &iter, std::string::iterator &end)
      -> std::pair<std::string, std::pair<std::string, int>>;
  /*
  输入：
    字符串的迭代器
  返回值：
    二元组：<数字，常量表内码（等于0时为Error）>
  */
  auto sub_program2(std::string::iterator &iter, std::string::iterator &end)
      -> std::pair<std::string, int>;
  /*
  输入：
    字符串的迭代器
  返回值：
    二元组：<符号，种类，表内码（等于0时为Error）>
  */
  auto sub_program3(std::string::iterator &iter, std::string::iterator &end)
      -> std::pair<std::string, std::pair<std::string, int>>;

public:
  Analyser() = default;
  //读k表
  auto read_k(char const *p) -> void;
  //读p表
  auto read_p(char const *p) -> void;
  //调用分析p路径文件的接口
  auto analyse(char const *p) -> void;
};
