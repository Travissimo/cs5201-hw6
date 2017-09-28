// FileName:   matrix.hpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function definitions for functions declared in matrix.h

template <class T>
ostream& operator<<(ostream& out, const Matrix<T>& rhs)
{
  rhs.print(out);
  return out;
}

template <class T>
ifstream& operator>>(ifstream& in, Matrix<T>& rhs)
{
  rhs.input(in);
  return in;
}