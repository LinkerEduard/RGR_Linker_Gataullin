#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "rsa.h"
#include "gro.h"
#include "atb.h"
using namespace std;
void check_numbers(int_fast64_t& p, int_fast64_t& q)
{
        if (p <= 0 || q <= 0) {
            p = 17;
            q = 19;
        }
        if (!is_prime(p) || !is_prime(q)) {
            p = 17;
            q = 19;
        }
        if (!is_different(p, q)) {
            p = 17;
            q = 19;
        }
        if (!can_encrypt1(p, q)) {
            p = 17;
            q = 19;
        }
        if (!can_encrypt2(p, q)) {
            p = 17;
            q = 19;
        }
}
string pass1_decrypt(string inputString, string key) {
    istringstream input(inputString);
    if (!(checkIfNumeric(key))) key = "666";
    int keyLength = key.length();
    int* keyArray = new int[keyLength];
    for (int i = 0; i < keyLength; i++)
    {
        keyArray[i] = key[i] - '0';
    }
    string decryptedText = "";
    string line;
            while (getline(input, line))
            {
                for (int i = 0; i < line.length(); i++)
                {
                    char symbol = line[i];
                    if (symbol == ' ')
                    {
                        decryptedText += " ";
                        continue;
                    }
                    int asciiCode = (int)symbol - keyArray[i % keyLength];
                    changegro(asciiCode, symbol);
                    decryptedText += (char)asciiCode;
                }
            }
            delete[] keyArray;
            return decryptedText;
}
string pass2_decrypt(string inputString)
{
    istringstream iss(inputString);
    string line;
    string decrypted_pass = "";
    while (getline(iss, line)) {
        for (int i = 0; i < line.length(); i++) {
            char symbol = line[i];
            int asciiCode = (int)symbol;
            changeatb(asciiCode);
            decrypted_pass += (char)asciiCode;
        }
    }
    return decrypted_pass;
}
string pass3_decrypt(string inputFileName, int_fast64_t p, int_fast64_t q)
{
    ifstream inputFile(inputFileName);
    string line;
    check_numbers(p, q);
    int_fast64_t n = p * q;
    int_fast64_t phi = (p - 1) * (q - 1);
    int_fast64_t e = calculate_e(phi);
    int_fast64_t d = calculate_d(e, phi);
    string decrypted_pass = "";
    string crypted_m_str;
    stringstream ss(line);
    while (getline(inputFile, line))
    {
        string crypted_m_str;
        int_fast64_t crypted_m;
        stringstream ss(line);
        while (getline(ss, crypted_m_str, ' '))
        {
            crypted_m = stoull(crypted_m_str);
            int_fast64_t m = fast_pow(crypted_m, d, n);
            char symbol = (char)m;
            decrypted_pass += symbol;
        }
    }
    inputFile.close();
    return decrypted_pass;
}
string get_password(string key, int_fast64_t p, int_fast64_t q) {
    string inputFileName = "password.txt";
    if (key == "" || p <= 0 || q <= 0)
        return "Invalid";
    else
        return (pass1_decrypt(pass2_decrypt(pass3_decrypt(inputFileName, p, q)), key));

}