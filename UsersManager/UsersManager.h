#ifndef ASKME_USERSMANAGER_USERSMANAGER_H
#define ASKME_USERSMANAGER_USERSMANAGER_H

#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>

using std::string;
using std::map;
using std::set;
using std::ofstream;
using std::cin;
using std::cout;

const char KUsersSrcPath[] = "../UsersManager/users_data.csv";

class User;
class Question;

class UsersManager {
 private:
  map<string, User> users_;
  set<string> emails_;
 public:
  UsersManager();
  ~UsersManager();
  void Update();
  void Clear();
  void Save() const;
  bool IsUserFound(const string &username);
  bool IsEmailFound(const string &email);
  User* AccessUser();
  void AddUser();
};

#endif