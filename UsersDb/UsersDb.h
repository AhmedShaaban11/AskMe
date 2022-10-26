//
// Created by ahmed on 10/17/2022.
//

#ifndef ASKME_USERSDB_H
#define ASKME_USERSDB_H

#include <string>
#include "../User/User.h"

class User;

class UsersDb {
 private:
  static std::string ClearEmailFromUpperLettersAndDomainDots(
      const std::string &email);
  static bool IsUsernameUsedBefore(const std::string &username);
  static bool IsEmailUsedBefore(const std::string &email);
  static int GenerateId();
  static bool IsIdOutOfRange(const int &id);
 public:
  static void AddFromQuestion(const int &user_id, const int &que_id);
  static void AddToQuestion(const int &user_id, const int &que_id);
  static void DeleteFromQuestion(const int &que_id, const int &from_id);
  static void DeleteToQuestion(const int &que_id, const int &to_id);
  static bool IsIdExist(const int &id);
  static bool IsAcceptingAnonymous(const int &id);
  static int IsUsernameAndPasswordExist(const std::string &username,
                                         const std::string &password);
  static User LoadUser(const int &id);
  static void LoadData();
  static void SaveData();
  static bool AddUser(const std::string &username, const std::string &email,
                      const std::string &password,
                      const bool &is_accepting_anonymous);
  static void ListUsersSystem();
};


#endif //ASKME_USERSDB_H
