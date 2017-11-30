template <typename T>

class SortedList {
  struct Node {
    
    T data_;
    Node* next_;
    Node* prev_;

    Node(const T& data = T{}, Node* nx = nullptr, Node* pr = nullptr){
      data_ = data;
      next_ = nx;
      prev_ = pr;
    }
  };

  Node* front_;
  Node* back_;
  int sz;

 public:
  class const_iterator {
    
    friend class SortedList;

  protected:
    Node* curr_;
    const_iterator(Node* nx) { curr_ = nx; }

  public:
    const_iterator() { this->curr_ = nullptr; }

    
    //points to the next node in the list
    const_iterator operator++() {
      if (curr_) {
        curr_ = curr_->next_;
      }
      return *this;
    }

    //points to the next node in the list
    const_iterator operator++(int) {
      const_iterator old = *this;
      if (curr_){
        curr_ = curr_->next_;
      }
      return old;
    }

    //points to the previous node in the list
    const_iterator operator--() {
      if (curr_) {
        curr_ = curr_->prev_;
      }
    }

    //points to the next node in the list
    const_iterator operator--(int) {
      const_iterator old = *this;
      if (curr_) {
        curr_ = curr_->prev_;
      }

      return old;
    }

    //returns true if two iterators are pointing to the same node, or else it returns false
    bool operator==(const_iterator rhs) { return curr_ == rhs.curr_; }
    
    //returns true if two iterators point at different nodes, or else it returns false 
    bool operator!=(const_iterator rhs) { return curr_ != rhs.curr_; }

    //dereferencing operator that returns the data in the node pointed to by iterator
    const T& operator*() const { return curr_->data_; }
  };

  class iterator : public const_iterator {
    friend class SortedList;

   protected:
    iterator(Node* nx) : const_iterator(nx) {}

   public:

    
    iterator() { this->curr_ = nullptr; }


    //Makes iterator point to the next node
    iterator operator++() {
      if (this->curr_) {
        this->curr_ = this->curr_->next_;
      }
      return *this;
    }
    //Makes iterator point to the next node
    iterator operator++(int) {
      iterator old = *this;
      if (this->curr_) {
        this->curr_ = this->curr_->next_;
      }
      return old;
    }
    //Makes iterator point to the previous node
    iterator operator--() {
      if (this->curr_) {
        this->curr_ = this->curr_->prev_;
      }
      return *this;
    }

    //Makes iterator point to the previous node
    iterator operator--(int) {
      iterator old = *this;
      if (this->curr_) {
        this->curr_ = this->curr_->prev_;
      }
      return old;
    }

    //dereferencing operator that returns the data in the node pointed to by iterator
    T& operator*() { return this->curr_->data_; }

    //dereferencing operator that returns the data in the node pointed to by iterator
    const T& operator*() const { return this->curr_->data_; }
  
  };
  SortedList();
  ~SortedList();
  SortedList(const SortedList& rhs);
  SortedList& operator=(const SortedList& rhs);
  SortedList(SortedList&& rhs);
  SortedList& operator=(SortedList&& rhs);
  iterator begin() { return iterator(front_->next_); }

  iterator end() { return iterator(back_); }
  const_iterator begin() const { return const_iterator(front_->next_); }
  const_iterator end() const { return const_iterator(back_); }
  iterator insert(const T& data);
  iterator search(const T& data);
  const_iterator search(const T& data) const;
  iterator erase(iterator it);
  iterator erase(iterator first, iterator last);
  bool empty() const;
  int size() const;
};

//creates an empty SortedList
template <typename T>
SortedList<T>::SortedList() {
  front_ = new Node();
  back_ = new Node();
  front_->next_ = back_;
  back_->prev_ = front_;
  sz = 0;
}

//destroys SortedList at the end of object lifetime
template <typename T>
SortedList<T>::~SortedList() {
  Node* tmp = front_;

  while (tmp != nullptr) {
    Node* rm = tmp;
    tmp = tmp->next_;
    delete rm;
    sz--;
  }
}

