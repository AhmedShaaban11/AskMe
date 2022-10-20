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
