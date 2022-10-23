//
// Created by ahmed on 10/22/2022.
//

#include <fstream>
#include <sstream>
#include "Question.h"

Question::Question() : id_(-1), parent_id_(-1), from_id_(-1), to_id_(-1) { }

Question::Question(const int &id, const int &parent_id,const int &from_id,
                   const int &to_id, const std::string &question)
                   : id_(id), parent_id_(parent_id),
                   from_id_(from_id), to_id_(to_id), question_(question) { }

Question::~Question() { threads_.clear(); }

std::ofstream& operator<<(std::ofstream &fout, const Question &que) {
  fout << que.id_ << ' ' << que.parent_id_ << ' '
      << que.from_id_ << ' ' << que.to_id_ << '\n';
  fout << que.question_ << '\n';
  fout << que.answer_ << '\n';
  for (const int &qu : que.threads_) {
    fout << qu << ' ';
  }
  fout << '\n';
  return fout;
}

std::ifstream& operator>>(std::ifstream &fin, Question &que) {
  fin >> que.id_ >> que.parent_id_ >> que.from_id_ >> que.to_id_;
  fin.ignore(); // Ignores \n at the end
  getline(fin, que.question_);
  getline(fin, que.answer_);
  // Getting Threads
  int thread;
  std::string holder;
  std::stringstream ss;
  getline(fin, holder);
  ss << holder;
  while (ss >> thread) { que.threads_.push_back(thread); }
  ss.clear();
  return fin;
}
