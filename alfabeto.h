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
 * @brief Clase Alfabeto
 * 
 */
class Alphabet {
 private:
  Set alfa_;

 public:
/**
 * @brief Construct a new Alphabet object
 * 
 */
  Alphabet();
  /**
   * @brief Destroy the Alphabet object
   * 
   */
  ~Alphabet() {}
  /**
   * @brief Construct of copy of Alphabet object
   * 
   * @param rhs 
   */
  Alphabet( const Alphabet& rhs);

/**
 * @brief Insert symbol in alphabet
 * 
 * @param int because we use int in set
 */
  void InsertSymbol(int);
  /**
   * @brief Insert an alphabet from file
   * 
   */
  void InsertAlphabetFromFile();
  /**
   * @brief Insert the ACII alphabet only
   * 
   */
  void InsertAlphabetACII();
  /**
   * @brief Used to check if the symbol exists in the alphabet
   * 
   * @return true if exist 
   * @return false it don't exist
   */
  bool IsInAlphabeth(char);
  /**
   * @brief used to check if the string exists in the alphabet
   * 
   * @return true if exist
   * @return false 
   */
  bool IsInAlphabeth(std::string);
  
/**
 * @brief Resturn a string with alphabet
 * 
 * @return std::string 
 */
  std::string PrintAlphabet();
  
  /**
   * @brief Operator of copy
   * 
   * @param rhs 
   * @return Alphabet& 
   */
  Alphabet& operator=(const Alphabet& rhs);

};