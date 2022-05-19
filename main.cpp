#include "Lexical_analysis.h"
//#include "LL_1.h"
#include <iomanip>
#include <iostream>
#include <string>
auto main(int argc, char **argv) -> int {
  Analyser a;
  a.read_k("./k_table");
  a.read_p("./p_table");
  // std::cout<<"23 2\n";
  // a.analyse("debug");
  // a.analyse(argv[argc-1]);
  // std::cin.get();
  
  std::cout<<"我的世界";
  return 0;
}
