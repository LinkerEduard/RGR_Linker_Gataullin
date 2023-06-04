#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool checkIfNumeric(string str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}
void gro_encrypt(string inputFileName, string outputFileName) {
    wifstream input(inputFileName);
    wofstream output(outputFileName);
    string key;
    do {
        cout << "Enter key: ";
        getline(cin, key);
        if (!(checkIfNumeric(key)))
            cout << "Invalid Key (The number must be a natural number). Please try again." << endl;
        else {
            int keyLength = key.length();
            int* keyArray = new int[keyLength];
            for (int i = 0; i < keyLength; i++)
            {
                keyArray[i] = key[i] - '0';
            }
            wstring line;
            while (getline(input, line)) {
                for (int i = 0; i < line.length(); i++) {
                    wchar_t symbol = line[i]; if (symbol == ' ') {
                        output << " ";
                        continue;
                    }
                    int asciiCode = (int)symbol + keyArray[i % keyLength];
                   
                    if (symbol < 0)
                    {
                        output << symbol;
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
                    else
                    {
                        output << symbol;
                    }
                    output << (wchar_t)asciiCode;
                }
                    else
                    {
                    output << symbol;
                    }
            }
                output << endl;
            }

            input.close();
            output.close();
            delete[] keyArray;
        }
    } while (!(checkIfNumeric(key)));
}
void gro_decrypt(string inputFileName, string outputFileName) {
    wifstream input(inputFileName);
    wofstream output(outputFileName);
    string key;
    do {
        cout << "Enter key: ";
        getline(cin, key);
        if (!(checkIfNumeric(key)))
            cout << "Invalid Key (The number must be a natural number). Please try again." << endl;
        else {
            int keyLength = key.length();
            int* keyArray = new int[keyLength];
            for (int i = 0; i < keyLength; i++)
            {
                keyArray[i] = key[i] - '0';
            }
            wstring line;
            while (getline(input, line))
            {
                for (int i = 0; i < line.length(); i++)
                {
                    wchar_t symbol = line[i];
                    if (symbol == ' ')
                    {
                        output << " ";
                        continue;
                    }
                    int asciiCode = (int)symbol - keyArray[i % keyLength];
                    if (symbol < 0)
                    {
                        output << symbol;
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
                    output << (wchar_t)asciiCode;
                    }
                    else
                    {
                        output << symbol;
                    }
                }
                output << endl;
            }
            input.close();
            output.close();
            delete[] keyArray;
        }
    } while (!(checkIfNumeric(key)));
}