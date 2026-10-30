// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>

const size_t MAX_VECTOR_SIZE = 100000000;
const size_t MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;

public:

  explicit TDynamicVector(size_t size = 1) : sz(size) // конструктор по умолчанию 
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw std::out_of_range("Vector size should be greater than zero and less MAX_VECTOR_SIZE");

    pMem = new T[sz]();
  }

  TDynamicVector(const T* arr, size_t s) : sz(s) // конструктор иницилизатор 
  {
    if (arr == nullptr) 
          throw std::invalid_argument("Array == nullptr!");

    if (sz == 0 || sz > MAX_VECTOR_SIZE)
        throw std::out_of_range("Vector size should be greater than zero and less MAX_VECTOR_SIZE");

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

      TDynamicVector result(*this);
      result += v;
      return result;
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

      TDynamicVector result(*this);
      result -= v;
      return result;
  }

  TDynamicVector& operator-=(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::out_of_range("The operation is not available for vectors of different sizes");

      for (size_t i = 0; i < sz; i++)
          pMem[i] -= v.pMem[i];
      return *this;
  }

  T operator*(const TDynamicVector& v) const 
  {
      if (sz != v.sz)
          throw std::out_of_range("The operation is not available for vectors of different sizes");

      T result = T();
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
  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }

  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
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

  static size_t checkSize(size_t s) //улучшение проверки для выделения памяти в матрице
  {
      if (s == 0 || s > MAX_MATRIX_SIZE)
          throw std::out_of_range("Incorrectly specified matrix");
      return s;
  }

public:

  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;

  explicit TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(checkSize(s))
  {
      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(sz);
  }

  bool operator==(const TDynamicMatrix& m) const noexcept   // сравнение
  {
      if (sz != m.sz) 
          return false;

      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != m.pMem[i]) 
              return false;

      return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept 
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const
  {
      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              result[i][j] = pMem[i][j] * val;

      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if (sz != v.size())
          throw std::invalid_argument("Multiplying a matrix by a vector is not possible");

      TDynamicVector<T> result(sz);

      for (size_t i = 0; i < sz; i++)
      {
          T sum = T();
          for (size_t j = 0; j < sz; j++)
              sum += pMem[i][j] * v[j];
          result[i] = sum;
      }
      
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const
  {
      if (m.sz != sz) 
          throw std::invalid_argument("Matrix addition is not possible");

      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              result[i][j] = pMem[i][j] + m[i][j];

      return result;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m) const 
  {
      if (m.sz != sz)
          throw std::invalid_argument("Matrix subtraction is not possible");

      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              result[i][j] = pMem[i][j] - m[i][j];

      return result;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
      if (sz != m.sz)
          throw std::invalid_argument("Matrix multiplication is not possible");

      TDynamicMatrix result(sz); 

      for (size_t i = 0; i < sz; i++) // цикл для прохода по строкам исходной матрицы
          for (size_t k = 0; k < sz; k++)   // выбираем строку для умножения из матрицы m
          {
              const T element = pMem[i][k]; // выбираем элемент, на который будем умножать элементы строчки k из матрицы m
              for (size_t j = 0; j < sz; j++) // пробегаемся по элементам строчки k матрицы m
                  result[i][j] += element * m[k][j];
          }
      return result;
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          for (size_t j = 0; j < v.sz; j++)
              istr >> v.pMem[i][j];

      return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) 
      {
          for (size_t j = 0; j < v.sz; j++)
              ostr << v.pMem[i][j] << ' ';
          ostr << '\n';
      }

      return ostr;
  }
};

#endif
