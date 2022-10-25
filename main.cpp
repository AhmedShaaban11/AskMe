#include <iostream>
#include "SignUp/SignUp.h"
#include "UsersDb/UsersDb.h"
#include "QuesDb/QuesDb.h"
#include "User/User.h"

int main() {
//  User user(0, "Ahmed", "a@gmail.com", "1234", 1);
  User user2(2, "Mahmoud", "mahmoud@yahoo.com", "1234", true);
  user2.Ask(3, "Akramak Allah!", false, 6);
  user2.Answer(5, "I'm fine. Thank you.");
  return 0;
}
