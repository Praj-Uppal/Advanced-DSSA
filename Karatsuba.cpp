#include <iostream>

using namespace std;
int power(int n, int pow)
{
    if (pow == 0)
    {
        return 1;
    }
    return n * power(n, pow - 1);
}

// int recursiveMultS(int a, int b)
// {
//     if (a / 10 == 0 && b / 10 == 0)
//     {
//         return a * b;
//     }

//     int diga = 0, digb = 0;
//     int aCopy = a, bCopy = b;
//     while (aCopy > 0)
//     {
//         diga++;
//         aCopy /= 10;
//     }

//     while (bCopy > 0)
//     {
//         digb++;
//         bCopy /= 10;
//     }

//     int midDa = diga / 2;
//     int midDb = digb / 2;
//     int modA = power(10, midDa);
//     int modB = power(10, midDb);

//     int a1 = a / modA;
//     int a0 = a % modA;

//     int b1 = b / modB;
//     int b0 = b % modB;

//     int result = modA * modB * recursiveMult(a1, b1) + modA * recursiveMult(a1, b0) + modB * recursiveMult(b1, a0) + recursiveMult(a0, b0);
//     return result;
// }

int recursiveMult(int a, int b)
{
    if (a / 10 == 0 && b / 10 == 0)
    {
        return a * b;
    }
    int max = a;
    if (a < b)
    {
        max = b;
    }

    int digits = 0;
    while (max > 0)
    {
        digits++;
        max /= 10;
    }

    int mid = digits / 2;
    int mod = power(10, mid);

    int a1 = a / mod;
    int a0 = a % mod;

    int b1 = b / mod;
    int b0 = b % mod;

    int result = mod * mod * recursiveMult(a1, b1) + mod * recursiveMult(a1, b0) + mod * recursiveMult(b1, a0) + recursiveMult(a0, b0);
    return result;
}

int Karatsuba(int a, int b)
{

    if (a / 100 == 0 && b / 10 == 0)
    {
        return a * b;
    }
}

int main(void)
{

    cout << recursiveMult(1000000, 1000000) << endl;
}
