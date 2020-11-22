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


void Nfa::InsertState(State new_state) {
  states_dfa_.insert(new_state);
}


//Busca entre los estados el que tiene mismo nombre y devuelve el iterador
std::set<State>::iterator Nfa::FindStateName(std::string& name_to_find){
  std::set<State>::iterator it;
  for(it = states_dfa_.begin(); it != states_dfa_.end(); ++it) {
    if(it->GetName() == name_to_find ) 
      return it;
  }
  return it;
}

void Nfa::UpdateState(std::set<State>::iterator& it,const State& nuevo) {
  std::cout << it->GetName() << '\n';
  if (it != states_dfa_.end()){
    states_dfa_.erase(it);
    states_dfa_.insert(nuevo);
  }
}

std::set<State> Nfa::GetStates() {
 return states_dfa_;

}

std::set<State>::iterator Nfa::Begin() {
  return states_dfa_.begin();
}

std::set<State>::iterator Nfa::End() {
  return states_dfa_.end();
}


std::vector<std::string> Nfa::GetAceptStates() {
  std::vector<std::string> aux;
  for(auto it=states_dfa_.begin() ; it != states_dfa_.end(); ++it) {
    if(it->IsAceptState())
      aux.push_back("\""+it->GetName()+"\"");
  }
  return aux;
}

std::string Nfa::GetStartState() {
  for (auto it=states_dfa_.begin() ; it != states_dfa_.end(); ++it) {
    if (it->IsStartState())
      return ("\""+it->GetName()+"\"");
  }
  return "--";
}

/* GenerateDfaWithPattern
Los estados de arranque e inicial se crean fuera del bucle para controlar sus
estados especiales de arranque y aceptación */
void Nfa::GenerateDfaWithPattern(std::string pattern) {
  pattern_ = pattern;
  //Contemplada posibilidad de patron de un simbolo
  if (pattern.size() > 1) {
    State aux(0, false, true);
    aux.InsertTransition(std::make_pair(pattern[0],1));
    states_dfa_.insert(aux);
    for (uint i = 1; i < pattern.size(); i++) {
      aux.CleanData(); 
      aux.SetId(i);
      aux.InsertTransition(std::make_pair(pattern[i], i+1));
      states_dfa_.insert(aux);

    }
    aux.CleanData();
    aux.SetId(pattern.size());
    aux.SetAceptState(true);
    states_dfa_.insert(aux);
    // SeeWhat(aux);
  } else {
    State aux(0, true, true);
  } 
  

}

/* SearchPatternInString
Se declara un uint, que será donde se guarde si hay cambio de estado.
Se crea un iterador que apunta al estado de arranque (Comienzo del set)
La función State::Transition busca el caracter que se le pasa entre las
transiciones que tiene y devuelve el estado al que debe transitar con ese simbolo. 
Si valor == -1 no encontro transicion y se reinicia el iterador al principio
Si valor != -1 it se queda apuntando en el siguiente estado para esperar el 
siguiente simbolo  */
std::vector<int> Nfa::SearchPatternInString(std::string word) {
  bool get_acept_state = false;
  uint new_id;
  std::vector<int> mod;
  std::set<State>::iterator it = Begin();
  //Recorremos la cadena completa
  for (size_t i = 0; i < word.size(); i++) {
    if ((new_id = it->Transition(word[i])) == (uint)-1) {
      it = Begin();
    } else {
      it = states_dfa_.find(State(new_id, ""));
      // get_acept_state = it->IsAceptState() || get_acept_state;
      if(it->IsAceptState()) mod.push_back( i );
    }
  }
  return mod;
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




Nfa::Nfa(std::string name_file_input, std::string name_file_output) {

  alphabet_.InsertAlphabetACII(); //El Alfabeto lo genera el objeto segun opcion
  if (StringBelongsAlphabet(pattern_to_make)) {
    pattern_ = pattern_to_make;
    file_input_.open(name_file_input);
    file_output_.open(name_file_output);
    MakeDFA();
    ReadFromFile();
  } else {
    std::cerr << "El patron no pertenece al alfabeto." << std::endl;
  }

}
PatternSearch::~PatternSearch() { //Cierra los ficheros si estan abiertos
  if (file_input_.is_open()) {
    file_input_.close();
  }
  if (file_output_.is_open()) {
    file_output_.close();
  }
}

// bool PatternSearch::StringBelongsAlphabet(std::string pattern) {
//   return alphabet_.IsInAlphabeth(pattern);
// }

// void PatternSearch::ReadFromFile() {
//   std::string aux;
//   int i=0;
//   try {
//     if (file_input_.is_open() && file_input_) {
//       while (!file_input_.eof()) {
//         file_input_ >> aux;
//         if (file_input_.eof()) break;
//         if (StringBelongsAlphabet(aux)) {
//             file_output_ << SearhPattern(aux) <<"\"\n";
//         } else {
//           file_output_ << SearhPattern(aux) <<"\"\n";
//         }
//       }
//       i++;
//     } 
//     else {
//       std::cerr << "Nombre de fichero erroneo. " << std::endl;
//     }
       
//   }
//   catch ( std::exception& e) {
//     std::cout << "Failed to read file" << e.what() << std::endl;
//   }  
// }

// void PatternSearch::MakeDFA() {
//   dfa_.SetAlphabet(alphabet_);
//   dfa_.GenerateDfaWithPattern(pattern_);
// }

// std::string PatternSearch::SearhPattern(std::string string_to_analize) {
//   temp_ = dfa_.SearchPatternInString(string_to_analize);
//   std::string solution;
//   if(temp_.size() < 1) {
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
