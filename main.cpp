#include <iostream>
#include <vector>
#include "SignUp/SignUp.h"

int main() {
  std::vector<std::string> vec = {
      "mysite.ourearth.com",
      "mysite@.com.my",
      "@you.me.net",
      "mysite123@gmail.b",
      "mysite@.org.org",
      ".mysite@mysite.org",
      "mysite()*@gmail.com",
      "mysite..1234@yahoo.com"
  };
  for (const std::string &val : vec) {
    std::cout << std::boolalpha << SignUp::IsEmailValid(val) << std::endl;
  }
  return 0;
}
