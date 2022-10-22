//
// Created by ahmed on 10/17/2022.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include "UsersDb.h"
#include "../User/User.h"

const char KDataPath[] = "../data/users_data.txt";

std::vector<User> data;

int UsersDb::GenerateId() {
  return (int) data.size();
}

std::string UsersDb::ClearEmailFromUpperLettersAndDomainDots(
    const std::string &email) {
  std::string new_email;
  int at_pos = (int) email.find('@');
  for (int i = 0; i < (int) email.length(); ++i) {
    char c = email[i];
    if (c == '.' && i < at_pos) {
      continue;
    } else if (std::isalpha(c)) {
      new_email += (char) tolower(c);
    } else {
      new_email += c;
    }
  }
  return new_email;
}

bool UsersDb::IsUsernameUsedBefore(const std::string &username) {
  LoadData();
  for (const User &user : data) {
    if (user.username_ == username) { return true; }
  }
  return false;
}

bool UsersDb::IsEmailUsedBefore(const std::string &email) {
  LoadData();
  for (const User &user : data) {
    if (user.email_ == email) { return true; }
  }
  return false;
}

bool UsersDb::LoadData() {
  if (!data.empty()) { // if data loaded before
    return false;
  }
  std::ifstream fin(KDataPath, std::ios::in);
  assert(!fin.fail());
  while (fin.peek() != EOF) {
    User user;
    fin >> user;
    data.push_back(user);
  }
  fin.close();
  return true;
}

void UsersDb::SaveData() {
  std::ofstream fout(KDataPath, std::ios::out);
  assert(!fout.fail());
  for (const User &user : data) {
    fout << user;
  }
  fout.close();
}

bool UsersDb::AddUser(const std::string &username, const std::string &email,
                      const std::string &password,
                      const bool &is_accepting_anonymous) {
  LoadData();
  std::string cur_email = ClearEmailFromUpperLettersAndDomainDots(email);
  if (IsUsernameUsedBefore(username)) {
    std::cout << "Username used before.\n";
    return false;
  } else if (IsEmailUsedBefore(cur_email)) {
    std::cout << "Email used before.\n";
    return false;
  }
  User user(GenerateId(), username, cur_email, password, is_accepting_anonymous);
  std::ofstream fout(KDataPath, std::ios::out | std::ios::app);
  assert(!fout.fail());
  fout << user;
  fout.close();
  data.push_back(user);
  return true;
}
