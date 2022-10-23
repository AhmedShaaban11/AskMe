//
// Created by ahmed on 10/22/2022.
//

#ifndef ASKME_QUESTION_H
#define ASKME_QUESTION_H

#include <string>
#include <vector>


class Question {
 private:
  int id_;
  int parent_id_;
  int from_id_;
  int to_id_;
  std::string question_;
  std::string answer_;
  std::vector<int> threads_;
  friend std::ofstream& operator<<(std::ofstream &fout, const Question &que);
  friend std::ifstream& operator>>(std::ifstream &fout, Question &que);
  friend class QuesDb;
 public:
  Question();
  Question(const int &id, const int &parent_id, const int &from_id,
           const int &to_id, const std::string &question);
  ~Question();
};


#endif //ASKME_QUESTION_H
