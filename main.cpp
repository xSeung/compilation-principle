//#include "Lexical_analysis.h"
#include "LL_1.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

auto main(int argc, char **argv) -> int {
  LL1 a;
  try {
    a.reader("../../data/2/1.txt");
  } catch (std::exception &e) {
    std::cout << e.what();
    std::exit(1);
  }
  //std::string aaa;
  int cc{};
  a.getfirst();
  a.getfollow();
  a.table_creater();
  a.tout();
  std::string b(argv[argc - 1]);
  a.analyse(b);
  return 0;
}
