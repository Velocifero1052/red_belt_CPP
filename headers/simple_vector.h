//
// Created by Rakhmon Radjabov on 12/07/23.
//

#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
  SimpleVector();

  explicit SimpleVector(size_t size);

  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();

  T* end();

  size_t Size() const;

  size_t Capacity() const;

  void PushBack(const T& value);

private:
  T* data;
  size_t size;
  size_t capacity;
};

template<typename T>
SimpleVector<T>::SimpleVector() {
  capacity = 0;
  size = 0;
  data = nullptr;
}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size){
  data = new T[size];
  this->capacity = size;
  this->size = size;
}

template<typename T>
SimpleVector<T>::~SimpleVector(){
  delete[] data;
}

template<typename T>
T& SimpleVector<T>::operator[](size_t index) {
  return data[index];
}

template<typename T>
T* SimpleVector<T>::begin() {
  return data;
}

template<typename T>
T* SimpleVector<T>::end() {
  return data + size;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
  return size;
}

template<typename T>
size_t  SimpleVector<T>::Capacity() const {
  return capacity;
}
template<typename T>
void SimpleVector<T>::PushBack(const T& value) {
  if (capacity == 0) {
    data = new T[1];
    data[size] = value;
    size++;
    capacity++;
  } else if (capacity > size) {
    data[size] = value;
    size++;
  } else {
    capacity *= 2;
    T* new_data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
      new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    data[size] = value;
    size++;
  }
}
