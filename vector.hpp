// FileName:   vector.hpp
// Programmer: Travis Connelly
// Class:      CS 5201 - Price
// Assignment: 6 - An Abstract Matrix Class w/ Derivatives
// Due:        4/8/2016

// Description: Definitions for functions declared in vector.h

template <class T>
Vector<T>::Vector()
{
  m_size = 0;
  ptr_to_data = new T[0];
}

template <class T>
Vector<T>::Vector(const int n)
{
  if (n < 0)
    throw SizeError(n);
  m_size = n;
  ptr_to_data = new T[n];
}

template <class T>
Vector<T>::Vector(Vector<T>&& source)
{
  m_size = source.m_size;
  ptr_to_data = source.ptr_to_data;
  source.ptr_to_data = nullptr;
  source.m_size = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T>& source)
{
  m_size = source.m_size;
  ptr_to_data = new T[m_size];
  vectorCopy (source); // copy source's elements
}

template <class T>
void Vector<T>::vectorCopy(const Vector& source)
{
  for (int i = 0; i < m_size; i++)
    ptr_to_data[i] = source.ptr_to_data[i];

  return;
}

template <class T>
Vector<T>::~Vector()
{
  delete[] ptr_to_data; 
}

template <class T>
void Vector<T>::setSize(const int n)
{
  if (n != m_size)
  {
    if (n < 0)
      throw SizeError(n);
    delete[] ptr_to_data;
    m_size = n;
    ptr_to_data = new T[n];
  }

  return;
}

template <class T>
T Vector<T>::operator[](const int i)const
{
  if (i < 0 || i >= m_size)
    throw RangeError(i);
  return ptr_to_data[i];
}

template <class T>
T& Vector<T>::operator[](const int i)
{
  if (i < 0 || i >= m_size)
    throw RangeError(i);
  return ptr_to_data[i];
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs)
{
  m_size = rhs.m_size;
  ptr_to_data = rhs.ptr_to_data;
  rhs.ptr_to_data = nullptr;
  rhs.m_size = 0;
  return (*this);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
  if (ptr_to_data != rhs.ptr_to_data)
  {
    setSize(rhs.m_size);
    vectorCopy(rhs);
  }
  return (*this);
}

template <class T>
Vector<T>& Vector<T>::operator=(const T& rhs)
{
  for (int i = 0; i < m_size; i++)
  {
    ptr_to_data[i] = rhs;
  }
  return (*this);
}

template <class T>
bool Vector<T>::operator==(const int& rhs) const
{
  for (int i = 0; i < m_size; i++)
  {
    if (!(ptr_to_data[i] == rhs))
      return false;
  }

  return true;
}

template <class T>
bool Vector<T>::operator!=(const int& rhs) const
{
  if ((*this) == rhs)
    return false;

  return true;
}

template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& rhs) const
{
  Vector<T> sum(m_size);
  for (int i = 0; i < m_size; i++)
  {
    sum.ptr_to_data[i] = ptr_to_data[i] + rhs.ptr_to_data[i];
  }
  return sum;
}

template <class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs) 
{
  return ((*this) = ((*this) + rhs));
}

template <class T>
Vector<T> Vector<T>::operator-() const
{
  Vector<T> negate;
  negate = (*this);
  for (int i = 0; i < m_size; i++)
  {
    if (ptr_to_data[i] != 0)
      negate.ptr_to_data[i] = -ptr_to_data[i];
  }
  return negate;
}

template <class T>
Vector<T> Vector<T>::operator-(const Vector<T>& rhs) const
{
  return ((*this) + (-rhs));
}

template <class T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs)
{
  return ((*this) = ((*this) - rhs));
}

template <class T>
T Vector<T>::operator*(const Vector<T>& rhs) const
{
  T dotProd = 0;
  for (int i = 0; i < m_size; i++)
  {
    dotProd += ptr_to_data[i] * rhs.ptr_to_data[i];
  }

  return dotProd;
}

template <class T>
Vector<T> Vector<T>::operator*(const T& rhs) const
{
  Vector<T> scalProd(m_size);
  for (int i = 0; i < m_size; i++)
  {
    scalProd.ptr_to_data[i] = ptr_to_data[i] * rhs; 
  }

  return scalProd;
}

template <class T>
Vector<T> operator*(const T& lhs, const Vector<T>& rhs)
{
  return (rhs * lhs);
}

template <class T>
ostream& operator<<(ostream& out, const Vector<T>& rhs)
{
  out << "<";
  for (int i = 0 ; i < (rhs.m_size - 1); i++)
  {
    out << rhs.ptr_to_data[i] << ", ";
  }
  out << rhs.ptr_to_data[rhs.m_size - 1] << ">";

  return out;
}

template <class T>
ifstream& operator>>(ifstream& in, const Vector<T>& rhs)
{
  for (int i = 0; i < rhs.m_size; i++)
    in >> rhs.ptr_to_data[i];

  return in;
}

template <class T>
T Vector<T>::twoNorm() const
{
  T norm = 0;

  for (int i  = 0; i < m_size; i++)
    norm += (ptr_to_data[i] * ptr_to_data[i]);

  return (sqrt(norm));
}