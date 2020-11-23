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
  if (SearchPatternInString("ab")) {
    std::cout << "Aceptada" << std::endl;
  } else {
    std::cout << "No Aceptada" << std::endl;
  }
}

void Nfa::InsertState(State new_state) {
  nfa_states_.insert(new_state);
}


/* SearchPatternInString
Se declara un uint, que será donde se guarde si hay cambio de estado.
Se crea un iterador que apunta al estado de arranque (Comienzo del set)
La función State::Transition busca el caracter que se le pasa entre las
transiciones que tiene y devuelve el estado al que debe transitar con ese simbolo. 
Si valor == -1 no encontro transicion y se reinicia el iterador al principio
Si valor != -1 it se queda apuntando en el siguiente estado para esperar el 
siguiente simbolo  */
// bool Nfa::SearchPatternInString(std::string word) {
//   bool get_acept_state = false;
//   uint new_id;
//   std::set<State>::iterator it = Begin();
//   //Recorremos la cadena completa
//   for (size_t i = 0; i < word.size(); i++) {
//     if (it->Transition(word[i]) == (uint)-1) {
//       it = Begin();
//     } else {
//       // it = nfa_states_.find(State(new_id, ""));
//       it++;
//       get_acept_state = it->IsAceptState() || get_acept_state;
//     }
//   }
//   return get_acept_state;
// }

bool Nfa::SearchPatternInString(std::string word) {
  bool get_acept_state = false;
  word = "aababaaaababaaa";
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
    Analizer(it, word, i+1, acept_state);
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
  bool acept_state;
  uint id_state, total_states, start_state;
  // int i=0;
  uint number_transitions;
  
  if (file_maker_.is_open() && file_maker_) {
    while (!file_maker_.eof()) {
      file_maker_ >> total_states;
      file_maker_ >> start_state;        
      for (uint i = 0; i < total_states; i++) {
        file_maker_ >> id_state >> acept_state >> number_transitions;
        if (id_state == start_state) 
          start_state = true;
        else 
          start_state = false;
        State estado_temporal(id_state, acept_state, start_state);
        for (uint i = 0; i < number_transitions; i++) {
          char symbol;
          uint next_id;
          file_maker_ >> symbol >> next_id;
          alphabet_.InsertSymbol((int)symbol);
          estado_temporal.InsertTransition(std::make_pair(symbol, next_id));
        }
        SeeWhat(estado_temporal);
        nfa_states_.insert(estado_temporal); 
      }
    }
    std::cout << "Alfabeto creado: " << alphabet_.PrintAlphabet() << std::endl;
  } 
  else {
    std::cerr << "Nombre de fichero erroneo. " << std::endl;
  }
}

void Nfa::ReadFromFileAndWrite() {
  std::string aux;
  
  if (file_input_.is_open() && file_input_) {
    while (!file_input_.eof()) {
      file_input_ >> aux;
      
      if (IsInAlphabet(aux)) {
        std::cout << aux << "--> SI" << std::endl;
      } else {
        std::cout << aux << "--> NO" << std::endl;
      }
    }
  } 
  else {
    std::cerr << "Nombre de fichero erroneo. " << std::endl;
  }
}


// std::string PatternSearch::SearhPattern(std::string string_to_analize) {
//   temp_ = dfa_.SearchPatternInString(string_to_analize);
//   std::string solution;
//   if (temp_.size() < 1) {
//     solution = "[]";
//     std::cout << solution;
//   } else {
//     for (size_t i = 0; i <= temp_.size(); i++) {
//       solution += temp_[i];
//       std::cout << "TEST ->" << temp_[i] << " ";
//     }
//   }

//   return solution;


// }

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

std::string Nfa::GetStartState() {
  for (auto it=nfa_states_.begin() ; it != nfa_states_.end(); ++it) {
    if (it->IsStartState())
      return ("\""+it->GetName()+"\"");
  }
  return "--";
}
