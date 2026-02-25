# File Encryption and Decryption System (C++)

This project implements a console-based file encryption and decryption system in C++.  
It supports user authentication, two encryption schemes, and secure storage of encrypted files.  
The system is designed for introductory-level security applications and coursework.

## Overviev

The program provides the following capabilities:

1. User Management
- Account creation with an 8-character username and password.
- Login functionality with validation.
- Credentials stored locally in `logins.txt`.

2. Encryption
Two encryption levels are supported:

**XOR Encryption (Low Level)**  
- Uses a randomly generated integer key (1–100).  
- Each byte of the source file is XORed with the key.

**Vigenère-Based Encryption (High Level)**  
- Generates a random alphabetic key (length 1–5).  
- Performs character shifting using ASCII values.  
- Supports multi-line text.

After encryption, the original file is automatically deleted for security.

3. Encrypted File Storage
For each user, two files are created:
- `<username>1.txt` — Index of original filenames.
- `<username>2.txt` — Encryption metadata, keys, and encrypted content.

Structure of stored data:
<method> <original_filename>
<key>
<encrypted_content>
END

4. Decryption
- Lists available encrypted files for the logged-in user.
- Detects whether XOR or Vigenère was used.
- Restores the original plaintext file.
