#pragma once

#include <string>
#include <utility>
#include <vector>
struct type {        /*产生式类型定义      */
  char origin;       /*产生式左侧字符 大写字符  */
  std::string array; /*产生式右边字符 */
  int length;        /*字符个数      */
  explicit type(char c = 'N', std::string str = "")
      : origin(c), array(std::move(str)),
        length(static_cast<int>(this->array.length())) {}
};

auto print(char p1[], char p2[]) -> void;