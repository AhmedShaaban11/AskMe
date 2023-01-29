#ifndef ASKME_QUESMANAGER_QUESMANAGER_H
#define ASKME_QUESMANAGER_QUESMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::map;
using std::string;
using std::vector;
using std::ofstream;
using std::cin;
using std::cout;
using std::multimap;

class Question;

const char KQuesSrcPath[] = "../QuesManager/ques_data.csv";

class QuesManager {
 private:
  int last_id_;
  map<int, Question> ques_;
  multimap<string, Question*> ques_from_;
  multimap<string, Question*> ques_to_;
 public:
  QuesManager();
  ~QuesManager();
  void Update();
  void Save() const;
  void Clear();
  void AddQn(const string &from, const string &to);
  bool AnsQn(const string &username, int id);
  vector<Question*> GetQuesFrom(const string &username);
  vector<Question*> GetQuesTo(const string &username);
  bool IsQnFound(int id);
};

#endif