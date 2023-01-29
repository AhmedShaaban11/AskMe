#include "QuesManager.h"
#include "../Question/Question.h"
#include "../GeneralFunctions/general_functions.h"

QuesManager::QuesManager() {
  Update();
}

QuesManager::~QuesManager() {
  Clear();
}

void QuesManager::Update() {
  Clear();
  vector<string> lines = FileToLines(KQuesSrcPath);
  for (const string &line : lines) {
    Question qn(line);
    ques_.insert({qn.GetId(), qn});
    Question *ptr_qn = &ques_[qn.GetId()];
    ques_from_.insert({qn.GetFrom(), ptr_qn});
    ques_to_.insert({qn.GetTo(), ptr_qn});
  }
  last_id_ = (int) ques_.size();
}

void QuesManager::Save() const {
  ofstream fout(KQuesSrcPath);
  for (const auto &p : ques_) {
    fout << p.second.ToString() << "\n";
  }
  fout.close();
}

void QuesManager::Clear() {
  last_id_ = 0;
  ques_.clear();
  ques_from_.clear();
  ques_to_.clear();
}

void QuesManager::AddQn(const string &from, const string &to) {
  string text = GetTxtTillDel(cin, "\n");
  Question qn(last_id_, from, to, text);
  Update();
  ques_.insert({last_id_, qn});
  Question *ptr_qn = &ques_[last_id_];
  ques_from_.insert({from, ptr_qn});
  ques_to_.insert({to, ptr_qn});
  ++last_id_;
  Save();
}

bool QuesManager::IsQnFound(int id) {
  return ques_.find(id) != ques_.end();
}

bool QuesManager::AnsQn(const string &username, int id) {
  Update();
  if (!IsQnFound(id)) {
    cout << "Error! Question isn't found\n";
    return false;
  } else if (ques_[id].GetTo() != username) {
    cout << "Error! Question doesn't belong to you\n";
    return false;
  }
  string text = GetTxtTillDel();
  Update();
  ques_[id].SetAns(text);
  Save();
  return true;
}

vector<Question*> QuesManager::GetQuesFrom(const string &username) {
  vector<Question*> res;
  auto it = ques_from_.find(username);
  for (; it != ques_from_.end(); ++it) {
    if (it->first != username) { break; }
    res.push_back(it->second);
  }
  return res;
}

vector<Question*> QuesManager::GetQuesTo(const string &username) {
  vector<Question*> res;
  auto it = ques_to_.find(username);
  for (; it != ques_to_.end(); ++it) {
    if (it->first != username) { break; }
    res.push_back(it->second);
  }
  return res;
}
