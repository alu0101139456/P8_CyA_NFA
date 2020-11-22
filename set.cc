


#include <set.h>

Set::Set() {
  max_of_elemts_ = bits_per_set_;
  set_.assign(1, 0);
  mask_ = ~0;
  number_sets_ = 1;
}


Set::Set(const int size) {
  assert(size > 0);
  max_of_elemts_ = size;
  int size_of_vector = size / bits_per_set_;
  if (size % bits_per_set_) {
    size_of_vector++;
  }
  set_.assign(size_of_vector, 0);
  mask_ = ~0;
  int number_elemnts_left = size % bits_per_set_;
  int how_much_to_move = bits_per_set_ - number_elemnts_left;
  mask_ = mask_ >> how_much_to_move;
  number_sets_ = size_of_vector;
}


Set::Set(const Set& SecondSet) {
  max_of_elemts_ = SecondSet.max_of_elemts_;
  set_ = SecondSet.set_;
  mask_ = SecondSet.mask_;
  number_sets_ = SecondSet.number_sets_;
}


std::vector<unsigned long> Set::get_set(void) const {
  return set_;
}


Set Set::operator +(const Set& SecondSet) {
  Set BiggerSet = *this;
  Set SmallerSet = SecondSet;
  unsigned max_size = BiggerSet.max_of_elemts_;
  unsigned min_size = SmallerSet.max_of_elemts_;
  if (SmallerSet.max_of_elemts_ > BiggerSet.max_of_elemts_) {
    BiggerSet = SmallerSet;
    SmallerSet = *this;
    max_size = BiggerSet.max_of_elemts_;
    min_size = SmallerSet.max_of_elemts_;
  }
  Set Result(BiggerSet);
  int condition = min_size / bits_per_set_ - ((min_size % bits_per_set_) ? 0 : 1);
  for (int i = 0; i <= condition; i ++) {
    Result.set_.at(i) = set_.at(i) | SecondSet.set_.at(i);
  }
  int condition2 = max_size / bits_per_set_
                  - ((max_size % bits_per_set_) ? 0 : 1);
  for (int i = condition + 1; i < condition2; i++) {
    Result.set_.at(i) = (max_size == max_of_elemts_) ? set_.at(i) : SecondSet.set_.at(i);
  }
  *(Result.set_.end()-1) = BiggerSet.mask_ & *(Result.set_.end()-1);
  return Result;
}



Set Set::operator *(const Set& SecondSet) {
  Set Result(SecondSet);
  unsigned min_size = SecondSet.max_of_elemts_;
  unsigned long temp_mask = SecondSet.mask_;
  if (SecondSet.max_of_elemts_ > max_of_elemts_) {
    Result = *this;
    min_size = max_of_elemts_;
    temp_mask = mask_;
  }
  int condition = min_size / bits_per_set_
                  - ((min_size % bits_per_set_) ? 0 : 1);
  for (int i = 0; i <= condition; i ++) {
    Result.set_[i] = set_[i] & SecondSet.set_[i];
  }

  *(Result.set_.end()-1) = temp_mask & *(Result.set_.end()-1);
  return Result;
  }


Set Set::operator !() const {
  Set Result(max_of_elemts_);
  for (uint i = 0; i < set_.size(); i++) {
    Result.set_[i] = ~set_[i];
  }
  Result.set_.back() = mask_ & Result.set_.back();
  return Result;
}



Set Set::operator -(const Set& SecondSet) {
  Set dummy = !SecondSet;
  Set biggest_set = *this;
  Set smalest_set = dummy;
  if (dummy.set_.size() > set_.size()) {
    biggest_set = dummy;
    smalest_set = *this;
  }
  Set Result(biggest_set.number_sets_);
  for (uint i = 0; i < biggest_set.number_sets_; i++) {
    if (i < smalest_set.number_sets_)
    Result.set_[i] = set_[i] & dummy.set_[i];
  }
  return Result;
}


void Set::operator =(const Set& SecondSet) {
  number_sets_ = SecondSet.number_sets_;
  max_of_elemts_ = SecondSet.max_of_elemts_;
  set_.resize(number_sets_);
  for (uint i = 0; i < number_sets_; i++) {
    set_[i] = SecondSet.set_[i];
  }
  mask_ = SecondSet.mask_;
}



bool Set::operator ==(const Set& SecondSet) {
  bool is_equal = 1;
  Set biggest_set = *this;
  Set smalest_set = SecondSet;
  if (SecondSet.set_.size() > set_.size()) {
    biggest_set = SecondSet;
    smalest_set = *this;
  }
  for (uint i = 0; i < number_sets_; i++) {
    if (set_[i] != SecondSet.set_[i]) {
      is_equal = 0;
    }
  }
  return is_equal;
}



