// 24 Jan 2023
#include "User.h"
#include "../Question/Question.h"
#include "../GeneralFunctions/general_functions.h"

User::User(const string &line, const string &delimiter) {
  vector<string> entries = LineToWords(line, delimiter);
  id_ = entries[0];
  username_ = entries[1];
  email_ = entries[2];
  password_ = entries[3];
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

bool User::HasFromQn(int id) {
  return from_ques_.find(id) != from_ques_.end();
}

bool User::HasToQn(int id) {
  return to_ques_.find(id) != to_ques_.end();
}
