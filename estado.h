/**
 * @file estado.h
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
#include <vector>

class State {
 private:
  uint id_;
  std::string name_state_;
  char name_char_;
  bool acept_state_ = false;
  bool start_state_ = false;
  std::vector<std::pair<char,unsigned>> transition_;

 public:
  /**
  * @brief Construct a new State object
  * 
  */
  State() {}
  /**
   * @brief Destroy the State object
   * 
   */
  ~State() {}
  /**
   * @brief Construct a new State object with id and name
   * 
   * @param id 
   * @param name 
   */
  State(unsigned id, std::string name):
    id_(id),
    name_state_(name)
  {}
  /**
   * @brief Construct copy of new State object
   * 
   */
  State(const State&);
  /**
   * @brief Construct a new State complete
   * 
   * @param id Id of state
   * @param name_state Name of state
   * @param acept If it is acept state it will be true
   * @param start If it is start state it will be true
   */
  State(uint id, std::string name_state, bool acept, bool start):
    id_(id),
    name_state_(name_state),
    acept_state_(acept),
    start_state_(start){}
  /**
   * @brief Construct a new State object
   * 
   * @param id 
   * @param acept If it is acept state it will be true
   * @param start If it is start state it will be true
   */
  State(uint id, bool acept, bool start):
    id_(id),
    acept_state_(acept),
    start_state_(start){}

  /**
   * @brief Clean data of the state
   * 
   */
  void CleanData();
  /**
   * @brief Insert transition in vector of pair<char, unsigned>
   * 
   * @param aux pair<char, unsigned>
   */
  void InsertTransition(std::pair<char,unsigned> aux);
  /**
   * @brief Print the transitions of the state 
   * For debug 
   */
  void PrintTransitions() const;
  /**
   * @brief Return the state with transition
   * 
   * @param symbol 
   * @return uint 
   */
  uint Transition(char symbol) const;

  //GETTERS
  /**
   * @brief Get the Id object
   * 
   * @return unsigned int 
   */
  inline unsigned int GetId() const { return id_; }
  /**
   * @brief Get the Name object
   * 
   * @return std::string 
   */
  inline std::string GetName() const {return name_state_;}
  /**
   * @brief Return if is acept state
   * 
   * @return true 
   * @return false 
   */
  inline bool IsAceptState() const { return acept_state_; }
  /**
   * @brief Return ir is start state
   * 
   * @return int 
   */
  inline int IsStartState() const { return start_state_; }


  //SETTERS
  /**
   * @brief Set the Acept State object
   * 
   * @param is_acept_state 
   */
  inline void SetAceptState(bool is_acept_state) { 
    acept_state_ = is_acept_state; }
  /**
   * @brief Set the Start State object
   * 
   * @param is_start 
   */
  inline void SetStartState(bool is_start) { 
    start_state_ = is_start; }
  /**
   * @brief Set the Id object
   * 
   * @param id 
   */
  inline void SetId(unsigned id) { id_ = id; }
  /**
   * @brief Set the Name object
   * 
   * @param name 
   */
  inline void SetName(std::string name) { name_state_ = name; }

  //OPERATORS
  /**
   * @brief Overload of operator <
   * 
   * @param rhs 
   * @return true 
   * @return false 
   */
  bool operator<(const State& rhs) const {
    return (this->GetId() < rhs.GetId());}
  /**
   * @brief Overload of operator ==
   * 
   * @param rhs 
   * @return true 
   * @return false 
   */
  bool operator==(const State& rhs) const {
    return (this->GetId() == rhs.GetId()); }
  /**
   * @brief Overload of operator =
   * 
   * @param rhs 
   * @return State& 
   */
  State& operator=(const State& rhs);

};