//
// Created by ahmed on 10/20/2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cassert>
#include "QuesDb.h"
#include "../Question/Question.h"

const char KDataPath[] = "../data/ques_data.txt";

std::vector<Question> ques_data;
std::queue<int> deleted_ques;

int QuesDb::GenerateId() {
  return (int) ques_data.size();
}

bool QuesDb::IsIdOutOfRange(const int &id) {
  return (id >= (int) ques_data.size());
}

bool QuesDb::IsDeletedQuestion(const int &id) {
  return (ques_data[id].id_ == -1);
}

bool QuesDb::LoadData() {
  if (!ques_data.empty()) { // if ques_data loaded before
    return false;
  }
  std::ifstream fin(KDataPath, std::ios::in);
  assert(!fin.fail());
  while (fin.peek() != EOF) {
    Question que;
    fin >> que;
    ques_data.push_back(que);
  }
  fin.close();
  return true;
}

void QuesDb::SaveData() {
  std::ofstream fout(KDataPath, std::ios::out);
  assert(!fout.fail());
  for (const Question &que : ques_data) {
    fout << que;
  }
  fout.close();
}

void QuesDb::AddThreadToParent(const int &thread_id, const int &parent_id) {
  ques_data[parent_id].threads_.push_back(thread_id);
  SaveData();
}

void QuesDb::AddQuestion(const int &parent_id, const int &from_id,
                         const int &to_id, const std::string &question) {
  LoadData();
  std::ofstream fout(KDataPath, std::ios::out | std::ios::app);
  assert(!fout.fail());
  Question que(GenerateId(), parent_id, from_id, to_id, question);
  fout << que;
  ques_data.push_back(que);
  fout.close();
  if (parent_id != -1) { // If thread
    AddThreadToParent(que.id_, parent_id);
  }
}

bool QuesDb::AnswerQuestion(const int &id, const int &to_user_id,
                            const std::string &ans) {
  LoadData();
  if (IsIdOutOfRange(id)) {
    std::cout << "Question (" << id << ") does not exist.\n";
    return false;
  } else if (IsDeletedQuestion(id)) {
    std::cout << "Question (" << id << ") was Deleted.\n";
    return false;
  } else if (ques_data[id].to_id_ != to_user_id) {
    std::cout << "Question (" << id << ") does not belong to you.\n";
    return false;
  }
  ques_data[id].answer_ = ans;
  SaveData();
  return true;
}

bool QuesDb::DeleteQuestion(const int &id, const int &from_id) {
  LoadData();
  if (IsIdOutOfRange(id)) {
    std::cout << "Question (" << id << ") does not exist.\n";
    return false;
  } else if (IsDeletedQuestion(id)) {
    std::cout << "Question (" << id << ") was Deleted.\n";
    return false;
  } else if (ques_data[id].from_id_ != from_id) {
    std::cout << "Question (" << id << ") does not belong to you.\n";
    return false;
  }
  Question que;
  ques_data[id] = que;
  deleted_ques.push(id);
  SaveData();
  return true;
}
