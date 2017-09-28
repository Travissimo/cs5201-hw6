// FileName:   diagonal_matrix.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function declaration for the DiagonalMatrix derived class 

#ifndef DIAGONAL_MATRIX_H
#define DIAGONAL_MATRIX_H

#include "matrix.h"

template <class T>
class DiagonalMatrix;

template <class T>
DiagonalMatrix<T> operator*(const T& lhs, const DiagonalMatrix<T>& rhs);

template <class T>
class DiagonalMatrix : public Matrix<T>
{
private:
  Vector<T> m_diagonal;

public:
  
  //Description: Size accessor
  //PRE: Vector<T>.getSize() must be defined for any type T
  //POST: value is returned
  virtual int getSize() const {return m_diagonal.getSize();}

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

  //Description: changes size of DiagonalMatrix
  //PRE: none
  //POST: calling object changed to size n x n. SizeError object is thrown if
  //      n < 0.
  virtual void setSize(const int n);

  //Description: DiagonalMatrix assignment
  //PRE: = operator must be defined for any type Vector<T> with Vector<T>
  //POST: rhs is copied/moved into the calling object
  DiagonalMatrix<T>& operator=(const DiagonalMatrix<T>& rhs);

  //Description: Constant assignment
  //PRE: = operator must be defined for any type Vector<T> with T
  //POST: Every data point in the diagonal is made equal to rhs, and the 
  //      calling object is returned
  DiagonalMatrix<T>& operator=(const T& rhs);
  
  //Description: DiagonalMatrix addition
  //PRE: + binary operator must be defined for any type Vector<T> with Vector<T>
  //     rhs.getSize() must be equal to getSize()
  //POST: returns the sum of the caling object with rhs
  DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& rhs) const;

  //Description: DiagonalMatrix addition assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the sum of the calling object and rhs to the calling object, then
  //      returns the calling object
  DiagonalMatrix<T>& operator+=(const DiagonalMatrix<T>& rhs);
  
  //Description: DiagonalMatrix negation
  //PRE: - unary operator must be defined for any type Vector<T>
  //POST: returns the negation of the calling object
  DiagonalMatrix<T> operator-() const;

  //Description: DiagonalMatrix subtraction
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: returns the difference of the calling object with rhs
  DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& rhs) const;

  //Description: DiagonalMatrix subtraction assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the difference of the calling object and rhs to the calling object,
  //      then returns the calling object
  DiagonalMatrix<T>& operator-=(const DiagonalMatrix<T>& rhs);

  //Description: DiagonalMatrix Multiplication
  //PRE: * operator must be defined for any type T with T
  //     rhs.getSize() must be equal to getSize()
  //POST: the product of the calling object and rhs is returned
  DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& rhs) const;

  //Description: Scalar product (T * DiagonalMatrix<T>)
  //PRE: * operator must be defined for any type T with T
  //POST: The scalar product of the calling object with rhs is returned
  DiagonalMatrix<T> operator*(const T& rhs) const;

  //Description: Scalar product (DiagonalMatrix<T> * T)
  //PRE: none
  //POST: The scalar product of the calling object with rhs is returned
  friend DiagonalMatrix<T> (::operator*<>)(const T& lhs, const DiagonalMatrix<T>& rhs);

  //Description: DiagonalMatrix output
  //PRE: << must be defined for ostream with any type Vector<T>
  //POST: a user friendly version of the DiagonalMatrix object is output to out
  virtual void print(ostream& out) const;

  //Description: DiagonalMatrix input
  //PRE: >> must be defined for ifstream with any type Vector<T>
  //POST: data fro in is input into the DiagonalMatrix
  virtual void input(ifstream& in);

};

#include "diagonal_matrix.hpp"
#endif