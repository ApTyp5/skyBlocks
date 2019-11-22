//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER__PTRVECTOR_H_
#define PARSER__PTRVECTOR_H_

#include <vector>
template<typename T>
class ptrVector {
 protected:
  std::vector<T *> buffer;

 public:
  explicit ptrVector(size_t size = 0) : buffer(size) {}

  virtual ~ptrVector() {
    for (auto &i : buffer) {
      delete *i;
    }

    buffer.clear();
  }

  ptrVector(ptrVector<T> &ptr_vector) {
    for (auto &i : ptr_vector) {
      buffer.push_back(new T(**i));
    }
  }

  ptrVector(ptrVector<T> &&ptr_vector) noexcept {
    buffer = std::move(ptr_vector.buffer);
    ptr_vector.buffer.clear();
  }

  ptrVector<T> &operator=(const ptrVector<T> &ptr_vector) {
    *this = std::move(ptrVector<T>(ptr_vector));
  }

  ptrVector<T> &operator=(ptrVector<T> &&ptr_vector) noexcept {
    *this = std::move(ptrVector<T>(ptr_vector));
    ptr_vector.buffer.clear();
  }
};
#endif //PARSER__PTRVECTOR_H_
