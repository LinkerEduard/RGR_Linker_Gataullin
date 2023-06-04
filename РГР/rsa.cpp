#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <wchar.h>
using namespace std;
bool checkIfNumericRSA(string str)
{
    if (str.length() < 19)
        return !str.empty() && str.find_first_not_of(" 0123456789") == std::string::npos;
    else
        return false;
}
long long calculate_gcd(long long p, long long q)
{
    if (q == 0)
        return p;
    else
        return calculate_gcd(q, p % q);
}

long long calculate_e(long long phi)
{
    long long e = 2;
    while (e < phi && calculate_gcd(e, phi) != 1)
    {
        e++;
    }
    return e;
}

long long calculate_d(long long e, long long phi)
{
    long long d = 1;
    while ((d * e) % phi != 1)
    {
        d++;
    }
    return d;
}

bool is_prime(long long num)
{
    if (num == 1)
        return false;

    for (long long i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

bool can_encrypt1(long long p, long long q)
{
    if ((p-1) * (q-1) >= 255)
        return true;
    else
        return false;
}

bool is_different(long long p, long long q)
{
    if (p != q)
        return true;
    else
        return false;
}

bool can_encrypt2(long long p, long long q)
{
    if (p*q <= 3025550009)
        return true;
    else
        return false;
}

void get_primes(long long& p, long long& q)
{
    string primes;
    cout << "Enter two different prime numbers separated by space: ";
    getline(cin, primes);
    stringstream ss(primes);
    ss >> p >> q;

    while (!is_prime(p) || !is_prime(q) || !can_encrypt1(p, q) || !is_different(p, q) || !can_encrypt2(p, q) || p <= 0 || q <= 0)
    {
        if (p <= 0 || q <= 0) {
            cout << "Invalid input. Please enter two different prime numbers separated by space: ";
            getline(cin, primes);
            stringstream ss(primes);
            ss >> p >> q;
        }
        if (!is_prime(p) || !is_prime(q)) {
            cout << "Invalid input. Please enter two different prime numbers separated by space: ";
            getline(cin, primes);
            stringstream ss(primes);
            ss >> p >> q;
        }
        if (!is_different(p, q)) {
            cout << "Invalid input. Please enter two different prime numbers separated by space: ";
            getline(cin, primes);
            stringstream ss(primes);
            ss >> p >> q;
        }
        if (!can_encrypt1(p, q)) {
            cout << "Invalid input. Please enter two prime larger numbers separated by space ((p-1)*(q-1)>254): ";
            getline(cin, primes);
            stringstream ss(primes);
            ss >> p >> q;
        }
        if (!can_encrypt2(p, q)) {
            cout << "Invalid input. Please enter two smaller prime numbers separated by space (p*q<3025550010): ";
            getline(cin, primes);
            stringstream ss(primes);
            ss >> p >> q;
        }
    }
}

long long fast_pow(long long a, long long b, long long n)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res * a) % n;
        }
        a = (a * a) % n;
        b >>= 1;
    }
    return res;
}

void rsa_encrypt(std::string inputFileName, std::string outputFileName)
{
    wifstream inputFile(inputFileName);
    wofstream outputFile(outputFileName);
    wstring line;
    long long p, q;
    get_primes(p, q);
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = calculate_e(phi);
    long long d = calculate_d(e, phi);
    cout << "Public key: " << e << " ; " << n << endl;
    cout << "Private key: " << d << " ; " << n << endl;
    while (getline(inputFile, line))
    {
        for (wchar_t& symbol : line)
        {
            long long m = symbol;
            long long crypted_m = fast_pow(m, e, n);
            outputFile << crypted_m << " ";
        }
        outputFile << "\n";
    }

    inputFile.close();
    outputFile.close();
}

void rsa_decrypt(std::string inputFileName, std::string outputFileName)
{
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string line;
    long long p, q;
    get_primes(p, q);
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = calculate_e(phi);
    long long d = calculate_d(e, phi);
    while (getline(inputFile, line))
    {
        string crypted_m_str;
        long long crypted_m;
        stringstream ss(line);
        while (getline(ss, crypted_m_str, ' '))
        {
            if (checkIfNumericRSA(crypted_m_str)) {
                crypted_m = stoull(crypted_m_str);
                long long m = fast_pow(crypted_m, d, n);
                char symbol = (char)m;
                outputFile << symbol;
            }
        }
        outputFile << "\n";
    }
    inputFile.close();
    outputFile.close();
}
