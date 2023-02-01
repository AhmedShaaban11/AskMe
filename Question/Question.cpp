#include "Question.h"
#include "../GeneralFunctions/general_functions.h"

Question::Question() {

}

Question::Question(const string &line, const string &del) {
  vector<string> entries = gpm::LineToWords(line, del);
  id_ = std::stoi(entries[0]);
  parent_id_ = std::stoi(entries[1]);
  is_from_anonymous_ = (bool) std::stoi(entries[2]);
  from_ = entries[3];
  to_ = entries[4];
  qn_ = entries[5];
  ans_ = entries[6];
}

Question::Question(int id, int parent_id, bool is_from_anonymous,
                   const string &from, const string &to, const string &text)
    : id_{id}, parent_id_{parent_id}, is_from_anonymous_{is_from_anonymous},
    from_{from}, to_{to}, qn_{text} {

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

bool Question::IsFromAnonymous() const {
  return is_from_anonymous_;
}

string Question::GetFrom() const {
  return from_;
}

string Question::GetTo() const {
  return to_;
}

string Question::ToString(const string &del) const {
  return gpm::ToString(del, std::to_string(id_), std::to_string(parent_id_),
                       std::to_string(is_from_anonymous_), from_, to_, qn_,
                       ans_);
}

void Question::SetAns(const string &ans) {
  ans_ = ans;
}

void Question::Print() const {
  cout << "ID: " << id_ << "\n";
  cout << "Parent ID: " << (parent_id_ == -1 ? "None" : std::to_string(parent_id_)) << "\n";
  cout << "From: " << (is_from_anonymous_ ? "Anonymous" : from_) << "\n";
  cout << "To: " << to_ << "\n";
  cout << "Question:\n" << qn_ << "\n";
  if (ans_.empty()) {
    cout << "Not Answered Yet!\n";
  } else {
    cout << "Answer:\n" << ans_ << "\n";
  }
}
