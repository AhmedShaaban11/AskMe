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
  bool InsertQn(const string &from, const string &to,
                bool is_from_anonymous = false, int parent_id = -1);
  void DeleteThreads(int parent_id);
  void DeleteQuesFrom(const string &username);
  void DeleteQuesTo(const string &username);
 public:
  QuesManager();
  ~QuesManager();
  void Update();
  void Save() const;
  void Clear();
  bool AddQn(const string &from, const string &to, bool is_from_anonymous = false);
  bool AddTh(const string &from, int parent_id, bool is_from_anonymous = false);
  bool AnsQn(const string &username, int id);
  string GetToUsr(int id) const;
  void PrintQuesFrom(const string &username) const;
  void PrintQuesTo(const string &username) const;
  bool IsQnFound(int id) const;
  bool DeleteQn(int id, const string &username);
  void DeleteAllQues(const string &username);
};

#endif