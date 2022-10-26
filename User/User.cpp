//
// Created by ahmed on 10/20/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "User.h"
#include "../UsersDb/UsersDb.h"
#include "../QuesDb/QuesDb.h"

User::User() : id_(-1), username_(""), email_(""), password_(""),
    is_accepting_anonymous_(false) { }

User::User(const int &id, const std::string &username, const std::string &email,
           const std::string &password, const bool &is_accepting_anonymous)
           : id_(id), username_(username), email_(email), password_(password),
           is_accepting_anonymous_(is_accepting_anonymous) {  }

std::ofstream& operator<<(std::ofstream &fout, const User &user) {
  fout << user.id_ << ' ' << user.username_ << ' ' << user.email_ << ' '
       << user.password_ << ' ' << user.is_accepting_anonymous_ << '\n';
  for (const int &qu : user.ques_from_) {
    fout << qu << ' ';
  }
  fout << '\n';
  for (const int &qu : user.ques_to_) {
    fout << qu << ' ';
  }
  fout << '\n';
  return fout;
}

std::ifstream& operator>>(std::ifstream &fin, User &user) {
  fin >> user.id_ >> user.username_ >> user.email_ >> user.password_
      >> user.is_accepting_anonymous_;
  fin.ignore(); // Ignores \n at the end
  int qu;
  std::string holder;
  std::stringstream ss;
  // Getting questions from this user
  getline(fin, holder);
  ss << holder;
  while (ss >> qu) { user.ques_from_.push_back(qu); }
  ss.clear();
  // Getting questions to this user
  getline(fin, holder);
  ss << holder;
  while (ss >> qu) { user.ques_to_.push_back(qu); }
  ss.clear();
  return fin;
}

bool User::Ask(const int &to_id, const std::string &question,
               const bool &is_anonymous, const int &parent_id) {
  UsersDb::LoadData();
  if (!UsersDb::IsIdExist(to_id)) {
    std::cout << "User (" << to_id << ") does not exist.\n";
    return false;
  } else if (is_anonymous && !UsersDb::IsAcceptingAnonymous(to_id)) {
    std::cout << "User (" << to_id << ") does not accept anonymous.\n";
    return false;
  }
  int from_id;
  if (is_anonymous) {
    from_id = -1;
  } else {
    from_id = id_;
  }
  int que_id = QuesDb::AddQuestion(parent_id, from_id, to_id, question);
  if (que_id == -1) { return false; }
  ques_from_.push_back(que_id);
  UsersDb::AddFromQuestion(id_, que_id);
  UsersDb::AddToQuestion(to_id, que_id);
  return true;
}

bool User::Answer(const int &que_id, const std::string &answer) const {
  return QuesDb::AnswerQuestion(que_id, id_, answer);
}

bool User::DeleteQuestion(const int &que_id) {
  auto it = std::find(ques_from_.begin(), ques_from_.end(), que_id);
  if (it == ques_from_.end()) { return false; }
  ques_from_.erase(it);
  int to_id = QuesDb::GetToUser(que_id, id_);
  bool is_deleted = QuesDb::DeleteQuestion(que_id);
  if (!is_deleted) { return false; }
  UsersDb::DeleteFromQuestion(que_id, id_);
  UsersDb::DeleteToQuestion(que_id, to_id);
  return true;
}

void User::PrintQuestionsFrom() const {
  QuesDb::PrintQuestions(ques_from_);
}

void User::PrintQuestionsTo() const {
  QuesDb::PrintQuestions(ques_to_);
}
