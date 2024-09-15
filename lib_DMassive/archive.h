#pragma once

#define STEP_CAPACITY 5

enum State { empty, busy, deleted };

namespace algorithms {
  template<typename T>
  inline void swap(T& val_1, T& val_2) noexcept {
    T tmp = val_1;
    val_1 = val_2;
    val_2 = tmp;
  }
}

template <typename T>
class TArchive {
  T* _data;                  // ������������ ������ ������
  State* _states;            // ��������� �����
  size_t _capacity;          // �������� ������ �������
  size_t _size;              // ���������� �������� ������
  size_t _deleted;           // ���������� "��������" �������
  size_t _realSize;
  //static int _status = 0;
public:
  TArchive();
  TArchive(size_t value);

  TArchive(const TArchive& archive);
  TArchive(const T* arr, size_t n);
  TArchive(size_t n, T value);
  TArchive(const TArchive& archive, size_t pos, size_t n);


  TArchive& sort();
  size_t Required_Index(int index);
  bool check();
  ~TArchive();

  void print() const noexcept;

  inline bool empty() const noexcept;
  inline bool full() const noexcept;

  size_t size();
  size_t deleted();
  size_t capacity();
  const T* data();

  void swap(TArchive& archive);

  TArchive& assign(const TArchive& archive);

  void AddElement(TArchive& value);
  void clear();
  void resize(size_t n, T value);
  void reserve(size_t n);

  void push_back(T value);             // ������� �������� (� �����)
  void pop_back();                     // �������� �������� (�� �����)
  void push_front(T value);            // ������� �������� (� ������)
  void pop_front();                    // �������� �������� (�� ������)

  TArchive& insert(const T* arr, size_t n, size_t pos);
  TArchive& insert(T value, size_t pos);

  //TArchive& replace(size_t pos, T new_value);

  TArchive& erase(size_t pos, size_t n);
  TArchive& remove_all(T value);
  TArchive& remove_first(T value);
  TArchive& remove_last(T value);
  TArchive& remove_by_index(size_t pos);

  size_t* find_all(T value) const noexcept;
  //size_t find_first(T value);
  //size_t find_last(T value);
private:
  //size_t count_value(T value);
};

template <typename T>
TArchive<T>::TArchive() {
  _size = 0;
  _deleted = 0;
  _capacity = STEP_CAPACITY;
  _data = new T[_capacity];
  _states = new State[_capacity];
  for (size_t i = 0; i < STEP_CAPACITY; i++) {
    _states[i] = State::empty;
  }
}

template <typename T>
TArchive<T>::TArchive(size_t value) {
  _size = 0;
  _deleted = 0;
  _capacity = value;
  _data = new T[_capacity];
  _states = new State[_capacity];
  for (size_t i = 0; i < _capacity; i++) {
    _states[i] = State::empty;
  }
}



template <typename T>
TArchive<T>::TArchive(const TArchive& archive) {
  _size = archive._size;
  _deleted = archive._deleted;
  _capacity = archive._capacity;
  _data = new T[_capacity];
  _states = new State[_capacity];
  for (size_t i = 0; i < _size; i++) {
    _data[i] = archive._data[i];
    _states[i] = archive._states[i];
  }
}


template <typename T>
TArchive<T>::TArchive(const T* arr, size_t n) {
  _size = n;
  _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
  _data = new T[_capacity];
  _states = new State[_capacity];
  for (size_t i = 0; i < _size; i++) {
    _data[i] = arr[i];
    _states[i] = State::busy;
  }
}

template <typename T>
TArchive<T>::TArchive(size_t n, T value) {
  _size = n;
  //_capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
  _data = new T[_capacity];
  _states = new State[_capacity];
  for (size_t i = 0; i < _size; i++) {
    _data[i] = value;
    _states[i] = State::busy;
  }


}

template <typename T>
TArchive<T>::TArchive(const TArchive& archive, size_t pos, size_t n) {
  _size = n;
  //_capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
  _data = new T[_capacity];
  _states = new State[_capacity];
  for (size_t i = pos; i < _size; i++) {
    _data[i] = archive._data[i];
    _states[i] = archive._states[i];
  }
}

template <typename T>
inline size_t TArchive<T>::size() {
  return _size;
}

template <typename T>
inline size_t TArchive<T>::deleted() {
  return _deleted;
}


template <typename T>
inline size_t TArchive<T>::capacity() {
  return _capacity;
}

template <typename T>
inline const T* TArchive<T>::data() {
  return _data;
}

