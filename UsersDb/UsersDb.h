//
// Created by ahmed on 10/17/2022.
//

#ifndef ASKME_USERSDB_H
#define ASKME_USERSDB_H

#include "../User/User.h"


class UsersDb {
 public:
  static bool LoadData();
  static void SaveData();
  static bool AddUser(const std::string &username, const std::string &email,
                      const std::string &password,
                      const bool &is_accepting_anonymous);
};


#endif //ASKME_USERSDB_H
