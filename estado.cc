/**
 * @file estado.cc
 * @author Ángel Julián Bolaño Campos (alu0101139456@ull.edu.es)
 * @brief Práctica 8: Autómatas Finitos No Deterministas
 * @version 0.1
 * @date 2020-11-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "estado.h"

void State::CleanData() {
  id_ = 0;
  name_state_.clear();
  acept_state_= false;
  start_state_ = false;
  std::pair<char,unsigned> aux;
  transition_.clear();
  
}


void State::InsertTransition(std::pair<char,unsigned> new_transition) {
  transition_.push_back(new_transition);
}


void State::PrintTransitions() const {
  if (!transition_.empty()) {
    // std::cout << GetId() << '\n';
    for (size_t i = 0; i < transition_.size(); i++) {
      
      std::cout << "Con: \"" << transition_[i].first << "\" a estado " << transition_[i].second << std::endl;
    }
  } else {
    std::cout << "El estado \"" << GetId() << "\" no tiene transiciones.\n";
  }   
}

//Busca entre sus transiciones si la hay con un caracter determinado
uint State::Transition(char symbol) const{
  for ( auto transition : transition_) {
    if ( transition.first == symbol ){ 
      return transition.second;
    }
  }
  return -1;
}

TransitionMap State::TransitionsWith(char symbol) const{
  TransitionMap temporal;
  for ( auto transition : transition_) {
    if ( transition.first == symbol || transition.first == '~' ){ 
      temporal.push_back(transition);
    }
  }
  return temporal;
}


State::State(const State& rhs) {
  this->id_= rhs.id_;
  this->name_state_ = rhs.name_state_;
  this->acept_state_ = rhs.acept_state_;
  this->transition_ =rhs.transition_;
  this->start_state_ = rhs.start_state_;
}


State& State::operator=(const State& rhs) {
  this->id_ = rhs.id_;
  this->name_state_ = rhs.name_state_;
  this->acept_state_ = rhs.acept_state_;
  this->transition_ =rhs.transition_;
  this->start_state_ = rhs.start_state_;
  return *this;
}