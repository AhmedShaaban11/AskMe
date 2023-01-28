#ifndef ASKME_QUESTION_QUESTION_H
#define ASKME_QUESTION_QUESTION_H

#include <string>

using std::string;

class Question {
 private:
  int id_;
  int from_id_;
  int to_id_;
  string qn_;
  string ans_;
 public:
  explicit Question(const string &line, const string &delimiter = ",");
  bool IsAnsEmpty() const;
  int GetId() const;
  void SetAns(const string &ans);
};

#endif