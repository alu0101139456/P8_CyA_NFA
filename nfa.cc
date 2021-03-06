/**
 * @file nfa.cc
 * @author Ángel Julián Bolaño Campos (alu0101139456@ull.edu.es)
 * @brief Práctica 8: Autómatas Finitos No Deterministas
 * @version 0.1
 * @date 2020-11-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "nfa.h"



Nfa::Nfa(std::string name_make_nfa, std::string name_file_input, std::string name_file_output) {
  alphabet_.InsertSymbol(126);
  file_maker_.open(name_make_nfa);
  file_input_.open(name_file_input);
  file_output_.open(name_file_output);
  ReadNfaFromFile();
  ReadFromFileAndWrite();

}

void Nfa::InsertFiles(std::string name_make_nfa, std::string name_file_input, std::string name_file_output) {
  alphabet_.InsertSymbol(126);
  file_maker_.open(name_make_nfa);
  file_input_.open(name_file_input);
  file_output_.open(name_file_output);
  ReadNfaFromFile();
  ReadFromFileAndWrite();
}

void Nfa::InsertState(State new_state) {
  nfa_states_.insert(new_state);
}



bool Nfa::SearchPatternInString(std::string word) {
  bool get_acept_state = false;
  std::set<State>::iterator it = Begin();
  Analizer(it, word, 0, get_acept_state);
  return get_acept_state;
}

void Nfa::Analizer(std::set<State>::iterator& it, std::string& word, uint i, bool& acept_state) {

  if (i >= word.size()) {
    if (it->IsAceptState())
      acept_state = true;
    return;
  }
  auto transitions = it->TransitionsWith(word[i]);
  for (auto trans: transitions) {
    it = nfa_states_.find(State(trans.second, ""));
    if( trans.first == '~') {
      Analizer(it, word, i, acept_state);
    } else
      Analizer(it, word, i+1, acept_state);
  }   
}


Nfa::~Nfa() { //Cierra los ficheros si estan abiertos
  if (file_input_.is_open()) {
    file_input_.close();
  }
  if (file_output_.is_open()) {
    file_output_.close();
  }
  if (file_maker_.is_open()) {
    file_maker_.close();
  }
}


bool Nfa::IsInAlphabet(char symbol) {
  return alphabet_.IsInAlphabeth(symbol);
}

bool Nfa::IsInAlphabet(std::string string_to_analize) {
  return alphabet_.IsInAlphabeth(string_to_analize);
}


void Nfa::ReadNfaFromFile() {
  std::string aux;
  bool acept_state = false;
  bool start_s = false;
  uint id_state, total_states, start_state, number_transitions;
  if (file_maker_.is_open() && file_maker_) {
    while (!file_maker_.eof()) {
      file_maker_ >> total_states;
      file_maker_ >> start_state;        
      for (uint i = 0; i < total_states; i++) {
        file_maker_ >> id_state >> acept_state >> number_transitions;
        if (id_state == start_state)
          start_s = true;
        else
          start_s = false; 
        State estado_temporal(id_state, acept_state, start_s);
        for (uint i = 0; i < number_transitions; i++) {
          char symbol;
          uint next_id;
          file_maker_ >> symbol >> next_id;
          alphabet_.InsertSymbol((int)symbol);
          estado_temporal.InsertTransition(std::make_pair(symbol, next_id));
        }
        // SeeWhat(estado_temporal);
        nfa_states_.insert(estado_temporal); 
      }
    }
    //std::cout <<"Alfabeto creado:" << alphabet_.PrintAlphabet() << std::endl;
    check_nfa_make_ = true;
    // PrintNfa();
  } 
  else {
    std::cerr << "Nombre de fichero para crear NFA erroneo. " << std::endl;
  }
}

void Nfa::ReadFromFileAndWrite() {
  std::string aux;
  
  if (!check_nfa_make_) {
    std::cerr << "NFA no construido." << std::endl;
    return;
  }

  if (file_input_.is_open() && file_input_ ) {
    while (!file_input_.eof()) {
      file_input_ >> aux;      
      if (IsInAlphabet(aux) && SearchPatternInString(aux)) {
        file_output_ << aux << " --> SI" << std::endl;
      } else {
        file_output_ << aux << " --> NO" << std::endl;
      }
    }
    std::cout << "Fichero generado con éxito." << std::endl;
  } 
  else {
    std::cerr << "Nombre de fichero de lectura erroneo. " << std::endl;
  }
}



//Busca entre los estados el que tiene mismo nombre y devuelve el iterador
std::set<State>::iterator Nfa::FindStateName(std::string& name_to_find){
  std::set<State>::iterator it;
  for (it = nfa_states_.begin(); it != nfa_states_.end(); ++it) {
    if (it->GetName() == name_to_find ) 
      return it;
  }
  return it;
}

void Nfa::UpdateState(std::set<State>::iterator& it,const State& nuevo) {
  std::cout << it->GetName() << '\n';
  if (it != nfa_states_.end()){
    nfa_states_.erase(it);
    nfa_states_.insert(nuevo);
  }
}

std::set<State> Nfa::GetStates() {
 return nfa_states_;

}

std::set<State>::iterator Nfa::Begin() {
  return nfa_states_.begin();
}

std::set<State>::iterator Nfa::End() {
  return nfa_states_.end();
}


std::vector<std::string> Nfa::GetAceptStates() {
  std::vector<std::string> aux;
  for (auto it=nfa_states_.begin() ; it != nfa_states_.end(); ++it) {
    if (it->IsAceptState())
      aux.push_back("\""+it->GetName()+"\"");
  }
  return aux;   
}

uint Nfa::GetStartState() {
  std::set<State>::iterator it;
  for ( it = nfa_states_.begin(); it != nfa_states_.end(); it++){
    if(it->IsStartState())
     return it->GetId();
  }
  return -1;
}

void Nfa::PrintNfa() {
  std::set<State>::iterator it;
  for( it = Begin(); it != End() ; it++){
    std::cout << it->GetId() << " ";
    std::cout << it->IsStartState() << std::endl;
  }
}


///////// DEBUGG AND TEST

void Nfa::SeeWhat(State state_to_see) {
  std::cout << "-----------------------------------------"<< std::endl;;
  std::cout << "Estado con id: " << state_to_see.GetId() << '\n';
  std::cout << "Estado de arranque: "<<state_to_see.IsStartState()<<"\n";
  std::cout << "Estado de aceptación: "<<state_to_see.IsAceptState();
  std::cout << "\nCon transiciones: ";
  state_to_see.PrintTransitions();
  
}