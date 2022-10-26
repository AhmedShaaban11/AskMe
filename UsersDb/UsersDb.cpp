//
// Created by ahmed on 10/17/2022.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include "UsersDb.h"
#include "../User/User.h"

const char KDataPath[] = "../data/users_data.txt";

std::vector<User> users_data;

int UsersDb::GenerateId() {
  return (int) users_data.size();
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
  for (const User &user : users_data) {
    if (user.username_ == username) { return true; }
  }
  return false;
}

bool UsersDb::IsEmailUsedBefore(const std::string &email) {
  LoadData();
  for (const User &user : users_data) {
    if (user.email_ == email) { return true; }
  }
  return false;
}

bool UsersDb::IsIdOutOfRange(const int &id) {
  return (id >= (int) users_data.size());
}

bool UsersDb::IsIdExist(const int &id) {
  if (IsIdOutOfRange(id)) {
    return false;
  }
  return true;
}

bool UsersDb::IsAcceptingAnonymous(const int &id) {
  if (!IsIdExist(id)) { return false; }
  return users_data[id].is_accepting_anonymous_;
}

void UsersDb::LoadData() {
  std::ifstream fin(KDataPath, std::ios::in);
  assert(!fin.fail());
  users_data.clear();
  while (fin.peek() != EOF) {
    User user;
    fin >> user;
    users_data.push_back(user);
  }
  fin.close();
}

void UsersDb::SaveData() {
  std::ofstream fout(KDataPath, std::ios::out);
  assert(!fout.fail());
  for (const User &user : users_data) {
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
  users_data.push_back(user);
  return true;
}

void UsersDb::ListUsersSystem() {
  LoadData();
  std::cout.fill('-');
  for (const User &user : users_data) {
    std::cout << "ID: ";
    std::cout.width(20);
    std::cout << std::left << user.id_;
    std::cout << "Username: " << user.username_ << '\n';
  }
  std::cout.fill(' ');
}

void UsersDb::AddFromQuestion(const int &user_id, const int &que_id) {
  LoadData();
  users_data[user_id].ques_from_.push_back(que_id);
  SaveData();
}

void UsersDb::AddToQuestion(const int &user_id, const int &que_id) {
  LoadData();
  users_data[user_id].ques_to_.push_back(que_id);
  SaveData();
}

void UsersDb::DeleteFromQuestion(const int &que_id, const int &from_id) {
  LoadData();
  std::vector<int> *ques_from = &users_data[from_id].ques_from_;
  auto it = std::find(ques_from->begin(), ques_from->end(), que_id);
  ques_from->erase(it);
  SaveData();
}

void UsersDb::DeleteToQuestion(const int &que_id, const int &to_id) {
  LoadData();
  std::vector<int> *ques_to = &users_data[to_id].ques_to_;
  auto it = std::find(ques_to->begin(), ques_to->end(), que_id);
  ques_to->erase(it);
  SaveData();
}

int UsersDb::IsUsernameAndPasswordExist(const std::string &username,
                                         const std::string &password) {
  LoadData();
  for (const User &user : users_data) {
    if (user.username_ == username && user.password_ == password) {
      return user.id_;
    }
  }
  return -1;
}

User UsersDb::LoadUser(const int &id) {
  LoadData();
  if (!IsIdExist(id)) { return User{}; }
  return users_data[id];
}
