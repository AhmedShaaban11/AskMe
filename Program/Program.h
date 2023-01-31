#ifndef ASKME_PROGRAM_PROGRAM_H
#define ASKME_PROGRAM_PROGRAM_H

#include "../QuesManager/QuesManager.h"
#include "../UsersManager/UsersManager.h"

class Program {
 private:
  string usr;
  UsersManager users;
  QuesManager ques;
 public:
  Program();
  ~Program();
  void PrintSignMenu() const;
  void PrintMenu() const;
  bool IsUserIn() const;
  void LogOut();
  bool ContinueRun() const;
  bool Run();
};

#endif