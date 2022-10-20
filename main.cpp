#include <iostream>
#include "UsersDb/UsersDb.h"

int main() {
  std::cout << UsersDb::LoadData();
  UsersDb::SaveData();
  return 0;
}
