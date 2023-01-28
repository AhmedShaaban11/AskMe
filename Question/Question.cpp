#include "Question.h"
#include "../GeneralFunctions/general_functions.h"

Question::Question(const string &line, const string &delimiter) {
  vector<string> entries = LineToWords(line, delimiter);
  id_ = stoi(entries[0]);
  from_id_ = stoi(entries[1]);
  to_id_ = stoi(entries[2]);
  qn_ = entries[3];
  ans_ = entries[4];
}

bool Question::IsAnsEmpty() const {
  return ans_.empty();
}

int Question::GetId() const {
  return id_;
}

void Question::SetAns(const string &ans) {
  ans_ = ans;
}
