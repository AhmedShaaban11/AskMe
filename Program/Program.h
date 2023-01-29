#ifndef ASKME_PROGRAM_PROGRAM_H
#define ASKME_PROGRAM_PROGRAM_H

#include "../QuesManager/QuesManager.h"
#include "../UsersManager/UsersManager.h"

const char KBigSeparator[] = "==============================\n";

class Program {
 private:
  User *usr;
  UsersManager users;
  QuesManager ques;
  bool is_user_in;
 public:
  Program();
  ~Program();
  void PrintSignMenu() const;
  void PrintMenu() const;
  int GetChoice(int begin, int end) const;
  bool Run();
};

#endif