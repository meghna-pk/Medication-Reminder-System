#include "hash.h"

PasswordEncryptor::PasswordEncryptor(std::string pw) : password(pw) {}

std::string PasswordEncryptor::HashPassword()
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    std::string hashed_password;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        char hex[3];
        sprintf(hex, "%02x", hash[i]);
        hashed_password += hex;
    }

    return hashed_password;
}
