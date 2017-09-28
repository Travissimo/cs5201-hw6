// FileName:   symmetric_dense_matrix.hpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Function definition for the SymmetricDenseMatrix derived class

template <class T>
Vector<T> SymmetricDenseMatrix<T>::getRow(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  Vector<T> temp;
  temp.setSize(getSize());

  for (int j = 0; j < getSize(); j++)
  {
    if (j <= i)
      temp[j] = m_lowertri[i][j];
    else
      temp[j] = m_lowertri[j][i];
  }

  return temp;
}

template <class T>
Vector<T> SymmetricDenseMatrix<T>::getCol(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  Vector<T> temp;
  temp.setSize(getSize());

  for (int j = 0; j < getSize(); j++)
  {
    if (j >= i)
      temp[j] = m_lowertri[j][i];
    else
      temp[j] = m_lowertri[i][j];
  }

  return temp;
}

template <class T>
Vector<T> SymmetricDenseMatrix<T>::operator[](const int i) const
{
  return getRow(i);
}

template <class T>
void SymmetricDenseMatrix<T>::setSize(const int n)
{
  if (n < 0)
    throw SizeError(n);

  m_lowertri.setSize(n);
  for (int i = 0; i < getSize(); i++)
    m_lowertri[i].setSize(i+1);

  return;
}

template <class T>
SymmetricDenseMatrix<T>& SymmetricDenseMatrix<T>::operator=(const SymmetricDenseMatrix<T>& rhs)
{
  m_lowertri = rhs.m_lowertri;
  return *this;
}

template <class T>
SymmetricDenseMatrix<T>& SymmetricDenseMatrix<T>::operator=(const T& rhs)
{
  m_lowertri = rhs;
  return *this;
}

template <class T>
SymmetricDenseMatrix<T> SymmetricDenseMatrix<T>::operator+(const SymmetricDenseMatrix<T>& rhs) const
{
  SymmetricDenseMatrix<T> temp;
  temp.m_lowertri = (m_lowertri + rhs.m_lowertri);
  return temp;
}

template <class T>
SymmetricDenseMatrix<T>& SymmetricDenseMatrix<T>::operator+=(const SymmetricDenseMatrix<T>& rhs)
{
  return ((*this) = ((*this) + rhs));
}

template <class T>
SymmetricDenseMatrix<T> SymmetricDenseMatrix<T>::operator-() const
{
  SymmetricDenseMatrix<T> temp;
  temp.m_lowertri = -m_lowertri;
  return temp;
}

template <class T>
SymmetricDenseMatrix<T> SymmetricDenseMatrix<T>::operator-(const SymmetricDenseMatrix<T>& rhs) const
{
  return ((*this) + (-rhs));
}

template <class T>
SymmetricDenseMatrix<T>& SymmetricDenseMatrix<T>::operator-=(const SymmetricDenseMatrix<T>& rhs)
{
  return ((*this) = ((*this) - rhs));
}

template <class T>
SymmetricDenseMatrix<T> SymmetricDenseMatrix<T>::operator*(const SymmetricDenseMatrix<T>& rhs) const
{
  SymmetricDenseMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j <= i; j++)
    {
      temp.m_lowertri[i][j] = 0;
      for (int k = 0; k < getSize(); k++)
      {
        if (k < j)
        {
          temp.m_lowertri[i][j] += m_lowertri[i][k] * rhs.m_lowertri[j][k];
        }
        else if (k <= i)
        {
          temp.m_lowertri[i][j] += m_lowertri[i][k] * rhs.m_lowertri[k][j];
        }
        else
        {
          temp.m_lowertri[i][j] += m_lowertri[k][i] * rhs.m_lowertri[k][j];
        }
      }
    }
  }
  return temp;
}

template <class T>
SymmetricDenseMatrix<T> SymmetricDenseMatrix<T>::operator*(const T& rhs) const
{
  SymmetricDenseMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
  {
    temp.m_lowertri[i] = (m_lowertri[i] * rhs);
  }

  return temp;
}

template <class T>
SymmetricDenseMatrix<T> operator*(const T& lhs, const SymmetricDenseMatrix<T>& rhs)
{
  return (rhs * lhs);
}

template <class T>
void SymmetricDenseMatrix<T>::print(ostream& out) const
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
void SymmetricDenseMatrix<T>::input(ifstream& in)
{
  T junk;

  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j < getSize(); j++)
    {
      if (j <= i)
        in >> m_lowertri[i][j];
      else
        in >> junk;
    }
  }

  return;
}