// FileName:   qrdecomp.hpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function definition for the QRdecomp function class

template <class T>
void QRdecomp<T>::operator()(const SquareMatrix<T>& A,
                                   SquareMatrix<T>& Q,
                                   UpperTriangularMatrix<T>& R)
{
  // For this function I am using the last three equations found on the back of
  // "The QR Decomposition" handout.
  for (int i = 0; i < A.getSize(); i++)
  {
    Vector<T> temp(A.getSize());
    temp = 0;

    for (int j = 0; j < i; j++)
    {
      // FIRST EQUATION
      R.ref(j,i) = A.getCol(i) * Q.getCol(j);
      
      // SECOND & THIRD EQUATION SUM CALCULATION
      temp += R[j][i] * Q.getCol(j);
    }

    // SECOND & THIRD EQUATION VECTOR DIFFERENCE CALCULATION
    temp = A.getCol(i) - temp;

    // SECOND EQUATION
    R.ref(i,i) = temp.twoNorm();
    if (R[i][i] == 0)
      throw ZeroError(i);

    // THIRD EQUATION
    Q.setCol(i, ((1 / R[i][i]) * temp));
  }

  return;
} 