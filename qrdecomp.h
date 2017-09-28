// FileName:   qrdecomp.h
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function declaration for the QRdecomp function class 

#ifndef QRDECOMP_H
#define QRDECOMP_H

#include "vector.h"
#include "upper_triangular_matrix.h"

class ZeroError
{
public:
  ZeroError(const int i) : m_location(i) {}
  int badLocation() const {return m_location;}
private:
  int m_location;
};

template <class T>
class QRdecomp
{
public:
  void operator()(const SquareMatrix<T>& A,
                        SquareMatrix<T>& Q,
                        UpperTriangularMatrix<T>& R);
};

#include "qrdecomp.hpp"
#endif