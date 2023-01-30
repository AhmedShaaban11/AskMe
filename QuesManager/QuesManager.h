#ifndef ASKME_QUESMANAGER_QUESMANAGER_H
#define ASKME_QUESMANAGER_QUESMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>

using std::map;
using std::string;
using std::vector;
using std::ofstream;
using std::cin;
using std::cout;
using std::multimap;
using std::set;

class Question;

const char KQuesSrcPath[] = "../QuesManager/ques_data.csv";

class QuesManager {
 private:
  int last_id_;
  map<int, Question> ques_;
  multimap<string, Question*> ques_from_;
  multimap<string, Question*> ques_to_;
  map<int, set<int>> threads_;
  bool InsertQn(const string &from, const string &to, int parent_id = -1);
 public:
  QuesManager();
  ~QuesManager();
  void Update();
  void Save() const;
  void Clear();
  bool AddQn(const string &from, const string &to);
  bool AddTh(const string &from, int parent_id);
  bool AnsQn(const string &username, int id);
  vector<Question*> GetQuesFrom(const string &username);
  vector<Question*> GetQuesTo(const string &username);
  bool IsQnFound(int id);
  void DeleteThreads(int parent_id);
  void DeleteQuesFrom(const string &username);
  void DeleteQuesTo(const string &username);
};

#endif