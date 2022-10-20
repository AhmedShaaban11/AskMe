//
// Created by ahmed on 10/20/2022.
//

#ifndef ASKME_SIGNUP_H
#define ASKME_SIGNUP_H

#include <string>

class SignUp {
 public:
  static bool IsUsernameValid(const std::string &username);
  static bool IsEmailValid(const std::string &email);
};


#endif //ASKME_SIGNUP_H
