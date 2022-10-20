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
};


#endif //ASKME_USERSDB_H