//copy constructor to copy a node that is passed on as a const
template <typename T>
SortedList<T>::SortedList(const SortedList& rhs) {
  front_ = new Node();
  back_ = new Node();

  front_->next_ = back_;
  back_->prev_ = front_;

  for (auto a = rhs.begin(); a != rhs.end(); a++) {
    insert(*a);
  }
  sz = rhs.sz;
}


//assignment operator to copy a const node to a current node if it doesnt already equal it.
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs) {
  if (this != &rhs) {
    front_ = new Node();
    back_ = new Node();

    front_->next_ = back_;
    back_->prev_ = front_;

    for (auto i = rhs.begin(); i != rhs.end(); i++) {
      insert(*i);
    }

    sz = rhs.sz;
  }

  return *this;
}

//copy constructor to copy a node
template <typename T>
SortedList<T>::SortedList(SortedList&& rhs) {
  front_ = rhs.front_;
  back_ = rhs.back_;
  sz = rhs.sz;
  rhs.front_ = rhs.back_;
}


//if the rhs node doesnt equal the current node then assigns it. If current node equals then returns a reference of this
template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs) {
  if (&rhs != this) {
    front_ = rhs.front_;
    back_ = rhs.back_;
    sz = rhs.sz;
    rhs.front_ = rhs.back_;
  }

  return *this;
}

//adds data to the linked list and returns the iterator to newly added node
template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data) {
  Node* curr = front_->next_;
  Node* newNode = new Node(data);

  if (curr->next_ == nullptr || newNode->data_ < curr->data_) {
    front_->next_ = newNode;
    newNode->next_ = curr;
    newNode->prev_ = front_;
    curr->prev_ = newNode;
  } else {
    while (curr->next_ != back_ && curr->next_->data_ < newNode->data_) {
      curr = curr->next_;
    }
    newNode->next_ = curr->next_;

    if (curr->next_ != back_) {
      newNode->next_->prev_ = newNode;
    }
    curr->next_ = newNode;
    newNode->prev_ = curr;
  }

  sz++;
  return iterator(newNode);
}

//Returns iterator to the node that contains the data. If the data is not found then it will return end()
template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data) {
  
  iterator start = begin();
  iterator ends = end();
  bool check = false;


  if (!(front_->next_ == back_)) {
    while (!check && start != end()) {
      if (*start == data) {
        check = true;
        return start;
      } else {
        start++;
      }
    }
  } else {
    return end();
  }

  return ends;
}

//Returns iterator to the node that contains the data. If the data is not found then it will return end()
template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(
    const T& data) const {
  
  iterator start = begin();
  iterator end = end();
  bool check = false;

  if (!(front_->next_ == back_)) {
    while (!check && start != end()) {
      if (*start == data) {
        check = true;
        return start;
      } else {
        start++;
      }
    }
  }

  else {
    return end();
  }

  return end;
}

//removes the node 'it' and returns iterator to node after the node removed
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it) {
  
  Node* erase = it.curr_;
  Node* one = new Node;
  Node* two = erase->prev_;
  Node* three = erase->next_;

  two->next_ = three;
  three->prev_ = two;

  sz--;

  return iterator(three);
}

//function removes the nodes beetween first and last including the node that refers to first. 
//returns an iterator to last 
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator first, iterator last) {
  
  Node* tmp = first.curr_;
  Node* one = last.curr_;
  Node* start = tmp->prev_;
  Node* next;
  
  if (tmp->prev_ == nullptr) {
    front_->next_ = one;
  } else {
    start->next_ = one;
    one->prev_ = start;
  }
  while (tmp != last.curr_) {
    next = tmp->next_;
    delete tmp;
    tmp = next;
  }

  return last--;
}
//function returns true if list is empty and false if size is greater than 1
template <typename T>
bool SortedList<T>::empty() const {
  
  if (sz == 0) {
    return true;
  }

  return false;
}

//function returns the size of the list 
template <typename T>
int SortedList<T>::size() const {
  return sz;
}
