#ifndef ASKME_QUESTION_QUESTION_H
#define ASKME_QUESTION_QUESTION_H

#include <string>

using std::string;

class Question {
 private:
  int id_;
  string from_;
  string to_;
  string qn_;
  string ans_;
 public:
  Question();
  explicit Question(const string &line, const string &del = ",");
  Question(int id, const string &from, const string &to, const string &text);
  bool IsAnsEmpty() const;
  int GetId() const;
  string GetFrom() const;
  string GetTo() const;
  string ToString(const string &del = ",") const;
  void SetAns(const string &ans);
};

#endif