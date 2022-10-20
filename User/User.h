//
// Created by ahmed on 10/20/2022.
//

#ifndef ASKME_USER_H
#define ASKME_USER_H

#include <vector>
#include <string>
#include "../UsersDb/UsersDb.h"

class User {
 private:
  int id;
  std::string username;
  std::string email;
  std::string password;
  bool is_accepting_anonymous;
  std::vector<int> ques_from;
  std::vector<int> ques_to;
  friend std::ofstream& operator<<(std::ofstream &fout, const User &user);
  friend class UsersDb;
 public:
  User();
};


#endif //ASKME_USER_H
