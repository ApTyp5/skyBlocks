//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER__PTRVECTOR_H_
#define PARSER__PTRVECTOR_H_

#include <vector>

template<typename T>
class ptrVector
{
protected:
    std::vector<T *> buffer;

public:
    explicit ptrVector(size_t size = 0)
        : buffer(size)
    {}

    virtual ~ptrVector()
    {
        for (auto i = buffer.begin(); i != buffer.end(); i++) {
            delete *i;
        }

        buffer.clear();
    }

    ptrVector(const ptrVector<T> &ptr_vector)
    {
        for (auto &i : ptr_vector) {
            buffer.push_back(new T(*i));
        }
    }

    ptrVector(ptrVector<T> &&ptr_vector) noexcept
    {
        buffer = std::move(ptr_vector.buffer);
        ptr_vector.buffer.clear();
    }

    ptrVector<T> &operator=(const ptrVector<T> &ptr_vector)
    {
        *this = std::move(ptrVector<T>(ptr_vector));
    }

    ptrVector<T> &operator=(ptrVector<T> &&ptr_vector) noexcept
    {
        *this = std::move(ptrVector<T>(ptr_vector));
        ptr_vector.buffer.clear();
    }

    void push_back(T *element)
    {
        if (element == nullptr)
            throw std::exception();
        buffer.push_back(element);
    }

    T *pop_back()
    {
        if (buffer.empty())
            throw std::exception();
        T *retVal = buffer.back();
        buffer.pop_back();
        return retVal;
    }

    size_t size() const
    {
      return buffer.size();
    }

  T *&back() {
    if (buffer.empty())
      throw std::exception();
    return buffer.back();
  }

  void clear() {
    for (auto i : buffer) {
      delete i;
    }
    buffer.clear();
  }

  T *&operator[](size_t index) {
    if (index >= size())
      throw std::exception();
    return buffer[index];
  }

  const T *operator[](size_t index) const {
        if (index >= size())
            throw std::exception();
        return buffer[index];
    }

    typename std::vector<T *>::iterator begin()
    {
        return buffer.begin();
    }

    typename std::vector<T *>::iterator end()
    {
        return buffer.end();
    }

    typename std::vector<T *>::const_iterator begin() const
    {
        return buffer.cbegin();
    }

    typename std::vector<T *>::const_iterator end() const
    {
        return buffer.cend();
    }

    typename std::vector<T *>::const_iterator cbegin() const
    {
        return buffer.cbegin();
    }

    typename std::vector<T *>::const_iterator cend() const
    {
        return buffer.cend();
    }

    bool operator==(const ptrVector<T> &ptrVector) const
    {
        if (size() != ptrVector.size())
            return false;

        for (size_t i = 0; i < size(); i++)
            if (*operator[](i) != *ptrVector[i])
                return false;

        return true;
    }

    bool operator!=(const ptrVector<T> &ptrVector) const
    {
        return !operator==(ptrVector);
    }
};
#endif //PARSER__PTRVECTOR_H_
