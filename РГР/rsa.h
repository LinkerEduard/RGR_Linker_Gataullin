#ifndef RSA_H
#define RSA_H
#include <string>
long long calculate_gcd(long long a, long long b);
long long calculate_e(long long phi);
long long calculate_d(long long e, long long phi);
bool is_prime(long long num);
bool can_encrypt1(long long p, long long q);
bool is_different(long long p, long long q);
bool can_encrypt2(long long p, long long q);
long long fast_pow(long long a, long long b, long long n);
void rsa_encrypt(std::string inputFileName, std::string outputFileName);
void rsa_decrypt(std::string inputFileName, std::string outputFileName);
#endif