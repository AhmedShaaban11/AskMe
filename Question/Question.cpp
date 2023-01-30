#include "Question.h"
#include "../GeneralFunctions/general_functions.h"

Question::Question() {

}

Question::Question(const string &line, const string &del) {
  vector<string> entries = LineToWords(line, del);
  id_ = stoi(entries[0]);
  parent_id_ = stoi(entries[1]);
  from_ = entries[2];
  to_ = entries[3];
  qn_ = entries[4];
  ans_ = entries[5];
}

Question::Question(int id, int parent_id, const string &from, const string &to,
                   const string &text)
    : id_{id}, parent_id_{parent_id}, from_{from}, to_{to}, qn_{text} {

}

bool Question::IsAnsEmpty() const {
  return ans_.empty();
}

int Question::GetId() const {
  return id_;
}

int Question::GetParentId() const {
  return parent_id_;
}

string Question::GetFrom() const {
  return from_;
}

string Question::GetTo() const {
  return to_;
}

string Question::ToString(const string &del) const {
  string res;
  res = std::to_string(id_) + del + std::to_string(parent_id_)+ del + from_ +
      del + to_ + del + qn_ + del + ans_;
  return res;
}

void Question::SetAns(const string &ans) {
  ans_ = ans;
}

void Question::Print() const {
  cout << "ID: " << id_ << "\n";
  cout << "Parent ID: " << (parent_id_ == -1 ? "None" : std::to_string(parent_id_)) << "\n";
  cout << "From: " << from_ << "\n";
  cout << "To: " << to_ << "\n";
  cout << "Question:\n" << qn_ << "\n";
  if (ans_.empty()) {
    cout << "Not Answered Yet!\n";
  } else {
    cout << "Answer:\n" << ans_ << "\n";
  }
}
