#include<iostream>
#include<string>
#include<cctype>

class PasswordValidator {

    bool length;
    bool hasCapital;
    bool hasSmall;
    bool hasNumber;
    bool hasSpecial;

public:
    PasswordValidator();
    bool isPasswordValid(std:: string );
        
};