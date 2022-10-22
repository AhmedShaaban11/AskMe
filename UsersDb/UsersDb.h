//
// Created by ahmed on 10/17/2022.
//

#ifndef ASKME_USERSDB_H
#define ASKME_USERSDB_H

#include "../User/User.h"


class UsersDb {
 private:
  static std::string ClearEmailFromUpperLettersAndDomainDots(
      const std::string &email);
  static bool IsUsernameUsedBefore(const std::string &username);
  static bool IsEmailUsedBefore(const std::string &email);
  static int GenerateId();
 public:
  static bool LoadData();
  static void SaveData();
  static bool AddUser(const std::string &username, const std::string &email,
                      const std::string &password,
                      const bool &is_accepting_anonymous);
};


#endif //ASKME_USERSDB_H
