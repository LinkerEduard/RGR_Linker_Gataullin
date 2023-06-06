#ifndef CIPHER_H
#define CIPHER_H
#include <string>
bool fileDifferent(std::string inputFileName, std::string outputFileName);
bool fileExists(std::string inputFileName);
void encryptFile(std::string inputFileName, std::string outputFileName, std::string choice);
void decryptFile(std::string outputFileName, std::string inputFileName, std::string choice);
#endif