#include "UsersManager.h"
#include "../User/User.h"
#include "../GeneralFunctions/general_functions.h"
#include "../Question/Question.h"

UsersManager::UsersManager(const string &file_name) : src_file_(file_name) {
  Update();
}

void UsersManager::Update() {
  Clear();
  vector<string> lines = FileToLines(src_file_);
  for (const string &line : lines) {
    User usr(line);
    users.insert({usr.GetUsername(), usr});
    emails.insert(usr.GetEmail());
  }
}

void UsersManager::Clear() {
  users.clear();
  emails.clear();
}

void UsersManager::Save() const {
  std::ofstream fout(src_file_);
  for (const auto &usr : users) {
    fout << usr.second.ToString() << "\n";
  }
  fout.close();
}

bool UsersManager::IsUserFound(const string &username) {
  return users.find(username) != users.end();
}

bool UsersManager::IsEmailFound(const string &email) {
  return emails.find(email) != emails.end();
}

auto UsersManager::Find(const string &username) {
  return users.find(username)->second;
}

bool UsersManager::AddFromQnToUser(int id, Question *qn, const string &username) {
  auto it = Find(username);
  Update();
  it.AddFromQn(id, qn);
  Save();
  return true;
}

bool UsersManager::AddToQnToUser(int id, Question *qn, const string &username) {
  auto it = Find(username);
  Update();
  it.AddToQn(id, qn);
  Save();
  return true;
}

auto UsersManager::AccessUser() {
  string username, pass;
  cout << "Username:";
  getline(cin, username);
  cout << "Password:";
  getline(cin, pass);
  Update();
  if (!IsUserFound(username)) {
    cout << "Error! Username isn't found\n";
  }
  if (Find(username).GetPassword() != pass) {
    cout << "Error! Password isn't correct\n";
  }
  return Find(username);
}

void UsersManager::AddUser() {
  string username, email, pass;
  cout << "Username:";
  getline(cin, username);
  cout << "Email:";
  getline(cin, email);
  cout << "Password:";
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
  users.insert({username, usr});
  Save();
}
