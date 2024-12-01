#include "password_auth.h"


PasswordValidator:: PasswordValidator(): length(false), hasCapital(false), hasSmall(false), hasNumber(false), hasSpecial(false){ }

bool PasswordValidator:: isPasswordValid(std:: string password){

    if(password.length() >= 8){
        length = true;
    }

    for (char c : password) {

        if (std::isupper(c)) {
            hasCapital = true;
        } 

        else if (std::islower(c)) {
            hasSmall = true;
        } 

        else if (std::isdigit(c)) {
            hasNumber = true;
        } 

        else if (!std::isalnum(c)) {
            hasSpecial = true;
        }

    }
    
    return length && hasCapital && hasSmall && hasNumber && hasSpecial;
}
        
