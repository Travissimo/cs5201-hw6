// FileName:   symmetric_dense_matrix.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function declaration for the SymmetricDenseMatrix derived class

#ifndef SYMMETRIC_DENSE_MATRIX_H
#define SYMMETRIC_DENSE_MATRIX_H

#include "matrix.h"

template <class T> 
class SymmetricDenseMatrix;

template <class T>
SymmetricDenseMatrix<T> operator*(const T& lhs, const SymmetricDenseMatrix<T>& rhs);

template <class T>
class SymmetricDenseMatrix : public Matrix<T>
{
private:
  Vector<Vector<T>> m_lowertri;

public:

  //Description: Size accessor
  //PRE: Vector<T>.getSize() must be defined for any type T
  //POST: value is returned
  virtual int getSize() const {return m_lowertri.getSize();}

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

  //Description: changes size of SymmetricDenseMatrix
  //PRE: none
  //POST: calling object changed to size n x n. SizeError object is thrown if
  //      n < 0.
  virtual void setSize(const int n);

  //Description: SymmetricDenseMatrix assignment
  //PRE: = operator must be defined for any type Vector<T> with Vector<T>
  //POST: rhs is copied/moved into the calling object
  SymmetricDenseMatrix<T>& operator=(const SymmetricDenseMatrix<T>& rhs);

  //Description: Constant assignment
  //PRE: = operator must be defined for any type Vector<T> with T
  //POST: Every data point in the diagonal is made equal to rhs, and the 
  //      calling object is returned
  SymmetricDenseMatrix<T>& operator=(const T& rhs);

  //Description: SymmetricDenseMatrix addition
  //PRE: + binary operator must be defined for any type Vector<T> with Vector<T>
  //     rhs.getSize() must be equal to getSize()
  //POST: returns the sum of the caling object with rhs
  SymmetricDenseMatrix<T> operator+(const SymmetricDenseMatrix<T>& rhs) const;

  //Description: SymmetricDenseMatrix addition assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the sum of the calling object and rhs to the calling object, then
  //      returns the calling object
  SymmetricDenseMatrix<T>& operator+=(const SymmetricDenseMatrix<T>& rhs);

  //Description: SymmetricDenseMatrix negation
  //PRE: - unary operator must be defined for any type Vector<T>
  //POST: returns the negation of the calling object
  SymmetricDenseMatrix<T> operator-() const;

  //Description: SymmetricDenseMatrix subtraction
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: returns the difference of the calling object with rhs
  SymmetricDenseMatrix<T> operator-(const SymmetricDenseMatrix<T>& rhs) const;

  //Description: SymmetricDenseMatrix subtraction assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the difference of the calling object and rhs to the calling object,
  //      then returns the calling object
  SymmetricDenseMatrix<T>& operator-=(const SymmetricDenseMatrix<T>& rhs);

  //Description: SymmetricDenseMatrix Multiplication
  //PRE: * operator must be defined for any type T with T
  //     rhs.getSize() must be equal to getSize()
  //POST: the product of the calling object and rhs is returned
  SymmetricDenseMatrix<T> operator*(const SymmetricDenseMatrix<T>& rhs) const;

  //Description: Scalar product (T * SymmetricDenseMatrix<T>)
  //PRE: * operator must be defined for any type T with T
  //POST: The scalar product of the calling object with rhs is returned
  SymmetricDenseMatrix<T> operator*(const T& rhs) const;

  //Description: Scalar product (SymmetricDenseMatrix<T> * T)
  //PRE: none
  //POST: The scalar product of the calling object with rhs is returned
  friend SymmetricDenseMatrix<T> (::operator*<>)(const T& lhs, const SymmetricDenseMatrix<T>& rhs);
  
  //Description: SymmetricDenseMatrix output
  //PRE: << must be defined for ostream with any type Vector<T>
  //POST: a user friendly version of the DiagonalMatrix object is output to out
  virtual void print(ostream& out) const;

  //Description: SymmetricDenseMatrix input
  //PRE: >> must be defined for ifstream with any type Vector<T>
  //POST: data fro in is input into the DiagonalMatrix
  virtual void input(ifstream& in);

};

#include "symmetric_dense_matrix.hpp"
#endif