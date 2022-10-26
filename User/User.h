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
  int id_;
  std::string username_;
  std::string email_;
  std::string password_;
  bool is_accepting_anonymous_;
  std::vector<int> ques_from_;
  std::vector<int> ques_to_;
  friend std::ofstream& operator<<(std::ofstream &fout, const User &user);
  friend std::ifstream& operator>>(std::ifstream &fin, User &user);
  friend class UsersDb;
 public:
  bool Ask(const int &to_id, const std::string &question,
           const bool &is_anonymous = false, const int &parent_id = -1);
  bool Answer(const int &que_id, const std::string &answer) const;
  bool DeleteQuestion(const int &que_id);
  User();
  User(const int &id, const std::string &username, const std::string &email,
       const std::string &password, const bool &is_accepting_anonymous);
};


#endif //ASKME_USER_H
