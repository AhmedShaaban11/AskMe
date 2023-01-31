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
  vector<string> lines = gpm::FileToLines(KUsersSrcPath);
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

bool UsersManager::IsUserFound(const string &username) const {
  return users_.find(username) != users_.end();
}

bool UsersManager::IsEmailFound(const string &email) const {
  return emails_.find(email) != emails_.end();
}

bool UsersManager::IsUserAcceptingAnonymous(const string &username) const {
  if (!IsUserFound(username)) {
    cout << "Error! User isn't found.\n";
    return false;
  }
  return users_.find(username)->second.IsAcceptingAnonymous();
}

string UsersManager::AccessUser() {
  string username, pass;
  cout << "Username:\n";
  getline(cin, username);
  cout << "Password:\n";
  getline(cin, pass);
  Update();
  if (!IsUserFound(username)) {
    cout << "Error! Username isn't found\n";
    return {};
  }
  if (users_.find(username)->second.GetPassword() != pass) {
    cout << "Error! Password isn't correct\n";
    return {};
  }
  return users_.find(username)->first;
}

void UsersManager::AddUser() {
  string username, email, pass;
  cout << "Username:\n";
  getline(cin, username);
  cout << "Email:\n";
  getline(cin, email);
  cout << "Password:\n";
  getline(cin, pass);
  string a;
  do {
    cout << "Accepting Anonymous? (y/n)\n";
    getline(cin, a);
  } while (a != "y" && a != "n");
  Update();
  if (IsUserFound(username)) {
    cout << "Error! Username used before\n";
    return;
  }
  if (IsEmailFound(email)) {
    cout << "Error! Email used before\n";
    return;
  }
  User usr(username, email, pass, a == "y");
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
  const User *usr = &users_.find(username)->second;
  if (usr->GetPassword() != pass) {
    cout << "Error! Password isn't correct\n";
    return false;
  }
  Update();
  emails_.erase(usr->GetEmail());
  users_.erase(usr->GetUsername());
  usr = nullptr;
  Save();
  return true;
}

void UsersManager::PrintUsers() const {
  cout << "Users:\n";
  cout << "---------\n";
  for (const auto &p : users_) {
    cout << p.first << '\n';
  }
}
