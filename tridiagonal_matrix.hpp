// FileName:   tridiagonal_matrix.hpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function definition for the TridiagonalMatrix derived class

template <class T>
Vector<T> TridiagonalMatrix<T>::getRow(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  Vector<T> temp;
  temp.setSize(getSize());

  for (int j = 0; j < getSize(); j++)
  {
    if (j == i)
      temp[j] = m_maindiag[i];
    else if (j == (i + 1))
      temp[j] = m_upperdiag[i];
    else if (j == (i - 1))
      temp[j] = m_lowerdiag[i - 1];
    else
      temp[j] = 0;
  }

  return temp;
}

template <class T>
Vector<T> TridiagonalMatrix<T>::getCol(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  Vector<T> temp;
  temp.setSize(getSize());

  for (int j = 0; j < getSize(); j++)
  {
    if (j == i)
      temp[j] = m_maindiag[i];
    else if (j == (i + 1))
      temp[j] = m_lowerdiag[i];
    else if (j == (i - 1))
      temp[j] = m_upperdiag[i - 1];
    else
      temp[j] = 0;
  }

  return temp;
}

template <class T>
Vector<T> TridiagonalMatrix<T>::operator[](const int i) const
{
  return getRow(i);
}

template <class T>
void TridiagonalMatrix<T>::setSize(const int n)
{
  if (n < 0)
    throw SizeError(n);

  m_maindiag.setSize(n);
  m_upperdiag.setSize(n-1);
  m_lowerdiag.setSize(n-1);

  return;
}

template <class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::operator=(const TridiagonalMatrix<T>& rhs)
{
  m_maindiag = rhs.m_maindiag;
  m_upperdiag = rhs.m_upperdiag;
  m_lowerdiag = rhs.m_lowerdiag;
  return *this;
}

template <class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::operator=(const T& rhs)
{
  m_maindiag = rhs;
  m_upperdiag = rhs;
  m_lowerdiag = rhs;
  return *this;
}

template <class T>
TridiagonalMatrix<T> TridiagonalMatrix<T>::operator+(const TridiagonalMatrix<T>& rhs) const
{
  TridiagonalMatrix<T> temp;
  temp.m_maindiag = (m_maindiag + rhs.m_maindiag);
  temp.m_upperdiag = (m_upperdiag + rhs.m_upperdiag);
  temp.m_lowerdiag = (m_lowerdiag + rhs.m_lowerdiag);
  return temp;
}

template <class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::operator+=(const TridiagonalMatrix<T>& rhs)
{
  return ((*this) = ((*this) + rhs));
}

template <class T>
TridiagonalMatrix<T> TridiagonalMatrix<T>::operator-() const
{
  TridiagonalMatrix<T> temp;
  temp.m_maindiag = -m_maindiag;
  temp.m_upperdiag = -m_upperdiag;
  temp.m_lowerdiag = -m_lowerdiag;
  return temp;
}

template <class T>
TridiagonalMatrix<T> TridiagonalMatrix<T>::operator-(const TridiagonalMatrix<T>& rhs) const
{
  return ((*this) + (-rhs));
}

template <class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::operator-=(const TridiagonalMatrix<T>& rhs)
{
  return ((*this) = ((*this) - rhs));
}

template <class T>
SquareMatrix<T> TridiagonalMatrix<T>::operator*(const TridiagonalMatrix<T>& rhs) const
{
  SquareMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j < getSize(); j++)
    {
      if (j == (i - 2))
        temp[i][j] = m_lowerdiag[j+1] * rhs.m_lowerdiag[j];
      else if (j == (i - 1))
        temp[i][j] = m_lowerdiag[j] * rhs.m_maindiag[j] + 
                     m_maindiag[j+1] * rhs.m_lowerdiag[j];
      else if (j == i)
        temp[i][j] = ((j == 0)?((T)0):(m_lowerdiag[j-1] * rhs.m_upperdiag[j-1])) +
                     m_maindiag[j] * rhs.m_maindiag[j] +
                     ((j == (getSize()-1))?((T)0):(m_upperdiag[j] * rhs.m_lowerdiag[j]));
      else if (j == (i + 1))
        temp[i][j] = m_maindiag[j-1] * rhs.m_upperdiag[j-1] +
                     m_upperdiag[j-1] * rhs.m_maindiag[j];
      else if (j == (i + 2))
        temp[i][j] = m_upperdiag[j-2] * rhs.m_upperdiag[j-1];
      else
        temp[i][j] = 0;
    }
  }
  return temp;
}

template <class T>
TridiagonalMatrix<T> TridiagonalMatrix<T>::operator*(const T& rhs) const
{
  TridiagonalMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
    temp.m_maindiag[i] = m_maindiag[i] * rhs;

  for (int i = 0; i < (getSize() - 1); i++)
  {
    temp.m_upperdiag[i] = m_upperdiag[i] * rhs;
    temp.m_lowerdiag[i] = m_lowerdiag[i] * rhs;
  }

  return temp;
}

template <class T>
TridiagonalMatrix<T> operator*(const T& lhs, const TridiagonalMatrix<T>& rhs)
{
  return (rhs * lhs);
}

template <class T>
void TridiagonalMatrix<T>::print(ostream& out) const
{
  int lprecise; // amount of numbers to left of decimal
  int rprecise; // amount of zeroes to right of decimal before first non-zero
  T temp;

  out << fixed;

  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j < getSize(); j++)
    {

      if ((*this)[i][j] == 0)
      {
        out << setw(9);
        out << "0      "; // 0 followed by 6 spaces
      }
      else
      {
        lprecise = 1;
        rprecise = 0;
        temp = (*this)[i][j];

        while (temp >= 10 || temp <= -10)
        {
          lprecise++;
          temp = temp / 10;
        }

        while (temp < .1 && temp > -.1)
        {
          if ((*this)[i][j] == 0)
            temp = 1;
          rprecise ++;
          temp = temp * 10;
        }

        if (lprecise < 6)
        {
          if (rprecise >= 5)
          {
            out << setw(9);
            out << scientific;
            out << setprecision(1) << (*this)[i][j];
            out << fixed;
          }
          else if (((*this)[i][j] - static_cast<int>((*this)[i][j])) == 0)
          {
            out << setw(2 + lprecise);
            out << static_cast<int>((*this)[i][j]);
            out << setw(7 - lprecise);
            out << " ";
          }
          else
          {
            out << setw(9);
            out << setprecision(6 - lprecise) << (*this)[i][j];
          }
        }
        else if (lprecise == 6)
        {
          out << setw(8);
          out << static_cast<int>((*this)[i][j]) << " ";
        }
        else if (lprecise == 7)
        {
          out << setw(9);
          out << static_cast<int>((*this)[i][j]);
        }
        else
        {
          out << setw(9);
          out << scientific;
          out << setprecision(1) << (*this)[i][j];
          out << fixed;
        }
      } // end of else checking for (*this)[i][j] == 0;
    } // end of j for loop
    out << endl;
  } // end of i for loop
  out.unsetf(ios_base::floatfield); // clears fixed output setting

  return;
}

template <class T>
void TridiagonalMatrix<T>::input(ifstream& in)
{
  T junk;

  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j < getSize(); j++)
    {
      if (j == (i - 1))
        in >> m_lowerdiag[j];
      else if (j == i)
        in >> m_maindiag[j];
      else if (j == (i + 1))
        in >> m_upperdiag[j-1];
      else
        in >> junk;
    }
  }
  return;
}