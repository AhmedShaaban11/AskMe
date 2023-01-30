#include "UsersManager.h"
#include "../User/User.h"
#include "../GeneralFunctions/general_functions.h"
#include "../Question/Question.h"
#include "../QuesManager/QuesManager.h"

UsersManager::UsersManager() {
  Update();
}

UsersManager::~UsersManager() {
  Clear();
}

void UsersManager::Update() {
  Clear();
  vector<string> lines = FileToLines(KUsersSrcPath);
  QuesManager ques;
  for (const string &line : lines) {
    User usr(line);
    users_.insert({usr.GetUsername(), usr});
    emails_.insert(usr.GetEmail());
  }
}

void UsersManager::Clear() {
  users_.clear();
  emails_.clear();
}

void UsersManager::Save() const {
  ofstream fout(KUsersSrcPath);
  for (const auto &p : users_) {
    fout << p.second.ToString() << "\n";
  }
  fout.close();
}

bool UsersManager::IsUserFound(const string &username) {
  return users_.find(username) != users_.end();
}

bool UsersManager::IsEmailFound(const string &email) {
  return emails_.find(email) != emails_.end();
}

User* UsersManager::AccessUser() {
  string username, pass;
  cout << "Username:\n";
  getline(cin, username);
  cout << "Password:\n";
  getline(cin, pass);
  Update();
  if (!IsUserFound(username)) {
    cout << "Error! Username isn't found\n";
    return nullptr;
  }
  if (users_[username].GetPassword() != pass) {
    cout << "Error! Password isn't correct\n";
    return nullptr;
  }
  return &users_[username];
}

void UsersManager::AddUser() {
  string username, email, pass;
  cout << "Username:\n";
  getline(cin, username);
  cout << "Email:\n";
  getline(cin, email);
  cout << "Password:\n";
  getline(cin, pass);
  Update();
  if (IsUserFound(username)) {
    cout << "Error! Username used before\n";
    return;
  }
  if (IsEmailFound(email)) {
    cout << "Error! Email used before\n";
    return;
  }
  User usr(username, email, pass);
  users_.insert({username, usr});
  Save();
}

bool UsersManager::DeleteUser(const string &username) {
  Update();
  if (!IsUserFound(username)) {
    cout << "Error! Username isn't found\n";
    return false;
  }
  cout << "Enter your Password:\n";
  string pass;
  getline(cin, pass);
  User *usr = &users_[username];
  if (usr->GetPassword() != pass) {
    cout << "Error! Password isn't correct\n";
    return false;
  }
  Update();
  emails_.erase(usr->GetEmail());
  users_.erase(username);
  usr = nullptr;
  Save();
  return true;
}

void UsersManager::PrintUsers() const {
  for (const auto &p : users_) {
    cout << p.first << '\n';
  }
}