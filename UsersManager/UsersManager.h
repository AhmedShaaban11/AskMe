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

class User;
class Question;

class UsersManager {
 private:
  string src_file_;
  map<string, User> users;
  set<string> emails;
 public:
  explicit UsersManager(const string &file_name);
  void Update();
  void Clear();
  void Save() const;
  bool IsUserFound(const string &username);
  bool IsEmailFound(const string &email);
  auto Find(const string &username);
  bool AddFromQnToUser(int id, Question *qn, const string &username);
  bool AddToQnToUser(int id, Question *qn, const string &username);
  auto AccessUser();
  void AddUser();
};

#endif