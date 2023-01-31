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
    if (qn.GetParentId() != -1) {
      threads_[qn.GetParentId()].insert(qn.GetId());
    }
    last_id_ = qn.GetId() + 1;
  }
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
  threads_.clear();
}

bool QuesManager::InsertQn(const string &from, const string &to,
                           bool is_from_anonymous, int parent_id) {
  if (from == to) {
    cout << "Error! Sender cannot be the Receiver.\n";
    return false;
  }
  string txt = GetTxtTillDel(cin, "\n");
  Question qn(last_id_, parent_id, is_from_anonymous, from, to, txt);
  Update();
  ques_.insert({last_id_, qn});
  Question *ptr_qn = &ques_[last_id_];
  ques_from_.insert({from, ptr_qn});
  ques_to_.insert({to, ptr_qn});
  if (parent_id != -1) {
    threads_[parent_id].insert(last_id_);
  }
  ++last_id_;
  Save();
  return true;
}

bool QuesManager::AddTh(const string &from, int parent_id,
                        bool is_from_anonymous) {
  Update();
  if (ques_.find(parent_id) == ques_.end()) {
    cout << "Error! Parent Question (" << parent_id << ") isn't found.\n";
    return false;
  } else if (ques_[parent_id].IsAnsEmpty()) {
    cout << "Error! Parent Question (" << parent_id << ") isn't answered yet.\n";
    return false;
  }
  return InsertQn(from, ques_[parent_id].GetTo(), is_from_anonymous, parent_id);
}

bool QuesManager::AddQn(const string &from, const string &to,
                        bool is_from_anonymous) {
  return InsertQn(from, to, is_from_anonymous);
}

bool QuesManager::IsQnFound(int id) const {
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

string QuesManager::GetToUsr(int id) const {
  if (!IsQnFound(id)) {
    cout << "Error! Question isn't found\n";
    return {};
  }
  return ques_.find(id)->second.GetTo();
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

bool QuesManager::DeleteQn(int id, const string &username) {
  Update();
  if (!IsQnFound(id)) {
    cout << "Error! Question isn't found.\n";
    return false;
  } else if (username != ques_[id].GetFrom() || username != ques_[id].GetTo()) {
    cout << "Error! Question doesn't belong to you.\n";
    return false;
  }
  DeleteThreads(id);
  ques_.erase(id);
  Save();
  return true;
}

void QuesManager::DeleteThreads(int parent_id) {
  for (auto &th : threads_[parent_id]) {
    DeleteThreads(th);
    ques_.erase(th);
  }
}

void QuesManager::DeleteQuesFrom(const string &username) {
  Update();
  auto it = ques_from_.begin();
  while ((it = ques_from_.find(username)) != ques_from_.end()) {
    DeleteThreads(it->second->GetId());
    ques_.erase(it->second->GetId());
    ques_from_.erase(it);
  }
  Save();
}

void QuesManager::DeleteQuesTo(const string &username) {
  Update();
  auto it = ques_to_.begin();
  while ((it = ques_to_.find(username)) != ques_to_.end()) {
    DeleteThreads(it->second->GetId());
    ques_.erase(it->second->GetId());
    ques_to_.erase(it);
  }
  Save();
}
