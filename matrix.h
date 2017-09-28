// FileName:   matrix.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Declaration of the Matrix interface base class

#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <iomanip>
#include <algorithm>
#include <utility>

template <class T>
class Matrix 
{
public:
  virtual int getSize()                               const = 0;
  
  virtual Vector<T> getRow(const int i)               const = 0;
  virtual Vector<T> getCol(const int i)               const = 0;
  
  //virtual Vector<T>& operator[](const int i)                = 0;
  
  virtual Vector<T> operator[](const int i)           const = 0;
  virtual void setSize(const int n)                         = 0;
  /*
  virtual Matrix<T>& operator=(const Matrix<T>& rhs)        = 0;
  virtual Matrix<T>& operator=(const T& rhs)                = 0;
  virtual Matrix<T> operator+(const Matrix<T>& rhs)   const = 0;
  virtual Matrix<T>& operator+=(const Matrix<T>& rhs) const = 0;
  virtual Matrix<T> operator-()                       const = 0;
  virtual Matrix<T> operator-(const Matrix<T>& rhs)   const = 0;
  virtual Matrix<T> operator-=(const Matrix<T>& rhs)        = 0;
  virtual Matrix<T> operator*(const Matrix<T>& rhs)   const = 0;
  virtual Matrix<T> operator*(const T& rhs)           const = 0;

  template <class U>
  friend Matrix<U> operator*(const U& lhs, const Matrix<U>& rhs);
  virtual Matrix<T> product(const T& lhs)             const = 0;

*/  
  template <class U>
  friend ostream& operator<<(ostream& out, const Matrix<U>& rhs);
  virtual void print(ostream& out)                    const = 0;

  template <class U>
  friend ifstream& operator>>(ifstream& in, Matrix<U>& rhs);
  virtual void input(ifstream& in)                          = 0;

  /*
  virtual Matrix<T> transpose()                       const = 0;
  */
  //virtual void swapRows(const int n, const int m)           = 0;

  virtual ~Matrix() {};
  
};
#include "matrix.hpp"
#endif