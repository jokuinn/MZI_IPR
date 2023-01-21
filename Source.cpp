#define _CRT_SECURE_NO_WARNINGS 1
#include <cassert>
#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include <cstdlib>
#include <ctime>


using namespace std;

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();
long Test();
void run_tests();
void run_rsa();

int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    run_rsa();
    //run_tests();
    return 0;
}

void run_rsa()
{
    srand(time(0));
    while (prime(p = rand() % 100) == 0) {}
    while (prime(q = rand() % 100) == 0 || p == q) {}
    cout << "\nENTER MESSAGE\n";
    cout << "\n";
    fflush(stdin);
    cin.getline(msg, 100);
    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];
    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    encrypt();
    decrypt();
}

void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}
long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}
void encrypt()
{
    long int pt, ct, key = e[0], k, len;
    char* result = nullptr;
    i = 0;
    len = strlen(msg);
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    cout << "\nTHE ENCRYPTED MESSAGE IS\n";
    for (i = 0; en[i] != -1; i++)
        printf("%c", en[i]);
    cout << "\n";

}
void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    cout << "\nTHE DECRYPTED MESSAGE IS\n";
    for (i = 0; m[i] != -1; i++)
        printf("%c", m[i]);
    cout << "\n";
}

char* Test(char msg[100])
{
    srand(time(0));
    while (prime(p = rand() % 100) == 0) {}
    while (prime(q = rand() % 100) == 0 || p == q) {}
    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];
    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    encrypt();
    decrypt();

    char result[100];
    for (i = 0; m[i] != '\0'; i++)
    {
        result[i] = char(m[i]);
    }
    return result;
}

void run_tests()
{
    char first_msg[100] = "It's a good Test";
    char second_msg[100] = "My name is Maks";
    char third_msg[100] = "I love Ruby";

    assert(Test(first_msg) == first_msg);
    assert(Test(second_msg) == second_msg);
    assert(Test(third_msg) == third_msg);
}


