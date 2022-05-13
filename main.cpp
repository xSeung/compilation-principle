#include "Lexical_analysis.h"
#include <iomanip>
#include <iostream>
#include <string>
auto main(int  /*argc*/, char ** /*argv*/) -> int {
  Analyser a;
  int ac = 0;
  a.read_k("./k_table");
  a.read_p("./p_table");
  a.analyse("./test2");
}