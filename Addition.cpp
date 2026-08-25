#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> addition(vector<int> a, vector<int> b, int base)
{
  // Define carry var and result vector
  int carry = 0;
  vector<int> result;

  // Iterates while both vectors have integers, or carry exists
  while (!a.empty() || !b.empty() || carry)
  {
    int digitA, digitB, digitRes;

    // Assume both digits 0 at first
    digitA = 0;
    digitB = 0;

    // Assign digit A if not empty
    if (!a.empty())
    {
      digitA = a.back();
      a.pop_back();
    }
    // Assign digit B if not empty
    if (!b.empty())
    {
      digitB = b.back();
      b.pop_back();
    }
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
  }

  // Reverse the vector to present in MSD to LSD form.
  reverse(result.begin(), result.end());
  return result;
}

vector<int> subtraction(vector<int> a, vector<int> b, int base)
{
  // Define borrow var and result vector
  int borrow = 0;
  vector<int> result;

  // Iterates while a not empty
  while (!a.empty())
  {
    int digitA, digitB, digitRes;

    // Take LSD of both vectors
    digitA = a.back();
    digitB = 0;
    if (!b.empty())
    {
      digitB = b.back();
      b.pop_back();
    }

    // Sum
    digitRes = digitA - digitB - borrow;
    borrow = 0;
    // Account for borrow
    if (digitRes < 0)
    {
      digitRes += base;
      borrow = 1;
    }
    // Add onto vector
    result.push_back(digitRes);
    // Pop the back to get the next LSD
    a.pop_back();
  }

  // Remove leading zeros
  while (result.size() > 1 && result.back() == 0)
  {
    result.pop_back();
  }

  // Reverse the vector to present in MSD to LSD form.
  reverse(result.begin(), result.end());
  return result;
}

vector<int> Karatsuba(vector<int> a, vector<int> b, int base)
{
  vector<int> result;
  vector<int> prod1, prod2, prod3;
  int maxLen = max(a.size(), b.size());

  int mid = max(a.size(), b.size()) / 2;

  // Base Case if both 1 digit long
  if (a.size() == 1 && b.size() == 1)
  {
    int res = a.front() * b.front();
    if (res == 0)
    {
      return {0};
    }

    while (res > 0)
    {
      result.push_back(res % base);
      res /= base;
    }

    reverse(result.begin(), result.end());
    return result;
  }

  // Make both vectors the same size by adding leading zeros
  if (a.size() < maxLen)
  {
    a.insert(a.begin(), maxLen - a.size(), 0);
  }

  if (b.size() < maxLen)
  {
    b.insert(b.begin(), maxLen - b.size(), 0);
  }

  vector<int> a0(a.begin(), a.begin() + mid);
  vector<int> a1(a.begin() + mid + 1, a.end());
  vector<int> b0(b.begin(), b.begin() + mid);
  vector<int> b1(b.begin() + mid + 1, b.end());
  prod1 = Karatsuba(a0, b0, base);
  prod3 = Karatsuba(a1, b1, base);

  vector<int> sumA = addition(a0, a1, base);
  vector<int> sumB = addition(b0, b1, base);

  prod2 = Karatsuba(sumA, sumB, base);

  prod2 = subtraction(prod3, prod1, base);
  prod2 = subtraction(prod3, prod2, base);

  prod1.insert(prod1.begin(), 2 * mid, 0);
  prod2.insert(prod2.begin(), mid, 0);

  result = addition(prod1, prod2, base);
  result = addition(result, prod3, base);
  return result;
}

int main(void) {}