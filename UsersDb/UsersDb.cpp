//
// Created by ahmed on 10/17/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
#include "UsersDb.h"
#include "../User/User.h"

const char KDataPath[] = "../data/users_data.txt";

std::vector<User> data;

int UsersDb::GenerateId() {
  return (int) data.size() + 1;
}

bool UsersDb::IsUsernameUsedBefore(const std::string &username) {
  LoadData();
  for (const User &user : data) {
    if (user.username == username) { return true; }
  }
  return false;
}

bool UsersDb::IsEmailUsedBefore(const std::string &email) {
  LoadData();
  for (const User &user : data) {
    if (user.email == email) { return true; }
  }
  return false;
}

bool UsersDb::LoadData() {
  if (!data.empty()) { // if data loaded before
    return false;
  }
  std::ifstream fin(KDataPath, std::ios::in);
  assert(fin.fail());
  while (fin.peek() != EOF) {
    User user;
    fin >> user.id >> user.username >> user.email >> user.password
        >> user.is_accepting_anonymous;
    int qu;
    std::string holder;
    std::stringstream ss;
    // Getting questions from this user
    getline(fin, holder);
    ss << holder;
    while (ss >> qu) { user.ques_from.push_back(qu); }
    // Getting questions to this user
    getline(fin, holder);
    ss << holder;
    while (ss >> qu) { user.ques_to.push_back(qu); }
    // Push data
    data.push_back(user);
  }
  fin.close();
  return true;
}

void UsersDb::SaveData() {
  std::ofstream fout(KDataPath, std::ios::out);
  assert(fout.fail());
  for (const User &user : data) {
    fout << user;
  }
  fout.close();
}

bool UsersDb::AddUser(const std::string &username, const std::string &email,
                      const std::string &password,
                      const bool &is_accepting_anonymous) {
  LoadData();
  if (!IsUsernameUsedBefore(username)) {
    std::cout << "Username used before.\n";
    return false;
  } else if (!IsEmailUsedBefore(email)) {
    std::cout << "Email used before.\n";
    return false;
  }
  User user(GenerateId(), username, email, password, is_accepting_anonymous);
  std::ofstream fout(KDataPath, std::ios::out | std::ios::app);
  assert(fout.fail());
  fout << user;
  fout.close();
  data.push_back(user);
  return true;
}