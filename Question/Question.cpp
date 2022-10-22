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

std::ofstream& operator<<(std::ofstream &fout, const Question &question) {
  fout << question.id_ << ' ' << question.parent_id_ << ' '
      << question.from_id_ << ' ' << question.to_id_ << ' '
      << question.question_ << ' ' << question.answer_ << '\n';
  for (const int &qu : question.threads_) {
    fout << qu << ' ';
  }
  fout << '\n';
  return fout;
}

std::ifstream& operator>>(std::ifstream &fin, Question &question) {
  fin >> question.id_ >> question.parent_id_ >> question.from_id_
      >> question.to_id_ >> question.question_ >> question.answer_;
  fin.ignore(); // Ignores \n at the end
  // Getting Threads
  int thread;
  std::string holder;
  std::stringstream ss;
  getline(fin, holder);
  ss << holder;
  while (ss >> thread) { question.threads_.push_back(thread); }
  ss.clear();
  return fin;
}
