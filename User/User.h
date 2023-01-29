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
  string username_;
  string email_;
  string password_;
  map<int, Question*> from_ques_;
  map<int, Question*> to_ques_;
 public:
  User();
  User(const string &username, const string &email, const string &password);
  explicit User(const string &line, const string &delimiter = ",");
  void FillFromQues(vector<Question*> &vec);
  void FillToQues(vector<Question*> &vec);
  void AddFromQn(int id, Question *qn);
  void AddToQn(int id, Question *qn);
  bool HasToQn(int id);
  bool HasFromQn(int id);
  string GetUsername() const;
  string GetEmail() const;
  string GetPassword() const;
  string ToString(const string &del = ",") const;
};

#endif