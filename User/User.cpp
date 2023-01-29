// 24 Jan 2023
#include "User.h"
#include "../Question/Question.h"
#include "../GeneralFunctions/general_functions.h"

User::User() {

}

User::User(const string &username, const string &email, const string &password)
    : username_{username}, email_{email}, password_{password} {

}

User::User(const string &line, const string &delimiter) {
  vector<string> entries = LineToWords(line, delimiter);
  username_ = entries[0];
  email_ = entries[1];
  password_ = entries[2];
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

string User::ToString(const string &del) const {
  string res;
  res = username_ + del + email_ + del + password_;
  return res;
}
