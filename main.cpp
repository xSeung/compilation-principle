#include <iterator>
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
    a.read_k(R"(D:\Dev\VSCode\BY.cpp\data\1\k_table)");
    a.read_p(R"(D:\Dev\VSCode\BY.cpp\data\1\p_table)");
  } catch (std::exception const &e) {
    std::cout << e.what() << std::endl;
    std::quick_exit(1);
  }
  a.analyse(argv[argc - 1]);
#endif

#ifdef LL_1
  //#define LL_1
  LL1 a;
  try {
    a.reader("../../data/2/1.txt");
  } catch (std::exception &e) {
    std::cout << e.what();
    std::exit(-1);
  }
  std::string b(argv[argc - 1]);
  if (b.back() != '#') {
    std::cout << "������û��β��#" << std::endl;
    std::exit(-1);
  }
  a.analyse(b);
#endif

#ifdef LR_1
  LR1 a;
  a.init();
  std::string s(argv[argc - 1]);
  std::cout << "������Ҫ�������ַ�����";
  s += '#';
  a.fun(s);
#endif

  return 0;
}