template <typename T>
void TArchive<T>::swap(TArchive& archive) {
  TArchive archive_2;
  archive_2._size = this->_size;
  archive_2._deleted = this->_deleted;
  archive_2._capacity = this->_capacity;
  archive_2._data = new T[archive_2._capacity];
  archive_2._states = new State[archive_2._capacity];
  for (size_t i = 0; i < archive_2._size; i++) {
    archive_2._data[i] = this->_data[i];
    archive_2._states[i] = this->_states[i];
  }
  this->_size = archive._size;
  this->_deleted = archive._deleted;
  this->_capacity = archive._capacity;
  this->_data = new T[this->_capacity];
  this->_states = new State[this->_capacity];
  for (size_t i = 0; i < this->_size; i++) {
    this->_data[i] = archive._data[i];
    this->_states[i] = archive._states[i];
  }
  archive._size = this->_size;
  archive._deleted = this->_deleted;
  archive._capacity = this->_capacity;
  archive._data = new T[archive._capacity];
  archive._states = new State[archive._capacity];
  for (size_t i = 0; i < archive._size; i++) {
    archive._data[i] = this->_data[i];
    archive._states[i] = this->_states[i];
  }
}

template <typename T>
TArchive<T>& TArchive<T>::assign(const TArchive& archive) {
  *this = archive;
  return *this;
}


/*template <typename T>
void TArchive<T>::AddElement(TArchive& value) {
  if (_size < _capacity) {
    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
  }
  else{
    std::cout << "ERROR.the number of elements exceeded "<<"\n";
  }
}*/



template <typename T>
void TArchive<T>::clear() {
  _size = 0;
  _deleted = 0;
  _capacity = STEP_CAPACITY;
  _data = new  T[_capacity];
  _states = new State[_capacity];
  for (size_t i = 0; i < _capacity; i++) {
    _states[i] = State::empty;
  }

}


