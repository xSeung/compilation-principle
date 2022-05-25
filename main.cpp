//#include "Lexical_analysis.h"
#include "LL_1.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

auto main(int /*argc*/, char ** /*argv*/) -> int {
  LL1 a;
  try {
    a.reader("../../data/2/1.txt");

  } catch (std::exception &e) {
    std::cout << e.what();
    std::exit(1);
  }
  // a.test();

  return 0;
}
