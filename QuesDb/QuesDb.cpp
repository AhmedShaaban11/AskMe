//
// Created by ahmed on 10/20/2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include "QuesDb.h"
#include "../Question/Question.h"

const char KDataPath[] = "../data/ques_data.txt";

std::vector<Question> ques_data;
std::queue<int> deleted_ques;

int QuesDb::GetDbSize() {
  return (int) ques_data.size();
}

int QuesDb::GenerateId() {
  int id;
  if (!deleted_ques.empty()) {
    id = deleted_ques.front();
    deleted_ques.pop();
  } else {
    id = (int) ques_data.size();
  }
  return id;
}

bool QuesDb::IsIdOutOfRange(const int &id) {
  return (id >= (int) ques_data.size());
}

bool QuesDb::IsDeletedQuestion(const int &id) {
  return (ques_data[id].id_ == -1);
}

void QuesDb::LoadData() {
  std::ifstream fin(KDataPath, std::ios::in);
  assert(!fin.fail());
  ques_data.clear();
  std::queue<int> q;
  deleted_ques.swap(q);
  while (fin.peek() != EOF) {
    Question que;
    fin >> que;
    if (que.id_ == -1) { deleted_ques.push(GetDbSize()); }
    ques_data.push_back(que);
  }
  fin.close();
}

void QuesDb::SaveData() {
  std::ofstream fout(KDataPath, std::ios::out);
  assert(!fout.fail());
  for (const Question &que : ques_data) {
    fout << que;
  }
  fout.close();
}

bool QuesDb::IsIdExist(const int &id) {
  if (IsIdOutOfRange(id)) {
    std::cout << "Question (" << id << ") does not exist.\n";
    return false;
  } else if (IsDeletedQuestion(id)) {
    std::cout << "Question (" << id << ") was Deleted.\n";
    return false;
  }
  return true;
}

int QuesDb::AddQuestion(const int &parent_id, const int &from_id,
                         const int &to_id, const std::string &question) {
  LoadData();
  std::ofstream fout(KDataPath, std::ios::out | std::ios::app);
  assert(!fout.fail());
  if (parent_id != -1 && !IsIdExist(parent_id)) {
    return -1;
  } else if (parent_id != -1 && ques_data[parent_id].answer_.empty()) {
      std::cout << "Question (" << parent_id << ") not answered yet.\n";
    return -1;
  }
  int id = GenerateId();
  Question que(id, parent_id, from_id, to_id, question);
  if (IsIdOutOfRange(id)) {
    ques_data.push_back(que);
  } else {
    ques_data[id] = que;
  }
  fout.close();
  if (parent_id != -1) { // If thread
    ques_data[parent_id].threads_.push_back(id);
  }
  SaveData();
  return id;
}

bool QuesDb::AnswerQuestion(const int &id, const int &to_user_id,
                            const std::string &ans) {
  LoadData();
  if (!IsIdExist(id)) {
    return false;
  } else if (ques_data[id].to_id_ != to_user_id) {
    std::cout << "Question (" << id << ") does not belong to you.\n";
    return false;
  }
  ques_data[id].answer_ = ans;
  SaveData();
  return true;
}

void QuesDb::DeleteThreads(const int &id) { // 4 5
  if (ques_data[id].threads_.empty()) {
    return;
  }
  int last_thread_id = ques_data[id].threads_.back();
  DeleteThreads(last_thread_id); // Delete threads of threads
  ques_data[last_thread_id] = Question();
  ques_data[id].threads_.pop_back();
  deleted_ques.push(last_thread_id);
  DeleteThreads(id); // Delete current threads
}

bool QuesDb::DeleteQuestion(const int &id) {
  LoadData();
  if (!IsIdExist(id)) {
    return false;
  }
  int parent_id = ques_data[id].parent_id_;
  // Delete the question (if thread) from its parent question
  if (parent_id != -1) {
    std::vector<int> *parent_threads = &ques_data[parent_id].threads_;
    int id_pos = *find(parent_threads->begin(), parent_threads->end(),
                       parent_id);
    parent_threads->erase(parent_threads->begin() + id_pos);
  }
  DeleteThreads(id);
  ques_data[id] = Question();
  deleted_ques.push(id);
  SaveData();
  return true;
}

bool QuesDb::IsParentQuestion(const int &id) {
  return ((ques_data[id].id_ != -1) && (ques_data[id].parent_id_ == -1));
}

void QuesDb::PrintThreads(const int &id) {
  if (ques_data[id].threads_.empty()) {
    return;
  }
  for (const int &thread_id : ques_data[id].threads_) {
    std::cout << "\tThread (" << thread_id << ") on "
        << (IsParentQuestion(id) ? "question" : "thread") << " ("
        << id << ") from ("
        << ((ques_data[thread_id].from_id_ == -1) ?
           "Anonymous" : std::to_string(ques_data[thread_id].from_id_))
        << ") to (" << ques_data[thread_id].to_id_ << "):\n";
    std::cout << '\t' << ques_data[thread_id].question_ << '\n';
    std::cout << "\tAnswer: " << ques_data[thread_id].answer_ << "\n\n";
    PrintThreads(thread_id);
  }
}

void QuesDb::PrintParentQuestionMessage(const int &id) {
  std::cout << "Question (" << id << ") from ("
            << ((ques_data[id].from_id_ == -1) ?
                "Anonymous" : std::to_string(ques_data[id].from_id_))
            << ") to (" << ques_data[id].to_id_ << "):\n";
  std::cout << ques_data[id].question_ << '\n';
  std::cout << "Answer: " << ques_data[id].answer_ << "\n\n";
}

void QuesDb::PrintFeed(const int &num_of_parent_ques) {
  LoadData();
  int cnt = num_of_parent_ques;
  for (int id = GetDbSize() - 1; id >= 0 && cnt; --id) {
    if (IsParentQuestion(id)) {
      PrintParentQuestionMessage(id);
      PrintThreads(id);
      --cnt;
    }
  }
}

void QuesDb::PrintQuestions(const std::vector<int> &ques) {
  LoadData();
  for (const int &id : ques) {
    PrintParentQuestionMessage(id);
    PrintThreads(id);
  }
}

int QuesDb::GetToUser(const int &que_id, const int &from_user_id) {
  LoadData();
  if (!IsIdExist(que_id)) { return -1; }
  if (ques_data[que_id].from_id_ != from_user_id) { return -1; }
  return ques_data[que_id].to_id_;
}
