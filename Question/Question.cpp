#include "Question.h"
#include "../GeneralFunctions/general_functions.h"

Question::Question() {

}

Question::Question(const string &line, const string &del) {
  vector<string> entries = LineToWords(line, del);
  id_ = stoi(entries[0]);
  from_ = entries[1];
  to_ = entries[2];
  qn_ = entries[3];
  ans_ = entries[4];
}

Question::Question(int id, const string &from, const string &to, const string &text)
    : id_{id}, from_{from}, to_{to}, qn_{text} {

}

bool Question::IsAnsEmpty() const {
  return ans_.empty();
}

int Question::GetId() const {
  return id_;
}

string Question::GetFrom() const {
  return from_;
}

string Question::GetTo() const {
  return to_;
}

string Question::ToString(const string &del) const {
  string res;
  res = std::to_string(id_) + del + from_ + del + to_ + del + qn_ + del + ans_;
  return res;
}

void Question::SetAns(const string &ans) {
  ans_ = ans;
}

void Question::Print() const {
  cout << "ID: " << id_ << "\n";
  cout << "From: " << from_ << "\n";
  cout << "To: " << to_ << "\n";
  cout << "Question:\n" << qn_ << "\n";
  if (ans_.empty()) {
    cout << "Not Answered Yet!\n";
  } else {
    cout << "Answer:\n" << ans_ << "\n";
  }
}
