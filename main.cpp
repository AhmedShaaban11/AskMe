#include <iostream>
#include "SignUp/SignUp.h"

int main() {
  std::cout << std::boolalpha << SignUp::IsUsernameValid("ahmed1");
  return 0;
}
