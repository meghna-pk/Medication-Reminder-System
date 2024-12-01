#include "client.h"
#include <thread>

void Client ::registration()
{
    // std :: cout << "Registration" << std :: endl;"
    std ::cout << "Enter your username : " << std ::endl;
    std ::cin >> username;
    std ::cout << "Enter your password : " << std ::endl;
    std ::cin >> password;

    PasswordValidator p;

    while (1)
    {
        if (p.isPasswordValid(password) == 1)
        {
            break;
        }
        else
        {
            std::cout << "Enter a valid password:";
            std::cin >> password;
        }
    }
}

void Client ::login()
{
    std::string id;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
}

void Client ::logout()
{
    exit(0);
}

void Client ::addMedicine()
{

    std ::cout << "Enter the medicine name: ";
    std ::cin >> medname;

    std ::cout << "\nEnter the number of days: ";
    std ::cin >> day;

    std ::cout << "\nEnter the time(hh:mm) in 24 hour format: ";
    std ::cin >> time;

    std ::cout << "\nShould the medicine be taken before food?(y/n) ";
    std ::cin >> before_food;

    if (before_food == 'y')
    {
        before = true;
    }
    else
    {
        before = false;
    }

    std ::cout << "\nSelect the type of medicine:\n";
    std ::cout << "1. Tablet\n2. Tonic\n";

    std ::cin >> option;

    if (option == 1)
    {
        std ::cout << "\nEnter quantity(in numbers): ";
        std ::cin >> quantity;
    }
    else if (option == 2)
    {
        std ::cout << "\nEnter quantity(in ml): ";
        std ::cin >> quantity;
    }
    else
    {
        std ::cout << "Enter a valid option\n";
    }
}

std ::string Client ::getUsername()
{
    return username;
}

std ::string Client ::getPassword()
{
    return password;
}

std ::string Client ::getMedname()
{
    return medname;
}

std ::string Client ::getDay()
{
    return day;
}

std ::string Client ::getTime()
{
    return time;
}

bool Client ::getBefore()
{
    return before;
}
std ::string Client ::getQuantity()
{
    return quantity;
}