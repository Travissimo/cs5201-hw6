// FileName:   square_matrix.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
//Assignment:  6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function declarations for the templated SquareMatrix derived class.

#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "matrix.h"

template <class T>
class SquareMatrix;

template <class T>
SquareMatrix<T> operator*(const T& lhs, const SquareMatrix<T>& rhs);

template <class T>
class SquareMatrix : public Matrix<T>
{
private:
  Vector<Vector<T>> m_matrix; 

public:

  //Description: Size accessor
  //PRE: Vector<Vector<T>>.getSize() must be defined for any type T
  //POST: value is returned
  virtual int getSize() const {return m_matrix.getSize();}

  //Description: ith Row accessor
  //PRE: none
  //POST: value is returned. RangeError object is thrown if i is outside the range
  //      [0, getSize() - 1]
  virtual Vector<T> getRow(const int i) const;

  //Description: ith Column accessor
  //PRE: The following must be defined for any type T
  //       Vector<T>.setSize()
  //       Vector<T>[]
  //       T = T
  //POST: value is returned. RangeError object is thrown if i is outside the range
  //      [0, getSize() - 1]
  virtual Vector<T> getCol(const int i) const;

  //Description: subscripting by reference
  //PRE: none
  //POST: vector at position i is returned by reference. RangeError object is thrown
  //      if i is outside the range [0, getSize() - 1]
  Vector<T>& operator[](const int i);
  
  //Description: subscripting as a const
  //PRE: none
  //POST: vector at position i is returned as a const. RangeError object is thrown
  //      if i is outside the range [0, getSize() - 1]
  virtual Vector<T> operator[](const int i) const;
  
  //Description: changes size of SquareMatrix
  //PRE: none
  //POST: calling object changed to size n x n. SizeError object is thrown if
  //      n < 0.
  virtual void setSize(const int n);

  //Description: Column Vector assignment
  //PRE: The following must be defined for any type T
  //      Vector<T>[]
  //      T=T
  //POST: calling object's ith column is made equal to source. RangeError object is 
  //      thrown if i is outside the range [0, getSize() - 1].
  void setCol(const int i, const Vector<T>& source);

  //Description: Row Vector assignment
  //PRE: source.getSize() must be equal to getSize()
  //     The following must be defined for any type T
  //      Vector<T> = Vector<T>
  //POST: calling object's ith row is made equal to source. RangeError object is 
  //      thrown if i is outside the range [0, getSize() - 1].
  void setRow(const int i, const Vector<T>& source);
  
  //Description: SquareMatrix assignment
  //PRE: = operator must be defined for any type Vector<Vector<T>> with 
  //     Vector<Vector<T>>
  //POST: The SquareMatrix rhs takes advantage of Vector's move semantics in order 
  //      to move/copy the SquareMatrix into the calling object. The calling object is 
  //      returned.
  SquareMatrix<T>& operator=(const SquareMatrix<T>& rhs);
  
  //Description: Constant assignment
  //PRE: = operator must be defined for any type Vector<Vector<T>> with T
  //POST: Every data point in the calling object is made equal to rhs, and the
  //      calling object is returned
  SquareMatrix<T>& operator=(const T& rhs);

  //Description: SquareMatrix addition
  //PRE: + binary operator must be defined for any type Vector<Vector<T>> with 
  //     Vector<Vector<T>>
  //     rhs.getSize() must be equal to getSize()
  //POST: returns the sum of the calling object with rhs
  SquareMatrix<T> operator+(const SquareMatrix<T>& rhs) const;
  
  //Description: SquareMatrix addition assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the sum of the calling object and rhs to the calling object, then
  //      returns the calling object
  SquareMatrix<T>& operator+=(const SquareMatrix<T>& rhs);
  
  //Description: SquareMatrix negation
  //PRE: - unary operator must be defined for any type Vector<Vector<T>>
  //POST: returns the negation of the calling object
  SquareMatrix<T> operator-() const;
  
  //Description: SquareMatrix subtraction
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: returns the difference of the calling object with rhs
  SquareMatrix<T> operator-(const SquareMatrix<T>& rhs) const;
  
  //Description: SquareMatrix subtraction assignment
  //PRE: rhs.getSize() must be equal to getSize()
  //POST: assigns the difference of the calling object and rhs to the calling object,
  //      then returns the calling object
  SquareMatrix<T>& operator-=(const SquareMatrix<T>& rhs);
  
  //Description: SquareMatrix Multiplication
  //PRE: * binary operator must be defined for any type T with T
  //     * binary operator must be defined for any type Vector<T> with Vector<T>
  //     Vector<T>[] must be defined for any type T
  //     rhs.getSize() must be equal to getSize()
  //POST: The product of the calling object and rhs is returned
  SquareMatrix<T> operator*(const SquareMatrix<T>& rhs) const;

  //Description: Scalar product (T * SquareMatrix<T>)
  //PRE: * binary operator must be defined for any type T with T
  //     = operator must be defined for any type T with T
  //POST: The scalar product of the calling object with rhs is returned
  SquareMatrix<T> operator*(const T& rhs) const;
  
  //Description: Scalar product (SquareMatrix<T> * T)
  //PRE: none
  //POST: The scalar product of lhs and rhs is returned
  friend SquareMatrix<T> (::operator*<>)(const T& lhs, const SquareMatrix<T>& rhs);

  //Description: SquareMatrix output
  //PRE: << must be defined for ostream with any type Vector<T>
  //POST: a user friendly version of the SquareMatrix object is output to out
  virtual void print(ostream& out) const;
  
  //Description: SquareMatrix input
  //PRE: >> must be defined for istream with any type Vector<T>
  //POST: data from in is input into the SquareMatrix
  virtual void input(ifstream& in);

  //Description: SquareMatrix transpose
  //PRE: none
  //POST: transpose of the calling object is returned
  SquareMatrix<T> transpose() const;

  //Description: Swap Rows function
  //PRE: none
  //POST: the calling object's row n and row m are swapped. RangeError object is 
  //      thrown if n or m are outside the range [0, getSize() - 1].
  void swapRows(const int n, const int m);
  
};

#include "square_matrix.hpp"
#endif