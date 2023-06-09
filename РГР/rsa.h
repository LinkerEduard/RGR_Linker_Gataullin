#ifndef RSA_H
#define RSA_H
#include <string>
uint_fast64_t  calculate_gcd(uint_fast64_t  a, uint_fast64_t  b);
uint_fast64_t  calculate_e(uint_fast64_t  phi);
uint_fast64_t  calculate_d(uint_fast64_t  e, uint_fast64_t  phi);
bool is_prime(uint_fast64_t  num);
bool can_encrypt1(uint_fast64_t  p, uint_fast64_t  q);
bool is_different(uint_fast64_t  p, uint_fast64_t  q);
bool can_encrypt2(uint_fast64_t  p, uint_fast64_t  q);
uint_fast64_t  fast_pow(uint_fast64_t  a, uint_fast64_t  b, uint_fast64_t  n);
void rsa_encrypt(std::string& inputFileName, std::string& outputFileName);
void rsa_decrypt(std::string& inputFileName, std::string& outputFileName);
#endif