// FileName:   tridiagonal_matrix.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function declaration for the TridiagonalMatrix derived class 

#ifndef TRIDIAGONAL_MATRIX_H
#define TRIDIAGONAL_MATRIX_H

#include "matrix.h"
#include "square_matrix.h"
#include "vector.h"

template <class T>
class TridiagonalMatrix;

template <class T>
TridiagonalMatrix<T> operator*(const T& lhs, const TridiagonalMatrix<T>& rhs);

template <class T>
class TridiagonalMatrix : public Matrix<T>
{
private:
  Vector<T> m_maindiag;
  Vector<T> m_upperdiag;
  Vector<T> m_lowerdiag;

public:
  
  //Description: Size accessor
  //PRE: Vector<T>.getSize() must be defined for any type T
  //POST: value is returned
  virtual int getSize() const {return m_maindiag.getSize();}

  //Description: ith Row accessor
  //PRE: none
  //POST: value is returned. RangeError object is thrown if i is outside the range 
  //      [0, getSize() - 1]
  virtual Vector<T> getRow(const int i) const;

  //Description: ith Column accessor
  //PRE: none
  //POST: value is returned. RangeError object is thrown if i is outside the range
  //      [0, getSize() - 1]
  virtual Vector<T> getCol(const int i) const;

  //Description: subscripting as a const
  //PRE: none
  //POST: Vector at position i is returned as a const. RangeError object is thrown
  //      if i is outside the range [0, getSize() - 1]
  virtual Vector<T> operator[](const int i) const;

  //Description: changes size of TridiagonalMatrix
  //PRE: none
  //POST: calling object changed to size n x n. SizeError object is thrown if
  //      n < 0.
  virtual void setSize(const int n);

  //Description: TridiagonalMatrix assignment
  //PRE: = operator must be defined for any type Vector<T> with Vector<T>
  //POST: rhs is copied/moved into the calling object
  TridiagonalMatrix<T>& operator=(const TridiagonalMatrix<T>& rhs);

  //Description: Constant assignment
  //PRE: = operator must be defined for any type Vector<T> with T
  //POST: Every data point in the diagonal is made equal to rhs, and the 
  //      calling object is returned
  TridiagonalMatrix<T>& operator=(const T& rhs);

  //Description: TridiagonalMatrix addition
  //PRE: + binary operator must be defined for any type Vector<T> with Vector<T>
  //     rhs.getSize() must be equal to getSize()
  //POST: returns the sum of the caling object with rhs
  TridiagonalMatrix<T> operator+(const TridiagonalMatrix<T>& rhs) const;

  //Description: TridiagonalMatrix addition assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the sum of the calling object and rhs to the calling object, then
  //      returns the calling object
  TridiagonalMatrix<T>& operator+=(const TridiagonalMatrix<T>& rhs);

  //Description: TridiagonalMatrix negation
  //PRE: - unary operator must be defined for any type Vector<T>
  //POST: returns the negation of the calling object
  TridiagonalMatrix<T> operator-() const;

  //Description: TridiagonalMatrix subtraction
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: returns the difference of the calling object with rhs
  TridiagonalMatrix<T> operator-(const TridiagonalMatrix<T>& rhs) const;

  //Description: TridiagonalMatrix subtraction assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the difference of the calling object and rhs to the calling object,
  //      then returns the calling object
  TridiagonalMatrix<T>& operator-=(const TridiagonalMatrix<T>& rhs);

  //Description: TridiagonalMatrix Multiplication
  //PRE: * operator must be defined for any type T with T
  //     rhs.getSize() must be equal to getSize()
  //POST: the product of the calling object and rhs is returned
  SquareMatrix<T> operator*(const TridiagonalMatrix<T>& rhs) const;

  //Description: Scalar product (T * TridiagonalMatrix<T>)
  //PRE: * operator must be defined for any type T with T
  //POST: The scalar product of the calling object with rhs is returned
  TridiagonalMatrix<T> operator*(const T& rhs) const;

  //Description: Scalar product (TridiagonalMatrix<T> * T)
  //PRE: none
  //POST: The scalar product of the calling object with rhs is returned
  friend TridiagonalMatrix<T> (::operator*<>)(const T& lhs, const TridiagonalMatrix<T>& rhs);

  //Description: TridiagonalMatrix output
  //PRE: << must be defined for ostream with any type Vector<T>
  //POST: a user friendly version of the DiagonalMatrix object is output to out
  virtual void print(ostream& out) const;

  //Description: TridiagonalMatrix input
  //PRE: >> must be defined for ifstream with any type Vector<T>
  //POST: data fro in is input into the DiagonalMatrix
  virtual void input(ifstream& in);

};

#include "tridiagonal_matrix.hpp"
#endif