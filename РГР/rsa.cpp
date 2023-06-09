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
uint_fast64_t  calculate_gcd(uint_fast64_t  p, uint_fast64_t  q)
{
    if (q == 0)
        return p;
    else
        return calculate_gcd(q, p % q);
}
uint_fast64_t  calculate_e(uint_fast64_t  phi)
{
    uint_fast64_t  e = 2;
    while (e < phi && calculate_gcd(e, phi) != 1)
    {
        e++;
    }
    return e;
}
uint_fast64_t  calculate_d(uint_fast64_t  e, uint_fast64_t  phi)
{
    uint_fast64_t  d = 1;
    while ((d * e) % phi != 1)
    {
        d++;
    }
    return d;
}
bool is_prime(uint_fast64_t  num)
{
    if (num == 1)
        return false;

    for (uint_fast64_t  i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}
bool can_encrypt1(uint_fast64_t  p, uint_fast64_t  q)
{
    if ((p-1) * (q-1) >= 255)
        return true;
    else
        return false;
}
bool is_different(uint_fast64_t  p, uint_fast64_t  q)
{
    if (p != q)
        return true;
    else
        return false;
}
bool can_encrypt2(uint_fast64_t  p, uint_fast64_t  q)
{
    if (p * q <= 3025550009)
        return true;
    else
        return false;
}
void get_primes(uint_fast64_t & p, uint_fast64_t & q)
{
    string primes;
    cout << "Enter two different prime numbers separated by space: ";
    Invalidinput :
    getline(cin, primes);
    stringstream ss(primes);
    ss >> p >> q;
        if (p <= 0 || q <= 0) {
            cout << "Invalid input. Please enter two different prime numbers separated by space: ";
            goto Invalidinput;
        }
        if (!is_prime(p) || !is_prime(q)) {
            cout << "Invalid input. Please enter two different prime numbers separated by space: ";
            goto Invalidinput;
        }
        if (!is_different(p, q)) {
            cout << "Invalid input. Please enter two different prime numbers separated by space: ";
            goto Invalidinput;
        }
        if (!can_encrypt1(p, q)) {
            cout << "Invalid input. Please enter two prime larger numbers separated by space ((p-1)*(q-1)>254): ";
            goto Invalidinput;
        }
        if (!can_encrypt2(p, q)) {
            cout << "Invalid input. Please enter two smaller prime numbers separated by space (p*q<3025550010): ";
            goto Invalidinput;
        }
}
uint_fast64_t  fast_pow(uint_fast64_t  a, uint_fast64_t  b, uint_fast64_t  n)
{
    uint_fast64_t  res = 1;
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
void rsa_encrypt(string& inputFileName, string& outputFileName)
{
    wifstream inputFile(inputFileName);
    wofstream outputFile(outputFileName);
    wstring line;
    uint_fast64_t  p, q;
    get_primes(p, q);
    uint_fast64_t  n = p * q;
    uint_fast64_t  phi = (p - 1) * (q - 1);
    uint_fast64_t  e = calculate_e(phi);
    uint_fast64_t  d = calculate_d(e, phi); 
    cout << "Public key: " << e << " ; " << n << endl;
    cout << "Private key: " << d << " ; " << n << endl;
    while (getline(inputFile, line))
    {
        for (wchar_t& symbol : line)
        {
            uint_fast64_t  m = symbol;
            uint_fast64_t  crypted_m = fast_pow(m, e, n);
            outputFile << crypted_m << " ";
        }
        outputFile << "\n";
    }

    inputFile.close();
    outputFile.close();
}
void rsa_decrypt(string& inputFileName, string& outputFileName)
{
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string line;
    uint_fast64_t  p, q;
    get_primes(p, q);
    uint_fast64_t  n = p * q;
    uint_fast64_t  phi = (p - 1) * (q - 1);
    uint_fast64_t  e = calculate_e(phi);
    uint_fast64_t  d = calculate_d(e, phi);
    while (getline(inputFile, line))
    {
        string crypted_m_str;
        uint_fast64_t  crypted_m;
        stringstream ss(line);
        while (getline(ss, crypted_m_str, ' '))
        {
            if (checkIfNumericRSA(crypted_m_str)) {
                crypted_m = stoull(crypted_m_str);
                uint_fast64_t  m = fast_pow(crypted_m, d, n);
                char symbol = (char)m;
                outputFile << symbol;
            }
        }
        outputFile << "\n";
    }
    inputFile.close();
    outputFile.close();
}
