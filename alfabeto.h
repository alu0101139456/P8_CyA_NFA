

#pragma once

#include <iostream>
#include "set.h"
#include <fstream>
#include <string>


class Alphabet {
 private:
  Set alfa_;

 public:

  Alphabet();
  ~Alphabet() {}
  Alphabet( const Alphabet& rhs);

  void InsertSymbol(char);
  void InsertAlphabetFromFile();
  void InsertAlphabetACII();
  bool FindSymbol(char);
  bool IsInAlphabeth(std::string);

  std::string PrintAlphabet();
  
  Alphabet& operator=(const Alphabet& rhs);

};