template <typename T>
void TArchive<T>::resize(size_t n, T value) {
  if (_capacity > n) {

    T* new_data = new T[n];
    State* new_states = new State[n];

    for (int i = 0; i < _size; i++) {
      new_data[i] = _data[i];
    }
    for (int i = _size; i < n; i++) {
      new_data[i] = value;
    }
    for (int i = 0; i < n; i++) {
      new_states[i] = _states[i];
    }
    for (int i = n; i < _capacity; i++) {
      new_states[i] = State::empty;
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _size = n;


  }if (_capacity == n) {
    T* new_data = new T[n];
    State* new_states = new State[n];

    for (int i = 0; i < _size; i++) {
      new_data[i] = _data[i];
    }
    for (int i = _size; i < n; i++) {
      new_data[i] = value;
    }
    for (int i = 0; i < n; i++) {
      new_states[i] = _states[i];
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
  }if (_capacity < n) {
    std::cout << "There is not enough space. Enlarge the archive";
  }
}


template <typename T>
void TArchive<T>::reserve(size_t n) {
  if (_capacity >= n) {
    std::cout << "There is already enough space";
  }
  else {
    T* new_data = new T[n];
    State* new_states = new State[n];

    for (int i = 0; i < _size; i++) {
      new_data[i] = _data[i];
    }

    for (int i = 0; i < n; i++) {
      new_states[i] = _states[i];
    }
    for (int i = n; i < n; i++) {
      new_states[i] = State::empty;
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = n;

  }
}



template <typename T>
TArchive<T>& TArchive<T>::sort() {
  int index = 0;
  int nulling = 0;
  T* new_data = new T[_capacity];
  State* new_states = new State[_capacity];
  for (int i = 0; i < _size + _deleted; i++) {
    if (_data[i] == NULL) {
      nulling++;
      continue;
    }
    else {
      new_data[index] = _data[i];
      new_states[index] = State::busy;
      index++;
    }
  }
  for (int i = index; i < _size + _deleted; i++) {
    new_states[i] = State::empty;
  }
  _deleted = 0;
  delete[]_data;
  delete[]_states;
  _data = new_data;
  _states = new_states;
  return *this;
}

template <typename T>
bool TArchive<T>::check() {
  if ((_deleted >= _capacity * 0.3) || ((_size >= _capacity * 0.8) && _deleted > 0)) {
    return true;
  }
  else {
    return false;
  }
}

template <typename T>
size_t TArchive<T>::Required_Index(int index) {
  if (_data[index] == NULL) {
    while (_data[index] == NULL) {
      index++;
    }

    return index;
  }
  else {
    return index;
  }
}


template <typename T>
void TArchive<T>::pop_front() {
  if (_size == 0) {
    throw std::logic_error("Error in function \
\"void TArchive<T>::pop_front()\": wrong position value.");
  }
  else {

    _data[this->Required_Index(0)] = NULL;
    _states[this->Required_Index(0)] = State::deleted;
    _size--;
    _deleted++;
    if (this->check()) {
      this->sort();
    }
  }
}


template <typename T>
void TArchive<T>::push_back(T value) {

  if (_size < _capacity) {
    if (_states[_size + _deleted] == State::deleted) {
      _deleted--;
      _data[_size + _deleted] = value;
      _states[_size + _deleted] = State::busy;
      _size++;

      //this->sort();
    }
    else {
      _data[_size + _deleted] = value;
      _states[_size + _deleted] = State::busy;
      _size++;

    }
  }if (_size >= _capacity) {
    throw std::logic_error("Error in function \
\"void TArchive<T>::push_back(T value)\": wrong position value.");
  }
  if (this->check()) {
    this->sort();
  }
}


template <typename T>
void TArchive<T>::pop_back() {
  if (_size == 0) {
    throw std::logic_error("Error in function \
\"void pop_back(T value)\": wrong position value.");
  }
  else {
    _data[_size - 1] = NULL;
    _states[_size - 1] = State::deleted;
    _size--;
    _deleted++;
    if (this->check()) {
      this->sort();
    }

  }
}

template <typename T>
TArchive<T>& TArchive<T>::remove_all(T value) {
  for (int i = 0; i < _size; i++) {
    if (_data[i] == value) {
      _data[i] = NULL;
      _states[_size - 1] = State::deleted;
      this->sort();
      _size--;
      _deleted++;

    }
  }
  return *this;
}




template <typename T>
TArchive<T>& TArchive<T>::remove_last(T value) {
  for (int i = _size - 1; i > -1; i--) {
    if (_data[i] == value) {
      _data[i] = NULL;
      _states[_size - 1] = State::deleted;
      this->sort();
      _size--;
      _deleted++;
      break;
    }
  }
  return *this;
}


template <typename T>
TArchive<T>& TArchive<T>::remove_first(T value) {
  for (int i = 0; i < _size; i++) {
    if (_data[i] == value) {
      _data[i] = NULL;
      _states[_size - 1] = State::deleted;
      this->sort();
      _size--;
      _deleted++;
      break;
    }
  }
  return *this;
}



template <typename T>
void TArchive<T>::push_front(T value) {

  if (_size < _capacity) {
    T* new_data = new T[_capacity];
    State* new_states = new State[_capacity];
    new_data[0] = value;
    new_states[0] = State::busy;
    for (int i = 1; i < _size + 1; i++) {
      new_data[i] = _data[i - 1];
      new_states[i] = _states[i - 1];
    }
    delete[]_data;
    delete[]_states;
    _data = new_data;
    _states = new_states;
    _size++;
    this->sort();
    int _count = 1;
    if (_deleted > 0) {
      while (_deleted < 0 || _count < 0) {
        _count--;
        _deleted--;
      }
    }
  }
  else {
    throw std::logic_error("Error in function \
\"void TArchive<T>::push_front(T value)\": wrong position value.");
  }
  if (this->deleted() > 0) {
    _deleted--;
  }
  this->sort();

}




template <typename T>
TArchive<T>::~TArchive() {
  delete[] _data;
  _data = nullptr;
}

template <typename T>
inline bool TArchive<T>::empty() const noexcept {
  return _size == 0;
}

template <typename T>
inline bool TArchive<T>::full() const noexcept {
  return _size == _capacity;
}

template <typename T>
TArchive<T>& TArchive<T>::insert(const T* arr, size_t n, size_t pos) {
  if (_size == 0 && pos > _size) {
    for (int i = 0; i < n; i++) {
      _data[i] = arr[i];
      _states[i] = State::busy;
      _size++;
    }
    this->sort();
    int _count = n;
    if (_deleted > 0) {
      while (_deleted < 0 || _count < 0) {
        _count--;
        _deleted--;
      }
    }



    return *this;
  }
  if (_size < pos) {
    throw std::logic_error("Error in function \
\"TArchive<T>& insert(const T* arr, size_t n, size_t pos)\": wrong position value.");
    return *this;
  }


  if (_size >= pos) {
    if (this->full()) {
      int t;
      std::cout << "There is not enough space. Enlarge the archive";
      std::cin >> t;
      this->reserve(t);
    }
    else {
      T* new_data = new T[_capacity];
      State* new_states = new State[_capacity];
      for (int i = 0; i < pos; i++) {
        new_data[i] = _data[i];
        new_states[i] = _states[i];
      }for (int i = pos - 1, j = 0; i != n + (pos - 1); i++, j++) {
        new_states[i] = State::busy;
        new_data[i] = arr[j];
        _size++;
      }

      for (int j = pos + n - 1, i = pos; j < _size; j++, i++) {
        new_data[j] = _data[i - 1];
        new_states[j] = _states[i - 1];
      }

      delete[]_data;
      delete[]_states;
      _data = new_data;
      _states = new_states;
      this->sort();
      int _count = n;
      if (_deleted > 0) {
        while (_deleted < 0 || _count < 0) {
          _count--;
          _deleted--;
        }
      }
    }





    return *this;
  }

}


template <typename T>
TArchive<T>& TArchive<T>::insert(T value, size_t pos) {
  if (_size == 0 && pos > _size) {
    _data[pos - 1] = value;
    _size++;
    this->sort();
    int _count = 1;
    if (_deleted > 0) {
      while (_deleted < 0 || _count < 0) {
        _count--;
        _deleted--;
      }
    }
    return *this;
  }
  if (_size < pos) {
    throw std::logic_error("Error in function \
\"TArchive<T>& insert(T value, size_t pos)\": wrong position value.");
    return *this;
  }
  if (_size >= pos) {
    if (this->full()) {
      int n;
      std::cout << "There is not enough space. Enlarge the archive";
      std::cin >> n;
      this->reserve(n);
    }
    else {
      T* new_data = new T[_capacity];
      State* new_states = new State[_capacity];
      for (int i = 0; i < pos; i++) {
        new_data[i] = _data[i];
        new_states[i] = _states[i];
      }
      new_states[pos - 1] = State::busy;
      new_data[pos - 1] = value;
      _size++;
      for (int j = pos; j < _size; j++) {
        new_data[j] = _data[j - 1];
        new_states[j] = _states[j - 1];
      }

      delete[]_data;
      delete[]_states;
      _data = new_data;
      _states = new_states;



      this->sort();
      int _count = 1;
      if (_deleted > 0) {
        while (_deleted < 0 || _count < 0) {
          _count--;
          _deleted--;
        }
      }
      return *this;
    }

  }
}

template <typename T>
TArchive<T>& TArchive<T>::remove_by_index(size_t pos) {
  if (pos > _size || _size == 0) {
    throw std::logic_error("Error in function \
\"TArchive<T>& remove_by_index(size_t pos)\": wrong position value.");
    return *this;
  }if (pos <= _size) {
    _data[pos - 1] = NULL;
    _states[pos - 1] = State::deleted;
    this->sort();
    _size--;
    _deleted++;

    return *this;
  }
}




template <typename T>
TArchive<T>& TArchive<T>::erase(size_t pos, size_t n) {
  if (pos > _size || _size == 0 || n > _size) {
    throw std::logic_error("Error in function \
\"TArchive<T>& remove_by_index(size_t pos)\": wrong position value.");
    return *this;
  }if (pos <= _size) {

    T* new_data = new T[_capacity];
    State* new_states = new State[_capacity];
    for (int i = 0; i < pos; i++) {
      new_data[i] = _data[i];
      new_states[i] = _states[i];
    }for (int i = pos - 1; i < n + pos - 1; i++) {
      new_states[i] = State::deleted;
      new_data[i] = NULL;
    }

    for (int j = pos + n - 1; j < _size; j++) {
      new_data[j] = _data[j];
      new_states[j] = _states[j];
    }

    delete[]_data;
    delete[]_states;
    _data = new_data;
    _states = new_states;
    this->sort();
    _size = _size - n;
    _deleted = _deleted + n;
    return *this;
  }
}


template <typename T>
size_t* TArchive<T>::find_all(T value) const noexcept {

}


template <typename T>
void TArchive<T>::print() const noexcept {
  for (size_t i = 0; i < _size + _deleted; i++) {
    if (_data[i] == NULL) {
      std::cout << "null" << ", ";
    }
    else {
      std::cout << _data[i] << ", ";
    }
  }
}

/*
// ������ ���������� � ��������� ������� ��������� �������
template <typename T>
size_t* TArchive<T>::find_all (T value) const noexcept {
    size_t count = this->count_value(value);
    if (count == 0) { return nullptr; }
    int* found_positions = new int[count + 1];
    found_positions[0] = count;

    // TBD

    return found_positions;
}
*/

