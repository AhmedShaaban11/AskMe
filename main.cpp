#include <iostream>
#include "SignUp/SignUp.h"
#include "UsersDb/UsersDb.h"
#include "QuesDb/QuesDb.h"
#include "User/User.h"

int main() {
  User user(0, "Ahmed", "a@gmail.com", "1234", 1);
  user.Ask(2, "How are you?");
  return 0;
}
