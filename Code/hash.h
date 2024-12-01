#include<openssl/sha.h>
#include<string>
class PasswordEncryptor {

    std:: string password;

public:
    PasswordEncryptor(std::string);
 
    std::string HashPassword();
};