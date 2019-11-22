//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER__PTRVECTOR_H_
#define PARSER__PTRVECTOR_H_

#include <vector>
template<typename T>
class ptrVector : public std::vector<T *> {
 public:
  ptrVector(size_t size = 0) : std::vector<T *>(size) {}

  virtual ~ptrVector() {
    for (auto &i : *this) {
      delete *i;
    }
  }

  ptrVector(ptrVector<T> &ptr_vector) {
    for (auto &i : ptr_vector) {
      this->push_back(new T(*i));
    }
  }

  ptrVector<T> &operator=(ptrVector<T> ptr_vector) {
    *this = ptrVector<T>(ptr_vector);
  }

  ptrVector(ptrVector<T> &&ptr_vector) noexcept {
    *this = std::move(ptr_vector);
  }
};
#endif //PARSER__PTRVECTOR_H_
