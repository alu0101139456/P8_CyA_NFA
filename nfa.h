/**
 * @file nfa.h
 * @author Ángel Julián Bolaño Campos (alu0101139456@ull.edu.es)
 * @brief Práctica 8: Autómatas Finitos No Deterministas
 * @version 0.1
 * @date 2020-11-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include<set>
#include<iostream>
#include<fstream>
#include<vector>
#include "alfabeto.h"
#include "estado.h"

class Nfa {
 private:
  Alphabet alphabet_;
  std::set<State> nfa_states_;
  std::string pattern_;
  std::ifstream file_maker_;
  std::ifstream file_input_;
  std::ofstream file_output_;
  bool check_nfa_make_ = false;

 public:
  /**
    * @brief Construct a new Nfa object
    * 
    */
  Nfa() {}
  /**
   * @brief Destroy the Nfa object
   * 
   */
  ~Nfa();
  /**
   * @brief Construct a new Nfa object
   * @param File to make NFA
   * @param File to read and find patterns
   * @param File to put results
   */
  Nfa(std::string,std::string, std::string);

  /**
   * @brief Read the file to make NFA
   * 
   */
  void ReadNfaFromFile();
  /**
   * @brief Used to read and write in output file the results
   * 
   */
  void ReadFromFileAndWrite();
  /**
   * @brief Set the Alphabet object
   * 
   * @param alphabet 
   */
  void SetAlphabet(const Alphabet alphabet) { alphabet_ = alphabet; }  
  /**
   * @brief Get the States object in SET type
   * 
   * @return std::set<State> 
   */
  std::set<State> GetStates();
  /**
   * @brief Get the Size object
   * 
   * @return unsigned 
   */
  unsigned GetSize() { return nfa_states_.size(); }
  /**
   * @brief Get the Acept States object
   * 
   * @return std::vector<std::string> 
   */
  std::vector<std::string> GetAceptStates();
  /**
   * @brief Get the Start State object
   * 
   * @return uint Return id of state
   */
  uint GetStartState();
  /**
   * @brief Update the state remove the old and make new
   * 
   */
  void UpdateState(std::set<State>::iterator&,const State&);
  /**
   * @brief Inicialize NFA
   * @param File to make NFA
   * @param File to read and find patterns
   * @param File to put results
   */
  void InsertFiles(std::string,std::string, std::string);

 private:
  /**
   * @brief Recursive funtion to search possibles path
   * 
   * @param it Iterator to state evaluated
   * @param word Reference to string to analize
   * @param i Index 
   * @param acept_state Boolean param to get acept state 
   */
  void Analizer(std::set<State>::iterator&, std::string&, uint, bool&);
  /**
   * @brief Used to check if the symbol exists in the alphabet
   * 
   * @return true 
   * @return false 
   */
  bool IsInAlphabet(char);
  /**
   * @brief Used to check if the string exists in the alphabet
   * 
   * @param string_to_analize 
   * @return true 
   * @return false 
   */
  bool IsInAlphabet(std::string);
  /**
   * @brief Debug for see the values of state
   * 
   * @param state_to_see 
   */
  void SeeWhat(State state_to_see);
  /**
   * @brief Iterator to begin of set states
   * 
   * @return std::set<State>::iterator 
   */
  std::set<State>::iterator Begin();
  /**
   * @brief Iterator to end of set states
   * 
   * @return std::set<State>::iterator 
   */
  std::set<State>::iterator End();
  /**
   * @brief Find a state with a specific name 
   * @param NameState of state to find
   * @return std::set<State>::iterator 
   */
  std::set<State>::iterator FindStateName(std::string&);
  /**
   * @brief Find a state with specific id
   * @param idState
   * @return std::set<State>::iterator 
   */
  std::set<State>::iterator FindStateId(unsigned&);
  /**
   * @brief Insert state in set
   * 
   * @param estado 
   */
  void InsertState( State estado); 
  /**
   * @brief Search Pattern in String
   * @param StringToSearch
   * @return true
   * @return false
   */
  bool SearchPatternInString(std::string);

  void PrintNfa();

};

