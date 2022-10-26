//
// Created by ahmed on 10/20/2022.
//

#ifndef ASKME_LOGIN_H
#define ASKME_LOGIN_H

#include <string>
#include "../User/User.h"

class LogIn {
 private:
  static bool is_logged_in;
 public:
  static User LogInUser(const std::string &username, const std::string &password);
  static bool LogOutUser();
};


#endif //ASKME_LOGIN_H
