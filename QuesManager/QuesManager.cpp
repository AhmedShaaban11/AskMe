#include "QuesManager.h"
#include "../Question/Question.h"
#include "../GeneralFunctions/general_functions.h"

QuesManager::QuesManager() : last_id_{0} {
  Update();
}

QuesManager::~QuesManager() {
  Clear();
}

void QuesManager::Update() {
  Clear();
  vector<string> lines = gpm::FileToLines(KQuesSrcPath);
  for (const string &line : lines) {
    Question qn(line);
    ques_.insert({qn.GetId(), qn});
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
  threads_.clear();
}

bool QuesManager::InsertQn(int parent_id, bool is_from_anonymous,
                           const string &from, const string &to) {
  if (from == to) {
    cout << "Error! Sender cannot be the Receiver.\n";
    return false;
  }
  string txt = gpm::GetTxtTillDel(cin, "\n");
  Question qn(last_id_, parent_id, is_from_anonymous, from, to, txt);
  Update();
  ques_.insert({last_id_, qn});
  if (parent_id != -1) {
    threads_[parent_id].insert(last_id_);
  }
  ++last_id_;
  Save();
  return true;
}

bool QuesManager::AddQn(int parent_id, bool is_from_anonymous, const string &from, const string &to) {
  Update();
  if (parent_id != -1 && ques_[parent_id].IsAnsEmpty()) {
    cout << "Error! Parent Question (" << parent_id << ") isn't answered yet.\n";
    return false;
  }
  return InsertQn(parent_id, is_from_anonymous, from, to);
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
  } else if (!ques_[id].IsAnsEmpty() &&
      !gpm::YesOrNoQn("Modifying Existing Answer?")) {
    return false;
  }
  string text = gpm::GetTxtTillDel();
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

void QuesManager::PrintQuesFrom(const string &username) const {
  cout << "Questions From " << username << ":\n";
  gpm::PrintSeparator('-', 20);
  for (const auto &p : ques_) {
    if (username != p.second.GetFrom()) { continue; }
    p.second.Print();
    gpm::PrintSeparator('-');
  }
}

void QuesManager::PrintQuesTo(const string &username) const {
  cout << "Questions To " << username << ":\n";
  gpm::PrintSeparator('-', 20);
  for (const auto &p : ques_) {
    if (username != p.second.GetTo()) { continue; }
    p.second.Print();
    gpm::PrintSeparator('-');
  }
}

bool QuesManager::DeleteQn(int id, const string &username) {
  Update();
  if (!IsQnFound(id)) {
    cout << "Error! Question isn't found.\n";
    return false;
  } else if (username != ques_.find(id)->second.GetFrom() &&
      username != ques_.find(id)->second.GetTo()) {
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
  auto prv = ques_.begin();
  for (auto it = ques_.begin(); it != ques_.end();) {
    prv = it++;
    if (username != prv->second.GetFrom()) { continue; }
    DeleteThreads(prv->first);
    ques_.erase(prv);
  }
  Save();
}

void QuesManager::DeleteQuesTo(const string &username) {
  Update();
  auto prv = ques_.begin();
  for (auto it = ques_.begin(); it != ques_.end();) {
    prv = it++;
    if (username != prv->second.GetTo()) { continue; }
    DeleteThreads(prv->first);
    ques_.erase(prv);
  }
  Save();
}

void QuesManager::DeleteAllQues(const string &username) {
  DeleteQuesFrom(username);
  DeleteQuesTo(username);
}
