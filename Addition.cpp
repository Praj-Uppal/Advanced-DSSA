#include <stdio.h>

#include <iostream>

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

int main(void) { cout << addition(1000000, 11200, 6) << endl; }