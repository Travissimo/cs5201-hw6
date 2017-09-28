// FileName:   vector.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function declarations for the templated Vector class

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class RangeError
{
public:
  RangeError(const int i) : m_subscript(i) {}
  int badSubscript() const {return m_subscript;}
private:
  int m_subscript;
};

class SizeError
{
public:
  SizeError(const int i) : m_size(i) {}
  int badSize() const {return m_size;}
private:
  int m_size;
};

template <class T>
class Vector
{
private:
  int m_size;
  T* ptr_to_data;

  //Description: Copy in elements of source
  //PRE: source.m_size must be equal to m_size
  //POST: copies every data point from source into the calling object
  void vectorCopy(const Vector<T>& source);  

public:
  
  //Description: default constructor
  //PRE: none
  //POST: Vector object is constructed with no data and no size
  Vector();                                      

  //Description: size constructor
  //PRE: none
  //POST: Vector object of size n but no data is constructed. SizeError object is
  //      thrown if n > 0.
  Vector(const int n);
  
  //Description: move constructor
  //PRE: none
  //POST: constructs a Vector identical to source using move semantics
  Vector(Vector<T>&& source);
  
  //Description: copy constructor
  //PRE: none 
  //POST: constructs a Vector identical to source 
  Vector(const Vector<T>& source);
  
  //Description: destructor
  //PRE: none
  //POST: deletes a Vector object
  ~Vector();

  //Description: allows any function to gain access to the m_size value
  //PRE: none
  //POST: value is returned
  int getSize() const {return m_size;}
  
  //Description: changes size of Vector
  //PRE: none
  //POST: value is read into m_size. If n < 0, SizeError object is thrown.
  void setSize(const int n);

  //Description: subscripting by reference
  //PRE: none
  //POST: data point at position i is returned by reference. RangeError object is
  //      thrown if is is outside of range [0, m_size-1]
  T& operator[](const int i);
  
  //Description: subscripting as a const
  //PRE: i > 0 and i < m_size
  //POST: data point at position i is returned as a const. RangeError object is 
  //      thrown if is is outside of range [0, m_size-1]
  T operator[](const int i) const;

  //Description: Move Vector assignment
  //PRE: = operator must be defined for any type T with T
  //POST: the Vector rhs is moved into the calling object, and the calling object
  //      is returned
  Vector<T>& operator=(Vector<T>&& rhs);
  
  //Description: Vector assignment
  //PRE: = operator must be defined for any type T with T
  //     Vector<T>.setSize(int) and Vector<T>.vectorCopy(Vector<T>) must be defined
  //     for any type T
  //POST: the Vector rhs is copied into the calling object, and the calling object
  //      is returned
  Vector<T>& operator=(const Vector<T>& rhs);
  
  //Description: Constant assignment
  //PRE: = operator must be defined for any type T with T
  //POST: Every data point in the calling object is made equal to rhs, and the
  //      calling object is returned
  Vector<T>& operator=(const T& rhs);
  
  //Description: Vector to int equal comparison
  //PRE: == operator must be defined for any type T with int
  //     rhs.m_size must be equal to m_size
  //POST: Returns true if every data point in the calling object is equal to rhs
  bool operator==(const int& rhs) const;
  
  //Description: Vector to int not equal comparison
  //PRE: == operator must be defined for any type Vector<T> with int
  //     rhs.m_size must be equal to m_size
  //POST: Returns false if every data point in the calling object is equal to rhs
  bool operator!=(const int& rhs) const;

  //Description: Vector addition
  //PRE: + binary operator must be defined for any type T with T
  //     rhs.m_size must be equal to m_size
  //POST: returns the sum of the calling object with rhs
  Vector<T> operator+(const Vector<T>& rhs) const;
  
  //Description: Vector addition assignment
  //PRE: + binary operator must be defined for any type Vector<T> with Vector<T> 
  //     = operator must be defined for any type Vector<T> with Vector<T>
  //     rhs.m_size must be equal to m_size
  //POST: assigns the sum of the calling object and rhs to the calling object, then
  //      returns the calling object
  Vector<T>& operator+=(const Vector<T>& rhs);
  
  //Description: Vector negation
  //PRE: - unary operator must be defined for any type T
  //POST: returns the negation of the calling object
  Vector<T> operator-() const;
  
  //Description: Vector subtraction
  //PRE: + binary operator must be defined for any type Vector<T> with Vector<T>,
  //     - unary operator must be defined for any type Vector<T>
  //     rhs.m_size must be equal to m_size
  //POST: returns the difference of the calling object with rhs
  Vector<T> operator-(const Vector<T>& rhs) const;
  
  //Description: Vector subtraction assignment
  //PRE: - binary operator must be defined for any type Vector<T> with Vector<T>,
  //     = operator must be defined for any type Vector<T> with Vector<T>
  //     rhs.m_size must be equal to m_size
  //POST: assigns the difference of the calling object and rhs to the calling object,
  //      the returns the calling object
  Vector<T>& operator-=(const Vector<T>& rhs);
  
  //Description: Dot product
  //PRE: += operator must be defined for any type T with T,
  //     * binary operator must be defined for any type T with T
  //     rhs.m_size must be equal to m_size
  //POST: The dot product of the calling object and rhs is returned
  T operator*(const Vector<T>& rhs) const;

  //Description: Scalar product (const * vect)
  //PRE: * binary operator must be defined for any type T with S
  //     = operator must be defined for any type T with (T * S)
  //POST: The scalar product of the calling object with rhs is returned
  Vector<T> operator*(const T& rhs) const;
  
  //Description: Scalar product (vect * const)
  //PRE: * binary operator must be defined for any type Vector<U> with S
  //POST: The scalar product of lhs and rhs is returned
  template <class U>
  friend Vector<U> operator*(const U& lhs, const Vector<U>& rhs);

  //Description: Vector output
  //PRE: << must be defined for ostream with any type U
  //POST: a user friendly version of the Vector object is output to out, out is 
  //      returned
  template <class U>
  friend ostream& operator<<(ostream& out, const Vector<U>& rhs);
  
  //Description: Vector input
  //PRE: >> must be defined for istream with any type T
  //POST: data from in is input into the Vector
  template <class U>
  friend ifstream& operator>>(ifstream& in, const Vector<U>& rhs);

  //Description: 2 norm
  //PRE: = operator must be defined for any type T with int,
  //     += operator must be defined for any type T with (T * T)
  //     * operator must be defined for any type T with T
  //POST: the 2 norm of the calling object is returned
  T twoNorm() const;
};

#include "vector.hpp"
#endif