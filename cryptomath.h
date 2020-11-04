#ifndef __CRYPTOMATH__
#define __CRYPTOMATH__

#include <iostream>
#include <cmath>

// GCD
template <typename T>
T gcd(T a, T b)
{
  static_assert(std::is_integral<T>::value, "Integral required.");
  if (b == 0)
    return a;
  if (b > a)
    return gcd(b, a);
  T c = a % b;
  while (c != 0)
  {
    a = b;
    b = c;
    c = a % b;
  }
  return b;
}

// Inverse Modulo: a.x = 1 (mod m)
template <typename T>
T mod_inverse(T a, T m)
{
  static_assert(std::is_integral<T>::value, "Integral required.");
  if (gcd<T>(a, m) != 1)
    return 0;
  if (a == 0)
    return 0;
  // a_i => a[i]
  T r_i_1, r_i_2;
  T a_i_1, a_i_2;
  T q;
  a_i_2 = 0, a_i_1 = 1;
  r_i_2 = m, r_i_1 = a;

  while (r_i_1 != 1)
  {
    q = floor(r_i_2 / r_i_1);
    T r_i = r_i_2 % r_i_1;
    T a_i = (a_i_2 - (q * a_i_1) % m) % m;
    r_i_2 = r_i_1;
    r_i_1 = r_i;
    a_i_2 = a_i_1;
    a_i_1 = a_i;
  }
  // add m for a non-negative value
  return (a_i_1 + m) % m;
}

//For now only square and multiply.
// a^b mod m
template <typename T>
T power(T base, T exp, T m)
{
  static_assert(std::is_integral<T>::value, "Integral required.");
  T ans = 1;
  // Also add a totient function later. exp = exp%(tot(m))
  base = base % m;
  while (exp != 0)
  {
    if ((exp & 1) == 1)
    {
      ans = (ans * base) % m;
    }
    exp >>= 1;
    base = (base * base) % m;
  }
  return ans;
}

template <typename T>
T power(T base, T exp)
{
  static_assert(std::is_integral<T>::value, "Integral required.");
  T ans = 1;
  // Also add a totient function later. exp = exp%(tot(m))
  while (exp != 0)
  {
    if ((exp & 1) == 1)
    {
      ans = (ans * base);
    }
    exp >>= 1;
    base = (base * base);
  }
  return ans;
}

struct railfence_cipher {

  private:
    uint key;
  
  public:
    
	railfence_cipher(size_t key) {
		this->key = key;
	}

  std::string * encrypt(std::string);
  std::string * decrypt(std::string *);

};

#endif
