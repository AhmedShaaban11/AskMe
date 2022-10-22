//
// Created by ahmed on 10/20/2022.
//

#include <fstream>
#include <sstream>
#include "User.h"

User::User() : id_(-1), username_(""), email_(""), password_(""),
    is_accepting_anonymous_(false) { }

User::User(const int &id, const std::string &username, const std::string &email,
           const std::string &password, const bool &is_accepting_anonymous)
           : id_(id), username_(username), email_(email), password_(password),
           is_accepting_anonymous_(is_accepting_anonymous) {  }

std::ofstream& operator<<(std::ofstream &fout, const User &user) {
  fout << user.id_ << ' ' << user.username_ << ' ' << user.email_ << ' '
       << user.password_ << ' ' << user.is_accepting_anonymous_ << '\n';
  for (const int &qu : user.ques_from_) {
    fout << qu << ' ';
  }
  fout << '\n';
  for (const int &qu : user.ques_to_) {
    fout << qu << ' ';
  }
  fout << '\n';
  return fout;
}

std::ifstream& operator>>(std::ifstream &fin, User &user) {
  fin >> user.id_ >> user.username_ >> user.email_ >> user.password_
      >> user.is_accepting_anonymous_;
  fin.ignore(); // Ignores \n at the end
  int qu;
  std::string holder;
  std::stringstream ss;
  // Getting questions from this user
  getline(fin, holder);
  ss << holder;
  while (ss >> qu) { user.ques_from_.push_back(qu); }
  ss.clear();
  // Getting questions to this user
  getline(fin, holder);
  ss << holder;
  while (ss >> qu) { user.ques_to_.push_back(qu); }
  ss.clear();
  return fin;
}