void Set::Add(const int number_to_add) {
  assert(number_to_add > 0);
  unsigned position_of_vector = number_to_add / bits_per_set_;
  if (number_to_add % bits_per_set_ == 0) {
    position_of_vector--;
  }
  long temp_number = 1;
  temp_number = temp_number << (number_to_add % bits_per_set_ - 1);
  set_[position_of_vector] = set_[position_of_vector] | temp_number;
  if (position_of_vector >= number_sets_) {
    set_[position_of_vector] &= mask_;
  }
}



void Set::Insert(const int number_to_add) {
  if (number_to_add > (int)max_of_elemts_) {
    int new_size = number_to_add / bits_per_set_;
    if (number_to_add % bits_per_set_ != 0) {
      new_size++;
    }
    max_of_elemts_ = new_size * bits_per_set_;
    set_.resize(new_size, 0);
    number_sets_ = new_size;
  }
  Add(number_to_add);
}



void Set::Remove(const int number_to_remove) {
  assert(number_to_remove > 0);
  int position_of_vector = number_to_remove / bits_per_set_;
  if (number_to_remove % bits_per_set_ == 0) {
    position_of_vector--;
  }
  int dummy = number_to_remove;
  int total_move = dummy % bits_per_set_ - 1;
  long temp_number = ~1;
  for (int i = total_move; i > 0; i--) {
    temp_number = temp_number << 1;
    temp_number++;
  }
  set_[position_of_vector] = set_[position_of_vector] & temp_number;
  if (position_of_vector >= (int)number_sets_) {
    set_[position_of_vector] &= mask_;
  }
}


void Set::Clear() {
  for (uint i = 0; i < set_.size(); i++)
    set_[i] = 0;
}



bool Set::IsEmpty() const {
  for (uint i = 0; i < set_.size() ; i++) {
    if (set_[i] != 0) {
      return false;
    }
  }
  return true;
}



bool Set::IsBelonging(const int number_to_prove) const {
  bool is_belonging = 0;
  int position_of_vector = number_to_prove / bits_per_set_;
  if (number_to_prove % bits_per_set_ == 0) {
    position_of_vector--;
  }
  long temp_set = 1;
  temp_set = temp_set << (number_to_prove % bits_per_set_ - 1);
  temp_set = temp_set & set_[position_of_vector];
  if (temp_set != 0)
    is_belonging = 1;
  return is_belonging;
}



std::string Set::toString() {
  std::stringstream output;
  output << "{";
  std::vector<char> set_elements;
  std::vector<unsigned long> dummy_set = set_;
  for (uint i = 0; i < dummy_set.size(); i++) {
    for (uint j = 1; j <= MAX_LONG; j++) {
      if ((dummy_set[i] % 2) == 1) {
        set_elements.push_back(j + (i * MAX_LONG));
        dummy_set[i] = dummy_set[i] >> 1;
      } else {
        dummy_set[i] = dummy_set[i] >> 1;
      }
    }
  }
  for (uint i = 0; i < set_elements.size(); i++) {
    if (i < set_elements.size() - 1)
      output << set_elements[i] << ", ";
    if (i == set_elements.size() - 1)
      output << set_elements[i];
  }
  output << "}";
  return output.str();
}




std::vector<int> Set::toVectorInt() {
  std::stringstream output;
  std::vector<int> set_elements;
  std::vector<unsigned long> dummy_set = set_;
  for (uint i = 0; i < dummy_set.size(); i++) {
    for (uint j = 1; j <= MAX_LONG; j++) {
      if ((dummy_set[i] % 2) == 1) {
        set_elements.push_back(j + (i * MAX_LONG));
        dummy_set[i] = dummy_set[i] >> 1;
      } else {
        dummy_set[i] = dummy_set[i] >> 1;
      }
    }
  }
  return set_elements;
}



std::ostream&
operator <<(std::ostream& output, Set Set_write) {
  return output << Set_write.toString();
}


bool Set::Find(const int number_to_find) {
  std::vector<unsigned long> dummy_set = set_;
  for (uint i = 0; i < dummy_set.size(); i++) {
    for (uint j = 1; j <= MAX_LONG; j++) {
      int number_in_set = j + (i * MAX_LONG);
      if ( ((dummy_set[i] % 2) == 1) && number_in_set == number_to_find) {
        return true;
      } else {
        dummy_set[i] = dummy_set[i] >> 1;
      }
    }
  }
  return false;
}

