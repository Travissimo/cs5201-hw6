// FileName:   upper_triangular_matrix.hpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function definition for the UpperTriangularMatrix derived class 

template <class T>
Vector<T> UpperTriangularMatrix<T>::getRow(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  Vector<T> temp;
  temp.setSize(getSize());

  for (int j = 0; j < getSize(); j++)
  {
    if (j >= i)
      temp[j] = m_uppertri[i][j-i];
    else
      temp[j] = 0;
  }

  return temp;
}

template <class T>
Vector<T> UpperTriangularMatrix<T>::getCol(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  Vector<T> temp;
  temp.setSize(getSize());

  for (int j = 0; j < getSize(); j++)
  {
    if (j <= i)
      temp[j] = m_uppertri[j][i-j];
    else
      temp[j] = 0;
  }

  return temp;
}

template <class T>
Vector<T> UpperTriangularMatrix<T>::operator[](const int i) const
{
  return getRow(i);
}

template <class T>
T& UpperTriangularMatrix<T>::ref(const int i, const int j)
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);
  if (j < i || j >= getSize())
    throw RangeError(j);

  return (m_uppertri[i][j-i]);
}

template <class T>
void UpperTriangularMatrix<T>::setSize(const int n)
{
  if (n < 0)
    throw SizeError(n);

  m_uppertri.setSize(n);
  for (int i = 0; i < getSize(); i++)
    m_uppertri[i].setSize(getSize() - i);

  return;
}

template <class T>
UpperTriangularMatrix<T>& UpperTriangularMatrix<T>::operator=(const UpperTriangularMatrix<T>& rhs)
{
  m_uppertri = rhs.m_uppertri;
  return *this;
}

template <class T>
UpperTriangularMatrix<T>& UpperTriangularMatrix<T>::operator=(const T& rhs)
{
  m_uppertri = rhs;
  return *this;
}

template <class T>
UpperTriangularMatrix<T> UpperTriangularMatrix<T>::operator+(const UpperTriangularMatrix<T>& rhs) const
{
  UpperTriangularMatrix<T> temp;
  temp.m_uppertri = (m_uppertri + rhs.m_uppertri);
  return temp;
}

template <class T>
UpperTriangularMatrix<T>& UpperTriangularMatrix<T>::operator+=(const UpperTriangularMatrix<T>& rhs)
{
  return ((*this) = ((*this) + rhs));
}

template <class T>
UpperTriangularMatrix<T> UpperTriangularMatrix<T>::operator-() const
{
  UpperTriangularMatrix<T> temp;
  temp.m_uppertri = -m_uppertri;
  return temp;
}

template <class T>
UpperTriangularMatrix<T> UpperTriangularMatrix<T>::operator-(const UpperTriangularMatrix<T>& rhs) const
{
  return ((*this) + (-rhs));
}

template <class T>
UpperTriangularMatrix<T>& UpperTriangularMatrix<T>::operator-=(const UpperTriangularMatrix<T>& rhs)
{
  return ((*this) = ((*this) - rhs));
}

template <class T>
UpperTriangularMatrix<T> UpperTriangularMatrix<T>::operator*(const UpperTriangularMatrix<T>& rhs) const
{
  UpperTriangularMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
  {
    for (int j = i; j < getSize(); j++)
    {
      temp.m_uppertri[i][j-i] = 0;
      for (int k = i; k <= j; k++)
      {
        temp.m_uppertri[i][j-i] += (*this)[i][k] * rhs[k][j];
      }
    }
  }
  return temp;
}

template <class T>
SquareMatrix<T> UpperTriangularMatrix<T>::operator*(const SquareMatrix<T>& rhs) const
{
  SquareMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j < getSize(); j++)
    {
      temp[i][j] = 0;
      for (int k = 0; k < (getSize() - i); k++)
      {
        temp[i][j] += m_uppertri[i][k] * rhs[k+i][j]; 
      }
    }
  }
  return temp;
}

template <class T>
UpperTriangularMatrix<T> UpperTriangularMatrix<T>::operator*(const T& rhs) const
{
  UpperTriangularMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
  {
    temp.m_uppertri[i] = (m_uppertri[i] * rhs);
  }
  
  return temp;
}

template <class T>
UpperTriangularMatrix<T> operator*(const T& lhs, const UpperTriangularMatrix<T>& rhs)
{
  return (rhs * lhs);
}

template <class T>
void UpperTriangularMatrix<T>::print(ostream& out) const
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
void UpperTriangularMatrix<T>::input(ifstream& in)
{
  T junk;

  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j < getSize(); j++)
    {
      if (j >= i)
        in >> m_uppertri[i][j-i];
      else
        in >> junk;
    }
  }

  return;
}