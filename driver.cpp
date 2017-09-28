// FileName:   driver.cpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Drives the implementation of the Abstract matrix class
//              Takes the first argument from the command line as the file to be
//              read from.

#include "diagonal_matrix.h"
#include "tridiagonal_matrix.h"
#include "lower_triangular_matrix.h"
#include "symmetric_dense_matrix.h"
#include "qrdecomp.h"
#include <stdlib.h>
#include <math.h>

void eigenvalue_calculator(ifstream& in);

const double STOPPING_THRESHOLD = 1e-9;
const int STOPPING_CRITERIA = 1000;

int main (int argc, char *argv[])
{
  try
  {
    if (argc != 2) // check for 2 arguments
    {
      cout << "2 arguments are needed, please try again.";
      cout << "Proper syntax: " << argv[0] << " <filename>" << endl;
    }
    
    else
    {
      ifstream in;
      in.open(argv[1]);
    
      if (!in.is_open()) // check for valid file
      {
        cout << "Could not open file, please try again." << endl;
        cout << "Proper syntax: " << argv[0] <<" <filename>" << endl;
      }
  
      else
      {
        ifstream inDemo;
        inDemo.open("demoData.txt");

        int dataSize;

        // TRIDIAGONAL MATRIX DEMO /////////////////////
        inDemo >> dataSize;

        TridiagonalMatrix<double> my_tri;
        my_tri.setSize(dataSize);
        inDemo >> my_tri;

        cout << "Tridiagonal Matrix my_tri: " << endl;
        cout << my_tri;
        cout << "my_tri * my_tri: " << endl;
        cout << (my_tri * my_tri) << endl << endl;

        // DIAGONAL MATRIX DEMO //////////////////////////
        inDemo >> dataSize;

        DiagonalMatrix<double> my_dia;
        my_dia.setSize(dataSize);
        inDemo >> my_dia;

        cout << "Diagonal Matrix my_dia: " << endl;
        cout << my_dia;
        cout << "my_dia * my_dia: " << endl;
        cout << (my_dia * my_dia) << endl << endl;

        // UPPER TRIANGULAR MATRIX DEMO ///////////////////
        inDemo >> dataSize;

        UpperTriangularMatrix<double> my_upper;
        my_upper.setSize(dataSize);
        inDemo >> my_upper;

        cout << "Upper Triangular Matrix my_upper: " << endl;
        cout << my_upper << endl << endl;
        cout << "my_upper * my_upper: " << endl;
        cout << (my_upper * my_upper) << endl << endl;

        // LOWER TRIANGULAR MATRIX DEMO ///////////////////
        inDemo >> dataSize;

        LowerTriangularMatrix<double> my_lower;
        my_lower.setSize(dataSize);
        inDemo >> my_lower;

        cout << "Lower Triangular Matrix my_lower: " << endl;
        cout << my_lower;
        cout << "my_lower * my_lower: " << endl;
        cout << (my_lower * my_lower) << endl << endl;

        // SYMMETRIC DENSE MATRIX DEMO //////////////////////
        inDemo >> dataSize;

        SymmetricDenseMatrix<double> my_sym;
        my_sym.setSize(dataSize);
        inDemo >> my_sym;

        cout << "Symmetric Dense Matrix my_sym: " << endl;
        cout << my_sym;
        cout << "my_sym * my_sym: " << endl;
        cout << (my_sym * my_sym) << endl << endl;

        // EIGENVALUE OUTPUT REQUIREMENTS ///////////////////
        eigenvalue_calculator(in);
        eigenvalue_calculator(in);
        cout << "===" << endl;

      } // end of file check else
      
    in.close();
    } //end of arg check else
  } //end of try
  catch(RangeError e)
  {
    cerr << "RangeError caught bad subscript = " << e.badSubscript() << endl;
    cerr << "Subscript must be in the range [0, size - 1]." << endl << endl;
  }
  catch(SizeError e)
  {
    cerr << "SizeError caught bad size = " << e.badSize() << endl;
    cerr << "Size must be greater than zero to be valid." << endl << endl;
  }
  
  return 0;
} 

void eigenvalue_calculator(ifstream& in)
{
  int dataSize;
        
  in >> dataSize;
  
  SquareMatrix<double> A;
  SquareMatrix<double> Q;
  UpperTriangularMatrix<double> R;

  A.setSize(dataSize);
  Q.setSize(dataSize);
  R.setSize(dataSize);


  QRdecomp<double> my_QRdecomp;

  in >> A;

  int count = 1;

  double temp;
  do
  {
    temp = A[0][0];
    my_QRdecomp(A, Q, R);

    A = (R * Q);

    count ++;
    if (count == 5 || count == 10)
    {
      cout << "=== Iteration " << count << " ===" << endl;
      cout << A;
    }

  } while (abs(A[0][0] - temp) > STOPPING_THRESHOLD && count < STOPPING_CRITERIA);

  cout << "=== Iteration " << count << " (Final) ===" << endl;
  cout << A;
  cout << "=== Reason ===" << endl;
  if (count == STOPPING_CRITERIA)
  {
    cout << "The count reached the STOPPING_CRITERIA of " << STOPPING_CRITERIA 
         << "iterations." << endl;
  }
  else 
  {
    cout << "The difference between the A[0][0] value of the current and previous\n" 
         << "iteration was less than the STOPPING_THRESHOLD of " << STOPPING_THRESHOLD 
         << "." << endl;
  }

  cout << "=== Eigenvalues ===" << endl;
  for (int i = 0; i < A.getSize(); i++)
  {
    cout << A[i][i] << " ";
  }
  cout << endl;
}
