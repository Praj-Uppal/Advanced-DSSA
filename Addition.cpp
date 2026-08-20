#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int addition(int a, int b, int base) {
  int result = 0, carry = 0, pos = 1;

  while (a > 0 || b > 0) {
    int digita, digitb, digitres;
    digita = a % 10;
    digitb = b % 10;
    digitres = digita + digitb + carry;
    carry = 0;
    if (digitres >= base) {
      carry = 1;
      digitres = digitres % base;
    }

    int posCopy = pos;
    while (posCopy > 1) {
      digitres *= 10;
      posCopy--;
    }
    result += digitres;
    a /= 10;
    b /= 10;
    pos++;
  }

  if (carry == 1) {
    while (pos > 1) {
      carry *= 10;
      pos--;
    }
    result += carry;
  }

  return result;
}

vector<int> additionVec(vector<int> a, vector<int> b, int base) {
  // Define carry var and result vector
  int carry = 0;
  vector<int> result;

  // Iterates while both vectors have integers
  while (~a.empty() && ~b.empty()) {
    int digitA, digitB, digitRes;

    // Take LSD of both vectors
    digitA = a.back();
    digitB = b.back();
    // Sum
    digitRes = digitA + digitB + carry;
    carry = 0;
    // Account for carry
    if (digitRes >= base) {
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
  while (~a.empty()) {
    int digitA = a.back();
    int digitRes = digitA + carry;
    if (digitRes >= base) {
      digitRes %= base;
      carry = 1;
    }
    result.push_back(digitRes);
    a.pop_back();
  }
  // If a was empty, fill result with remaining B digits, making note of
  // carry
  while (~b.empty()) {
    int digitB = b.back();
    int digitRes = digitB + carry;
    if (digitRes >= base) {
      digitRes %= base;
      carry = 1;
    }

    result.push_back(digitRes);
    b.pop_back();
  }

  // Account for carry at the end
  if (carry == 1) {
    result.push_back(1);
  }

  // Reverse the vector to present in MSD to LSD form.
  reverse(result.begin(), result.end());
  return result;
}

vector<int> Karatsuba(vector<int> a, vector<int> b, int base) {
  vector<int> result;
  if (a.size() <= 1 && b.size() <= 1) {
    result.push_back(a.front() * b.front());
    return result;
  }

  if (a.size() <= 1) {
  }
}

int main(void) { cout < < < < endl; }