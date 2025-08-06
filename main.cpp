#include "EncryptDecrypt.h"
#include <iostream>
#include <string>

void printUsage() {
    std::cout << "Usage: encryption <e|d> <filepath> <password>" << std::endl;
    std::cout << "  e: encrypt the file" << std::endl;
    std::cout << "  d: decrypt the file" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage();
        return 1;
    }

    std::string operation = argv[1];
    std::string filepath = argv[2];
    std::string password = argv[3];

    if (operation != "e" && operation != "d") {
        printUsage();
        return 1;
    }

    EncryptDecrypt ed;

    if (operation == "e") {
        ed.encryptFile(filepath, password);
        std::cout << "File encrypted successfully." << std::endl;
    } else { // operation == "d"
        ed.decryptFile(filepath, password);
        std::cout << "File decrypted successfully." << std::endl;
    }

    return 0;
}
