//
// Created by ahmed on 10/17/2022.
//

#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include "UsersDb.h"
#include "../User/User.h"

const char KDataPath[] = "../data/users_data.txt";

std::vector<User> data;

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
