#ifndef ATB_H
#define ATB_H
#include <string>
void atb_encrypt(std::string& inputFileName, std::string& outputFileName);
void atb_decrypt(std::string& inputFileName, std::string& outputFileName);
void changeatb(int& asciiCode);
#endif