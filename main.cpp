/*
 * @Author: FXS fengxusheng1014@163.com
 * @Date: 2022-06-09 00:14:24
 * @LastEditors: FXS fengxusheng1014@163.com
 * @LastEditTime: 2022-06-13 20:13:30
 * @FilePath: \BY.cpp\main.cpp
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴����
 * ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#define LA
#ifdef LL_1
#include "LL_1.h"
#endif
#ifdef LA
#include "Lexical_analysis.h"
#endif
#ifdef LR_1
#include "LR_1.h"
#endif
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

auto main(int argc, char **argv) -> int {
#ifdef LA
  Analyser a;
  try {
    //��ȡK��
    a.read_k(R"(..\1\k_table)");
    //��ȡP��
    a.read_p(R"(..\1\p_table)");
    //����
    a.analyse(argv[argc - 1]);
  } catch (std::exception const &e) {
    std::cout << e.what() << std::endl;
    std::quick_exit(1);
  }
#endif

#ifdef LL_1
  //#define LL_1
  LL1 a;
  try {
    a.reader("../2/1.txt");
  } catch (std::exception &e) {
    std::cout << e.what();
    std::quick_exit(1);
  }

  std::string b(argv[argc - 1]);

  if (b.back() != '#') {
    std::cout << "������û��β��#" << std::endl;
    std::quick_exit(1);
  }
  a.analyse(b);
#endif

#ifdef LR_1
  LR1 a;
  a.init();
  std::string s(argv[argc - 1]);
  s += '#';
  a.fun(s);
#endif

  return 0;
}