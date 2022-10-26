#include <iostream>
#include "SignUp/SignUp.h"
#include "UsersDb/UsersDb.h"
#include "QuesDb/QuesDb.h"
#include "User/User.h"
#include "LogIn/LogIn.h"

int main() {
//  User user(0, "Ahmed", "a@gmail.com", "1234", 1);
  User *ptr = new User(LogIn::LogInUser("Mahmoud", "1234"));
  ptr->PrintQuestionsTo();
  ptr->DeleteQuestion(6);
//  ptr->DeleteQuestion(6);
  return 0;
}
