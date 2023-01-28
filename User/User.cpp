// 24 Jan 2023
#include "User.h"
#include "../Question/Question.h"
#include "../GeneralFunctions/general_functions.h"

User::User(const string &username, const string &email, const string &password)
    : username_(username), email_(email), password_(password) {

}

User::User(const string &line, const string &delimiter) {
  vector<string> entries = LineToWords(line, delimiter);
  username_ = entries[0];
  email_ = entries[1];
  password_ = entries[2];
}

void User::FillFromQues(vector<Question*> &vec) {
  for (const auto qn : vec) {
    from_ques_.insert({qn->GetId(), qn});
  }
}

void User::FillToQues(vector<Question*> &vec) {
  for (const auto qn : vec) {
    to_ques_.insert({qn->GetId(), qn});
  }
}

void User::AddFromQn(int id, Question *qn) {
  from_ques_.insert({id, qn});
}

void User::AddToQn(int id, Question *qn) {
  to_ques_.insert({id, qn});
}

bool User::HasFromQn(int id) {
  return from_ques_.find(id) != from_ques_.end();
}

bool User::HasToQn(int id) {
  return to_ques_.find(id) != to_ques_.end();
}

string User::GetUsername() const {
  return username_;
}

string User::GetEmail() const {
  return email_;
}

string User::GetPassword() const {
  return password_;
}

string User::ToString(const string &del) const {
  string res;
  res = username_ + del + email_ + del + password_;
  return res;
}
