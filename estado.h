
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
  State() {}
  ~State() {}
  State(std::string name): name_state_(name) {}
  State(unsigned id, std::string name):
    id_(id),
    name_state_(name)
  {}
  State(const State&);
  State(uint id, std::string name_state, bool acept, bool start):
    id_(id),
    name_state_(name_state),
    acept_state_(acept),
    start_state_(start){}

  State(uint id, bool acept, bool start):
    id_(id),
    acept_state_(acept),
    start_state_(start){}

  void CleanData();
  void InsertTransition(std::pair<char,unsigned> aux);
  void PrintTransitions() const;
  uint Transition(char symbol) const;




  //GETTERS
  inline unsigned int GetId() const { return id_; }
  inline std::string GetName() const {return name_state_;}
  inline bool IsAceptState() const { return acept_state_; }
  inline int IsStartState() const { return start_state_; }


  //SETTERS
  inline void SetAceptState(bool is_acept_state) { 
    acept_state_ = is_acept_state; }
  inline void SetStartState(bool is_start) { 
    start_state_ = is_start; }
  inline void SetId(unsigned id) { id_ = id; }
  inline void SetName(std::string name) { name_state_ = name; }

  //OPERATORS
  bool operator<(const State& rhs) const {
    return (this->GetId() < rhs.GetId());}
  bool operator==(const State& rhs) const {
    return (this->GetId() == rhs.GetId()); }
  State& operator=(const State& rhs);


  //


};