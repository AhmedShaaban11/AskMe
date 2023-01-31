// 24 Jan 2023
#ifndef ASKME_USER_USER_H
#define ASKME_USER_USER_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::map;
using std::vector;

class Question;

class User {
 private:
  string username_;
  string email_;
  string password_;
  bool is_accepting_anonymous_;
 public:
  User();
  User(const string &username, const string &email, const string &password,
       bool is_accepting_anonymous = true);
  explicit User(const string &line, const string &delimiter = ",");
  string GetUsername() const;
  string GetEmail() const;
  string GetPassword() const;
  bool IsAcceptingAnonymous() const;
  string ToString(const string &del = ",") const;
};

#endif