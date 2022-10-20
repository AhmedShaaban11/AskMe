//
// Created by ahmed on 10/20/2022.
//

#include <fstream>
#include "User.h"

User::User() : id(0), username(""), email(""), password(""),
    is_accepting_anonymous(false) { };

std::ofstream& operator<<(std::ofstream &fout, const User &user) {
  fout << user.id << ' ' << user.username << ' ' << user.email << ' '
       << user.password << ' ' << user.is_accepting_anonymous << '\n';
  for (const int &qu : user.ques_from) {
    fout << qu << ' ';
  }
  fout << '\n';
  for (const int &qu : user.ques_to) {
    fout << qu << ' ';
  }
  fout << '\n';
  return fout;
}
