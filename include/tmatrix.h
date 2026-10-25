// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;

public:
  TDynamicVector(size_t size = 1) : sz(size) // конструктор по умолчанию 
  {
    if (sz == 0)
      throw std::out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }

  TDynamicVector(const T* arr, size_t s) : sz(s) // конструктор иницилизатор 
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v) // констуруктор копирования 
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }

  TDynamicVector(TDynamicVector&& v) noexcept //конструктор перемещения 
  {
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
  }

  ~TDynamicVector() 
  {
      delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& v) //оператор копирования 
  {
      if (this == &v)
          return *this;

      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);

      return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept //оператор премещения-присваивания  
  {
      if (this == &v)
          return *this;

      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;

      return *this;
  }

  size_t size() const noexcept { return sz; }

  T& operator[](size_t ind) // индексация
  {
      return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }

  
  T& at(size_t ind) // индексация с контролем
  {
    if (ind >= sz)
        throw std::out_of_range("Accessing a non-existent element");
    return pMem[ind];

  }

  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw std::out_of_range("Accessing a non-existent element");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;

      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i])
              return false;

      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return true;

      return !(*this == v); 
  }

  // скалярные операции
  TDynamicVector operator/(const T value) const
  {
      TDynamicVector tmp(*this); //используем ранее созданный конструктор копирования 
      tmp /= value;
      return tmp;
  }

  TDynamicVector& operator/=(T value)
  {
      if (value == 0)
          throw std::invalid_argument("ERROR");

      for (size_t i = 0; i < sz; i++)
          pMem[i] = pMem[i] / value;
      return *this;
  }

  TDynamicVector operator*(const T value) const
  {
      TDynamicVector tmp(*this);
      tmp *= value;
      return tmp;
  }

  TDynamicVector& operator*=(T value)
  {
      for (size_t i = 0; i < sz; i++)
          pMem[i] = pMem[i] * value;
      return *this;
  } 


  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const
  {
      if (sz != v.sz)
          throw std::out_of_range("The operation is not available for vectors of different sizes");

      TDynamicVector res(sz);
      res += v;
      return res;
  }

  TDynamicVector& operator+=(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::out_of_range("The operation is not available for vectors of different sizes");

      for (size_t i = 0; i < sz; i++)
          pMem[i] += v.pMem[i];
      return *this;
  }

  TDynamicVector operator-(const TDynamicVector& v) const
  {
      if (sz != v.sz)
          throw std::out_of_range("The operation is not available for vectors of different sizes");

      TDynamicVector res(sz);
      res -= v;
      return res;
  }

  TDynamicVector& operator-=(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::out_of_range("The operation is not available for vectors of different sizes");

      for (size_t i = 0; i < sz; i++)
          pMem[i] -= v.pMem[i];
      return *this;
  }

  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw std::out_of_range("The operation is not available for vectors of different sizes");

      T result = 0;
      for (size_t i = 0; i < sz; i++)
          result += pMem[i] * v.pMem[i];
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend std::istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }

  friend std::ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }

};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
