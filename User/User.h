// 24 Jan 2023
#ifndef ASKME_USER_USER_H
#define ASKME_USER_USER_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::map;
using std::vector;

class Question;

class User {
 private:
  string id_;
  string username_;
  string email_;
  string password_;
  map<int, Question*> from_ques_;
  map<int, Question*> to_ques_;
 public:
  void FillWithLine(const string &line, const string &delimiter = " ");
  void FillFromQues(vector<Question*> &vec);
  void FillToQues(vector<Question*> &vec);
  bool HasToQn(int n);
  bool HasFromQn(int n);
};

#endif