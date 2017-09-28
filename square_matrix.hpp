// FileName:   square_matrix.hpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/22/2016

// Description: Definitions for functions declared in square_matrix.h

template <class T>
Vector<T> SquareMatrix<T>::getRow(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  return (*this)[i];
}

template <class T>
Vector<T> SquareMatrix<T>::getCol(const int i) const
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  Vector<T> temp;
  temp.setSize(getSize());

  for (int j = 0; j < getSize(); j++)
  {
    temp[j] = (*this)[j][i];
  }

  return temp;
}

template <class T>
Vector<T>& SquareMatrix<T>::operator[](const int i)
{
  
  if (i < 0 || i >= getSize())
    throw RangeError(i);
    
  return m_matrix[i];
}

template <class T>
Vector<T> SquareMatrix<T>::operator[](const int i) const
{
  
  if (i < 0 || i >= getSize())
    throw RangeError(i);
    
  return m_matrix[i];
}

template <class T>
void SquareMatrix<T>::setSize(const int n)
{
  if (n < 0)
    throw SizeError(n);

  m_matrix.setSize(n);
  for (int i = 0; i < getSize(); i++)
    m_matrix[i].setSize(n);

  return;
}

template <class T>
void SquareMatrix<T>::setCol(const int i, const Vector<T>& source)
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  for (int j = 0; j < getSize(); j++)
    m_matrix[j][i] = source[j];

  return;
}

template <class T>
void SquareMatrix<T>::setRow(const int i, const Vector<T>& source)
{
  if (i < 0 || i >= getSize())
    throw RangeError(i);

  m_matrix[i] = source;

  return;
}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T>& rhs)
{
  m_matrix = rhs.m_matrix;
  return *this;
}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const T& rhs)
{
  m_matrix = rhs;
  return *this;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T>& rhs) const
{
  SquareMatrix<T> temp;
  temp.m_matrix = (m_matrix + rhs.m_matrix);
  return temp;
}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator+=(const SquareMatrix<T>& rhs)
{
  m_matrix += rhs.m_matrix;
  return *this;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator-() const
{
  SquareMatrix<T> temp;
  temp.m_matrix = -m_matrix;
  return temp;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator-(const SquareMatrix<T>& rhs) const
{
  SquareMatrix<T> temp;
  temp.m_matrix = m_matrix - rhs.m_matrix;
  return temp;
}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator-=(const SquareMatrix<T>& rhs)
{
  m_matrix -= rhs.m_matrix;
  return *this;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator*(const SquareMatrix<T>& rhs) const
{
  SquareMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
  {
    for (int j = 0; j < getSize(); j++)
      temp[i][j] = (getRow(i) * rhs.getCol(j));
  }

  return temp;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator*(const T& rhs) const
{
  SquareMatrix<T> temp;
  temp.setSize(getSize());
  for (int i = 0; i < getSize(); i++)
    temp[i] = (*this)[i] * rhs;

  return temp;
}

template <class T>
SquareMatrix<T> operator*(const T& lhs, const SquareMatrix<T>& rhs)
{
  return (rhs * lhs);
}

template <class T>                              
void SquareMatrix<T>::print(ostream& out) const
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
      } // end of else checking for (*this)[i][j] == 0
    } // end of j for loop
    out << endl;
  } // end of i for loop

  out.unsetf(ios_base::floatfield); // clears fixed output setting

  return;
}

template <class T>
void SquareMatrix<T>::input(ifstream& in)
{
  in >> m_matrix;
  return;
}


template <class T>
SquareMatrix<T> SquareMatrix<T>::transpose() const
{
  SquareMatrix<T> temp;
  temp = *this;

  if (getSize() > 1)
  {
    for (int i = 0; i < getSize(); i++)
    {
      for (int j = i + 1; j < getSize(); j++)
      {
        swap(temp[i][j], temp[j][i]);
      }
    }
  }
  return temp;
}

template <class T>
void SquareMatrix<T>::swapRows(const int n, const int m)
{
  if (n < 0 || n >= getSize())
    throw RangeError(n);
  if (m < 0 || m >= getSize())
    throw RangeError(m);

  for (int i = 0; i < getSize(); i++)
  {
    swap((*this)[n][i], (*this)[m][i]);
  }

  return;
}