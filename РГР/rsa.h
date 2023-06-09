#ifndef RSA_H
#define RSA_H
#include <string>
int_fast64_t  calculate_gcd(int_fast64_t  a, int_fast64_t  b);
int_fast64_t  calculate_e(int_fast64_t  phi);
int_fast64_t  calculate_d(int_fast64_t  e, int_fast64_t  phi);
bool is_prime(int_fast64_t  num);
bool can_encrypt1(int_fast64_t  p, int_fast64_t  q);
bool is_different(int_fast64_t  p, int_fast64_t  q);
bool can_encrypt2(int_fast64_t  p, int_fast64_t  q);
int_fast64_t  fast_pow(int_fast64_t  a, int_fast64_t  b, int_fast64_t  n);
void rsa_encrypt(std::string inputFileName, std::string outputFileName);
void rsa_decrypt(std::string inputFileName, std::string outputFileName);
#endif