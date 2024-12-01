#include "login.h"

User::User() : username("default"), password("Password@123") {}

User::User(const std::string &username, const std::string &password) : username(username), password(password), Id(GenerateTimestampBasedId()) {}

std::string User::getId() const
{
    return Id;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

std::string User::GenerateTimestampBasedId()
{

    auto now = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << timestamp;
    return ss.str();
}

void User::setId(std::string id)
{
    Id = id;
}

RegisterUser::RegisterUser() : User() {}

RegisterUser::RegisterUser(const std::string &username, const std::string &password) : User(username, password)
{
    // Hash the password before storing it
    PasswordEncryptor pe(password);

    hashed_password = pe.HashPassword();
}

// New user registration
std::string RegisterUser::Register()
{
    std::string msg;
    std::ifstream File("users.txt");

    std::string id, storedUsername, storedHashedPassword;

    while (File >> id >> storedUsername >> storedHashedPassword)
    {

        if (storedUsername == User::getUsername() && storedHashedPassword == hashed_password)
        {
            msg = "User already exists!\n";
            return msg;
        }
    }
    File.close();
    
    msg = "User registered with username: " + User::getUsername() + "\n";

    // Store user details in a file

    std::ofstream userFile("users.txt", std::ios::app);

    userFile << User::getId() << " " << User::getUsername() << " " << hashed_password << std::endl;

    userFile.close();

    return msg;
}

std::string RegisterUser::Login()
{
    return "nil";
}

// Existing user login
LoggedInUser::LoggedInUser(const std::string &username, const std::string &password) : User(username, password) {}

std::string LoggedInUser::Register() {}

std::string LoggedInUser::Login()
{

    // Check if the user exists in the file
    std::ifstream userFile("users.txt");

    std::string msg, id;
    std::string storedUsername, storedHashedPassword;

    while (userFile >> id >> storedUsername >> storedHashedPassword)
    {

        if (storedUsername == User::getUsername())
        {

            // Hash the input password and compare with stored hashed password
            PasswordEncryptor pe(User::getPassword());

            std::string inputHashedPassword = pe.HashPassword();

            if (inputHashedPassword == storedHashedPassword)
            {

                msg = "User loggeed in:" + User::getUsername() + "\n";

                User::setId(id);

                userFile.close();

                return msg;
            }
        }
    }

    userFile.close();
    msg = "Invalid Credentials\n";
    return msg;
}
