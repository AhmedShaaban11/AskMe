// 24 Jan 2023
#include "User.h"
#include "../Question/Question.h"
#include "../GeneralFunctions/general_functions.h"

User::User() {

}

User::User(const string &username, const string &email, const string &password,
           bool is_accepting_anonymous)
    : username_{username}, email_{email}, password_{password},
    is_accepting_anonymous_{is_accepting_anonymous} {

}

User::User(const string &line, const string &delimiter) {
  vector<string> entries = gpm::LineToWords(line, delimiter);
  username_ = entries[0];
  email_ = entries[1];
  password_ = entries[2];
  is_accepting_anonymous_ = (bool) std::stoi(entries[3]);
}

string User::GetUsername() const {
  return username_;
}

string User::GetEmail() const {
  return email_;
}

string User::GetPassword() const {
  return password_;
}

bool User::IsAcceptingAnonymous() const {
  return is_accepting_anonymous_;
}

string User::ToString(const string &del) const {
  string res;
  res = gpm::ToString(del, username_, email_, password_,
                      std::to_string(is_accepting_anonymous_));
  return res;
}
