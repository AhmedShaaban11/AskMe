//
// Created by ahmed on 10/20/2022.
//

#include <string>
#include "LogIn.h"
#include "../User/User.h"
#include "../UsersDb/UsersDb.h"

bool LogIn::is_logged_in = false;

User LogIn::LogInUser(const std::string &username, const std::string &password) {
  if (is_logged_in) { return {}; }
  int id = UsersDb::IsUsernameAndPasswordExist(username, password);
  if (id == -1) { return {}; }
  is_logged_in = true;
  return UsersDb::LoadUser(id);;
}

bool LogIn::LogOutUser() {
  if (!is_logged_in) { return false; }
  is_logged_in = false;
  return true;
}

bool LogIn::IsLoggedIn() {
  return is_logged_in;
}
