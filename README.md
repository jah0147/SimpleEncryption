# Simple C++ File Encryption

## Overview

This is a simple command-line application written in C++ that allows you to encrypt and decrypt files using a password. The application uses a basic transposition cipher for its encryption algorithm.

## How it Works

The encryption algorithm is a simple transposition cipher. It works by repeatedly rearranging the characters of the input text.

1.  **Key Derivation:** The password you provide is converted into a numeric "key". This is done by summing the ASCII values of all characters in the password. The result is then taken modulo 50 (to keep the number of iterations reasonable) and 1 is added (to ensure the key is never zero).

2.  **Transposition:** The application then iterates a number of times equal to the derived key. In each iteration, it splits the text into two strings: one containing all the characters at even positions, and one containing all the characters at odd positions. It then concatenates these two strings (`odds` + `evens`) to form the new text for the next iteration.

Decryption is the reverse of this process. It intelligently splits the encrypted text back into the "odds" and "evens" parts and reconstructs the original text, repeating the process for the same number of key iterations.

## How to Build

The project uses CMake for building. You will need a C++ compiler (like g++) and CMake installed on your system.

1.  **Clone the repository:**
    ```bash
    git clone <repository-url>
    cd <repository-directory>
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake to configure the project:**
    ```bash
    cmake ..
    ```

4.  **Compile the source code:**
    ```bash
    make
    ```
    This will create an executable named `encryption` in the `build` directory.

## How to Use

The application is run from the command line and takes three arguments.

**Syntax:**
```bash
./build/encryption <operation> <filepath> <password>
```

**Arguments:**

*   `<operation>`:
    *   `e`: Encrypt the file.
    *   `d`: Decrypt the file.
*   `<filepath>`: The path to the file you want to process.
*   `<password>`: The password to use for encryption or decryption.

**Example: Encrypting a file**
```bash
./build/encryption e my_secret_document.txt "p@ssw0rd123"
```

**Example: Decrypting a file**
```bash
./build/encryption d my_secret_document.txt "p@ssw0rd123"
```

**Note:** The application modifies the file in-place. Make sure you have a backup if the data is critical.
