#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <openssl/sha.h>
#include "hash.h"

// Base class User
class User
{
    std::string Id;

    std::string username;

    std::string password;

public:
    User();

    User(const std::string &, const std::string &);

    // Virtual function for registration
    virtual std::string Register(){};

    // Virtual function for login
    virtual std::string Login(){};

    std::string getId() const;

    std::string getUsername() const;

    std::string getPassword() const;

    std::string GenerateTimestampBasedId();

    void setId(std::string);
};

// Derived class for registered users
class RegisterUser : public User
{

    std::string hashed_password;

public:
    RegisterUser();

    RegisterUser(const std::string &, const std::string &);

    std::string Register();

    std::string Login();
};

// Derived class for logged-in users

class LoggedInUser : public User
{

public:
    LoggedInUser();

    LoggedInUser(const std::string &, const std::string &);

    std::string Register();

    std::string Login();
};