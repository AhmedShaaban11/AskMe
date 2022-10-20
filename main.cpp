#include <iostream>
#include "SignUp/SignUp.h"

int main() {
  std::cout << std::boolalpha << SignUp::IsPasswordValid("1423") << '\n';
  return 0;
}
