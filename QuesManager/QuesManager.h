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
using std::set;

class Question;

const char KQuesSrcPath[] = "../QuesManager/ques_data.csv";

class QuesManager {
 private:
  int last_id_;
  map<int, Question> ques_;
  map<int, set<int>> threads_;
  void DeleteThreads(int parent_id);
  void DeleteQuesFrom(const string &username);
  void DeleteQuesTo(const string &username);
  bool InsertQn(int parent_id, bool is_from_anonymous,
                const string &from, const string &to);
 public:
  QuesManager();
  ~QuesManager();
  void Update();
  void Save() const;
  void Clear();
  bool AddQn(bool is_from_anonymous, const string &from, const string &to = "");
  bool AnsQn(const string &username, int id);
  string GetToUsr(int id) const;
  void PrintQuesFrom(const string &username) const;
  void PrintQuesTo(const string &username) const;
  bool IsQnFound(int id) const;
  bool DeleteQn(int id, const string &username);
  void DeleteAllQues(const string &username);
};

#endif