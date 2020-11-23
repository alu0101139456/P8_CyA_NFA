/**
 * @file main.cc
 * @author Ángel Julián Bolaño Campos (alu0101139456@ull.edu.es)
 * @brief Práctica 8: Autómatas Finitos No Deterministas
 * @version 0.1
 * @date 2020-11-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include "nfa.h"

void Help(std::string);
void OptionDefault();

int main(int argc, char* argv[]) {
  
  Nfa nfa;

  switch (argc) {
    case 2:
        Help(argv[1]);
      break;
    case 3:
        nfa.InsertFiles(argv[1], argv[2], "output.txt");
      break;
    case 4:
        nfa.InsertFiles(argv[1], argv[2], argv[3]);
      break;
    default:
        OptionDefault();
      break;
  }
}


void Help(std::string hlp) {
  if( hlp == "--help") {
    system("clear");
    system("cat help.txt");
  } else {
    std::cout << "Sintaxis erronea" << std::endl;
    OptionDefault();
  }
  
}

void OptionDefault() {
  std::cout << "Modo de empleo: ./nfa_simulation input.nfa input.txt output.txt" << std::endl;
  std::cout << "Pruebe 'nfa_simulation --help' para más información." << std::endl;
}