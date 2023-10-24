#include "EncryptDecrypt.h"
using namespace std;


int main() {

    EncryptDecrypt ed;

    //Returns whether the user wants to Encrypt (T) or Decrypt (F)
    bool bEncrypt = ed.getUsrInput();
    //Depending on ecnrypt or decrpyt, select whether to do a string or file

    ed.encryption_decryption(bEncrypt);

    return 0;
}
