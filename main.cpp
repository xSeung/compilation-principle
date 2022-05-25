//#include "Lexical_analysis.h"
#include "LL_1.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <set>
#include <string>

auto main(int argc, char **argv) -> int {
  LL1 a;
  try {
    a.reader("../../data/2/1.txt");
  } catch (std::exception &e) {
    std::cout << e.what();
    std::exit(1);
  }
  a.getfirst();
  a.getfollow();
  a.table_creater();
  a.tout();
  std::string b(argv[argc - 1]);
  a.analyse(b);
  // a.output("std::string css", "std::string S", "std::string str", 1);
  return 0;
}
