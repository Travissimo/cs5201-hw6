// FileName:   upper_triangular_matrix.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function declaration for the UpperTriangularMatrix derived class 

#ifndef UPPER_TRIANGULAR_MATRIX_H
#define UPPER_TRAINGULAR_MATRIX_H

#include "matrix.h"
#include "square_matrix.h"

template <class T>
class UpperTriangularMatrix;

template <class T>
UpperTriangularMatrix<T> operator*(const T& lhs, const UpperTriangularMatrix<T>& rhs);

template <class T>
class UpperTriangularMatrix : public Matrix<T>
{
private:
  Vector<Vector<T>> m_uppertri;

public:

  //Description: Size accessor
  //PRE: Vector<T>.getSize() must be defined for any type T
  //POST: value is returned
  virtual int getSize() const {return m_uppertri.getSize();}

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

  //Description: referencing a single datum
  //PRE: none
  //POST: datum at position (*this)[i][j] is returned by reference so it may be 
  //      changed. RangeError object is thrown if i is outside the range
  //      [0, getSize() - 1] or if j is outside the range [i, getSize() - 1]
  T& ref(const int i, const int j);

  //Description: changes size of UpperTriangularMatrix
  //PRE: none
  //POST: calling object changed to size n x n. SizeError object is thrown if
  //      n < 0.
  virtual void setSize(const int n);

  //Description: UpperTriangularMatrix assignment
  //PRE: = operator must be defined for any type Vector<T> with Vector<T>
  //POST: rhs is copied/moved into the calling object
  UpperTriangularMatrix<T>& operator=(const UpperTriangularMatrix<T>& rhs);

  //Description: Constant assignment
  //PRE: = operator must be defined for any type Vector<T> with T
  //POST: Every data point in the diagonal is made equal to rhs, and the 
  //      calling object is returned
  UpperTriangularMatrix<T>& operator=(const T& rhs);

  //Description: UpperTriangularMatrix addition
  //PRE: + binary operator must be defined for any type Vector<T> with Vector<T>
  //     rhs.getSize() must be equal to getSize()
  //POST: returns the sum of the caling object with rhs
  UpperTriangularMatrix<T> operator+(const UpperTriangularMatrix<T>& rhs) const;

  //Description: UpperTriangularMatrix addition assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the sum of the calling object and rhs to the calling object, then
  //      returns the calling object
  UpperTriangularMatrix<T>& operator+=(const UpperTriangularMatrix<T>& rhs);

  //Description: UpperTriangularMatrix negation
  //PRE: - unary operator must be defined for any type Vector<T>
  //POST: returns the negation of the calling object
  UpperTriangularMatrix<T> operator-() const;

  //Description: UpperTriangularMatrix subtraction
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: returns the difference of the calling object with rhs
  UpperTriangularMatrix<T> operator-(const UpperTriangularMatrix<T>& rhs) const;

  //Description: UpperTriangularMatrix subtraction assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the difference of the calling object and rhs to the calling object,
  //      then returns the calling object
  UpperTriangularMatrix<T>& operator-=(const UpperTriangularMatrix<T>& rhs);

  //Description: UpperTriangularMatrix Multiplication
  //PRE: * operator must be defined for any type T with T
  //     rhs.getSize() must be equal to getSize()
  //POST: the product of the calling object and rhs is returned
  UpperTriangularMatrix<T> operator*(const UpperTriangularMatrix<T>& rhs) const;

  //Description: SquareMatrix Multiplication
  //PRE: * operator must be defined for any type T with T
  //     rhs.getSize() must be equal to getSize()
  //POST: the product of the calling object and rhs is returned
  SquareMatrix<T> operator*(const SquareMatrix<T>& rhs) const;

  //Description: Scalar product (T * UpperTriangularMatrix<T>)
  //PRE: * operator must be defined for any type T with T
  //POST: The scalar product of the calling object with rhs is returned
  UpperTriangularMatrix<T> operator*(const T& rhs) const;

  //Description: Scalar product (UpperTriangularMatrix<T> * T)
  //PRE: none
  //POST: The scalar product of the calling object with rhs is returned
  friend UpperTriangularMatrix<T> (::operator*<>)(const T& lhs, const UpperTriangularMatrix<T>& rhs);

  //Description: UpperTriangularMatrix output
  //PRE: << must be defined for ostream with any type Vector<T>
  //POST: a user friendly version of the DiagonalMatrix object is output to out
  virtual void print(ostream& out) const;

  //Description: UpperTriangularMatrix input
  //PRE: >> must be defined for ifstream with any type Vector<T>
  //POST: data fro in is input into the DiagonalMatrix
  virtual void input(ifstream& in);

};

#include "upper_triangular_matrix.hpp"
#endif