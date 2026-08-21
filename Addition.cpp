#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int addition(int a, int b, int base)
{
  int result = 0, carry = 0, pos = 1;

  while (a > 0 || b > 0)
  {
    int digita, digitb, digitres;
    digita = a % 10;
    digitb = b % 10;
    digitres = digita + digitb + carry;
    carry = 0;
    if (digitres >= base)
    {
      carry = 1;
      digitres = digitres % base;
    }

    int posCopy = pos;
    while (posCopy > 1)
    {
      digitres *= 10;
      posCopy--;
    }
    result += digitres;
    a /= 10;
    b /= 10;
    pos++;
  }

  if (carry == 1)
  {
    while (pos > 1)
    {
      carry *= 10;
      pos--;
    }
    result += carry;
  }

  return result;
}

vector<int> additionVec(vector<int> a, vector<int> b, int base)
{
  // Define carry var and result vector
  int carry = 0;
  vector<int> result;

  // Iterates while both vectors have integers
  while (~a.empty() && ~b.empty())
  {
    int digitA, digitB, digitRes;

    // Take LSD of both vectors
    digitA = a.back();
    digitB = b.back();
    // Sum
    digitRes = digitA + digitB + carry;
    carry = 0;
    // Account for carry
    if (digitRes >= base)
    {
      digitRes %= base;
      carry = 1;
    }
    // Add onto vector
    result.push_back(digitRes);
    // Pop the back to get the next LSD
    a.pop_back();
    b.pop_back();
  }

  // If a was not empty, b must be empty.
  // fill result with remaining a digits, making note of carry
  while (~a.empty())
  {
    int digitA = a.back();
    int digitRes = digitA + carry;
    if (digitRes >= base)
    {
      digitRes %= base;
      carry = 1;
    }
    result.push_back(digitRes);
    a.pop_back();
  }
  // If a was empty, fill result with remaining B digits, making note of
  // carry
  while (~b.empty())
  {
    int digitB = b.back();
    int digitRes = digitB + carry;
    if (digitRes >= base)
    {
      digitRes %= base;
      carry = 1;
    }

    result.push_back(digitRes);
    b.pop_back();
  }

  // Account for carry at the end
  if (carry == 1)
  {
    result.push_back(1);
  }

  // Reverse the vector to present in MSD to LSD form.
  reverse(result.begin(), result.end());
  return result;
}

vector<int> Karatsuba(vector<int> a, vector<int> b, int base)
{
  vector<int> result;
  vector<int> prod1, prod2, prod3;
  int mid = max(a.size(), b.size()) / 2;

  if (a.size() <= 1 && b.size() <= 1)
  {
    int res = a.front() * b.front();
    result.push_back(res / base);
    result.push_back(res % base);
    return result;
  }

  if (a.size() <= mid)
  {
    vector<int> b0(b.begin(), b.begin() + mid);
    vector<int> b1(b.begin() + mid + 1, b.end());
    prod1 = Karatsuba(b0, a, base);
    prod2 = Karatsuba(b1, a, base);
    prod1.insert(prod1.end(), mid, 0);
    result = additionVec(prod1, prod2, base);
    return result;
  }
  else if (b.size() <= mid)
  {
    vector<int> a0(a.begin(), a.begin() + mid);
    vector<int> a1(a.begin() + mid + 1, a.end());
    prod1 = Karatsuba(a0, b, base);
    prod2 = Karatsuba(a1, b, base);
    prod1.insert(prod1.end(), mid, 0);
    result = additionVec(prod1, prod2, base);
    return result;
  }
  else
  {
    vector<int> a0(a.begin(), a.begin() + mid);
    vector<int> a1(a.begin() + mid + 1, a.end());
    vector<int> b0(b.begin(), b.begin() + mid);
    vector<int> b1(b.begin() + mid + 1, b.end());
    prod1 = Karatsuba(a0, b0, base);
    prod2 = Karatsuba(a1, b1, base);
    prod3 = Karatsuba(additionVec(a1, a0, base), additionVec(b1, b0, base), base);
  }
}

int main(void) {}