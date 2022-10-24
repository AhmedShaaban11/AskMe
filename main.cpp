#include <iostream>
#include "SignUp/SignUp.h"
#include "UsersDb/UsersDb.h"
#include "QuesDb/QuesDb.h"

int main() {
  QuesDb::DeleteQuestion(2, 4);
  return 0;
}
