#ifndef RSA_H
#define RSA_H
#include <string>
int64_t  calculate_gcd(int64_t  a, int64_t  b);
int64_t  calculate_e(int64_t  phi);
int64_t  calculate_d(int64_t  e, int64_t  phi);
bool is_prime(int64_t  num);
bool can_encrypt1(int64_t  p, int64_t  q);
bool is_different(int64_t  p, int64_t  q);
bool can_encrypt2(int64_t  p, int64_t  q);
int64_t  fast_pow(int64_t  a, int64_t  b, int64_t  n);
void rsa_encrypt(std::string inputFileName, std::string outputFileName);
void rsa_decrypt(std::string inputFileName, std::string outputFileName);
#endif