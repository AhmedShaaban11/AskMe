#ifndef ASKME_PROGRAM_PROGRAM_H
#define ASKME_PROGRAM_PROGRAM_H

#include "../QuesManager/QuesManager.h"
#include "../UsersManager/UsersManager.h"

class Program {
 private:
  string usr;
  UsersManager users;
  QuesManager ques;
  vector<string> sign_menu_;
  vector<string> features_menu_;
  void AskProcess();
 public:
  Program();
  ~Program();
  void PrintSignMenu() const;
  void PrintFeaturesMenu() const;
  bool IsUserIn() const;
  void LogOut();
  bool ContinueRun() const;
  bool Run();
};

#endif