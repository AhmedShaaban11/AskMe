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
  static bool IsPasswordValid(const std::string &password);
  static bool Sign(const std::string &username, const std::string &email,
                   const std::string &password,
                   const bool &is_accepting_anonymous);
};


#endif //ASKME_SIGNUP_H
