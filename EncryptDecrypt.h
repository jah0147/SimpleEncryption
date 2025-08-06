//
// Created by jacob_howard on 10/24/2023.
//
#include "string"
#include <algorithm>
#include "iostream"
#include <fstream>
#include "sstream"
using namespace std;

#ifndef TEST_ENCRYPTDECRYPT_H
#define TEST_ENCRYPTDECRYPT_H


class EncryptDecrypt
{
public:
    EncryptDecrypt();

    // Encrypt a file using a password
    void encryptFile(const string& filename, const string& password);
    // Decrypt a file using a password
    void decryptFile(const string& filename, const string& password);

private:
    // Derives a numeric key from a password string
    int deriveKey(const string& password);
    // The core encryption algorithm for a string
    string encrypt(string text, int key);
    // The core decryption algorithm for a string
    string decrypt(string encryptedText, int key);
};


#endif //TEST_ENCRYPTDECRYPT_H
