/**
 * @file set.h
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
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>

#define MAX_LONG sizeof(long) * 8

class Set {
 private:
  unsigned number_sets_;            
  unsigned max_of_elemts_;          
  const unsigned bits_per_set_ = sizeof(long) * 8;
  std::vector<unsigned long> set_;  
  unsigned long mask_;              

 public:
  /**
  * @brief Construct a new Set object
  * 
  */
  Set();
  /**
   * @brief Construct a new Set object
   * 
   */
  explicit Set(const int);
  /**
   * @brief Construct a new Set object
   * 
   */
  Set(const Set&);
  /**
   * @brief Get the set object
   * 
   * @return std::vector<unsigned long> 
   */
  std::vector<unsigned long> get_set(void) const;

  /**
   * @brief Add between set objects
   * @param number to add
   */
  void Add(const int);    
  /**
   * @brief Insert number in set
   * @param Number to insert
   */
  void Insert(const int);
  /**
   * @brief Remove specific number
   * @param Number to remove
   */
  void Remove(const int);
  /**
   * @brief Crear all set
   * 
   */
  void Clear();
  /**
   * @brief Check if the set is empty
   * 
   * @return true 
   * @return false 
   */
  bool IsEmpty() const;
  /**
   * @brief Check if param belong to set
   * @param Number to check
   * 
   * @return true 
   * @return false 
   */
  bool IsBelonging(const int) const;
  /**
   * @brief Convert to string the set
   * 
   * @return std::string 
   */
  std::string toString();
  /**
   * @brief Convert the set to vector
   * 
   * @return std::vector<int> 
   */
  std::vector<int> toVectorInt();
  /**
   * @brief Find a number const in set
   *  
   * @param number to find
   * 
   * @return true 
   * @return false 
   */
  bool Find(const int);
  /**
   * @brief Overload of operator +
   * @param another set object
   * @return Set 
   */
  Set operator +(const Set&);
  /**
   * @brief Overload of operator *
   * @param another set object 
   * @return Set 
   */
  Set operator *(const Set&);
  /**
   * @brief Overload of operator !
   * @param another set object 
   * @return Set 
   */
  Set operator !() const;
  /**
   * @brief Overload of operator -
   * @param another set object 
   * @return Set 
   */
  Set operator -(const Set&);
  /**
   * @brief Overload of operator =
   * @param another set object 
   */
  void operator =(const Set&);
  /**
   * @brief Overload of operator ==
   * @param another set object
   * 
   * @return true 
   * @return false 
   */
  bool operator ==(const Set&);
};
/**
 * @brief Overload of operator <<
 * @param another set object 
 * 
 * @return std::ostream& 
 */
std::ostream& operator <<(std::ostream& , const Set);
