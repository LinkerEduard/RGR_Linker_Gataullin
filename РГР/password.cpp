#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "rsa.h"
#include "gro.h"
using namespace std;
void check_numbers(int64_t& p, int64_t& q)
{
    while (!is_prime(p) || !is_prime(q) || !can_encrypt1(p, q) || !is_different(p, q) || !can_encrypt2(p, q) || p <= 0 || q <= 0)
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
}
string pass1_decrypt(string inputFileName, string key) {
    istringstream input(inputFileName);
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
            if (symbol < 0)
            {
                decryptedText += symbol;
            }
            else if ((symbol >= 192 && symbol <= 255) || (symbol >= 65 && symbol <= 90) || (symbol >= 97 && symbol <= 122))
            {
                if ((symbol >= 192) && (symbol <= 223))
                {
                    if (asciiCode > 223)
                    {
                        asciiCode -= 32;
                    }
                    else if (asciiCode < 192)
                    {
                        asciiCode += 32;
                    }
                }
                else if ((symbol >= 224) && (symbol <= 255))
                {
                    if (asciiCode > 255)
                    {
                        asciiCode -= 32;
                    }
                    else if (asciiCode < 224)
                    {
                        asciiCode += 32;
                    }
                }
                else if ((symbol >= 97) && (symbol <= 122))
                {
                    if (asciiCode > 122)
                    {
                        asciiCode -= 26;
                    }
                    else if (asciiCode < 97)
                    {
                        asciiCode += 26;
                    }
                }
                else if ((symbol >= 65) && (symbol <= 90))
                {
                    if (asciiCode > 90)
                    {
                        asciiCode -= 26;
                    }
                    else if (asciiCode < 65)
                    {
                        asciiCode += 26;
                    }
                }
                decryptedText += (char)asciiCode;
            }
            else
            {
                decryptedText += symbol;
            }
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
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] >= 'A' && line[i] <= 'Z') {
                decrypted_pass += char('Z' - (line[i] - 'A'));
            }
            else if (line[i] >= 'a' && line[i] <= 'z') {
                decrypted_pass += char('z' - (line[i] - 'a'));
            }
            else if (line[i] >= 'à' && line[i] <= 'ÿ') {
                decrypted_pass += char('ÿ' - (line[i] - 'à'));
            }
            else if (line[i] >= 'À' && line[i] <= 'ß') {
                decrypted_pass += char('ß' - (line[i] - 'À'));
            }
            else if (line[i] >= '0' && line[i] <= '9') {
                decrypted_pass += char('9' - (line[i] - '0'));
            }
            else {
                decrypted_pass += line[i];
            }
        }
    }
    return decrypted_pass;
}
string pass3_decrypt(string inputFileName, int64_t p, int64_t q)
{
    ifstream inputFile(inputFileName);
    string line;
    check_numbers(p, q);
    int64_t n = p * q;
    int64_t phi = (p - 1) * (q - 1);
    int64_t e = calculate_e(phi);
    int64_t d = calculate_d(e, phi);
    string decrypted_pass = "";
    string crypted_m_str;
    stringstream ss(line);
    while (getline(inputFile, line))
    {
        string crypted_m_str;
        int64_t crypted_m;
        stringstream ss(line);
        while (getline(ss, crypted_m_str, ' '))
        {
            crypted_m = stoull(crypted_m_str);
            int64_t m = fast_pow(crypted_m, d, n);
            char symbol = (char)m;
            decrypted_pass += symbol;
        }
    }
    inputFile.close();
    return decrypted_pass;
}
string get_password(string key, int64_t p, int64_t q) {
    string inputFileName = "password.txt";
    if (key == "" || p <= 0 || q <= 0)
        return "Invalid";
    else
        return (pass1_decrypt(pass2_decrypt(pass3_decrypt(inputFileName, p, q)), key));

}