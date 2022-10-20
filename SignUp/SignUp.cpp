//
// Created by ahmed on 10/20/2022.
//

#include <regex>
#include <string>
#include "SignUp.h"

bool SignUp::IsUsernameValid(const std::string &username) {
  std::regex valid("[a-zA-Z]([a-zA-Z0-9]*[_]?[a-zA-Z0-9]+)*");
  return std::regex_match(username, valid);
}

bool SignUp::IsEmailValid(const std::string &email) {
  std::string local_part = "[#!%$‘&+*/=?^_`{|}~0-9a-zA-Z-]+(.[#!%$‘&+*/=?^_`{|}~0-9a-zA-Z-]+)*";
  std::string first_domain_part = "[0-9a-zA-Z]+(-[0-9a-zA-Z]+)*";
  std::string other_domain_parts = "(\\." + first_domain_part + ")+";
  std::regex valid (local_part + "@" + first_domain_part + other_domain_parts);
  return std::regex_match(email, valid);
}

bool SignUp::IsPasswordValid(const std::string &password) {
  std::regex valid("[^ ]{4,}");
  return std::regex_match(password, valid);
}
