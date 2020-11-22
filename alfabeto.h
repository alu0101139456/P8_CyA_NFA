/**
 * @file alfabeto.h
 * @author Ángel Julián Bolaño Campos (alu0101139456@ull.edu.es)
 * @brief Práctica 8: Autómatas Finitos No Deterministas
 * @version 0.1
 * @date 2020-11-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <iostream>
#include "set.h"
#include <fstream>
#include <string>

/**
 * @brief 
 * 
 */
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
  bool IsInAlphabeth(char);
  bool IsInAlphabeth(std::string);
  

  std::string PrintAlphabet();
  
  Alphabet& operator=(const Alphabet& rhs);

};