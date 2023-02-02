#include <iostream>
#include "Program/Program.h"

const char KQuesSrcPath[] = "QuesManager/ques_data.csv";
const char KUsersSrcPath[]= "UsersManager/users_data.csv";

int main() {
  Program app(KUsersSrcPath, KQuesSrcPath);
  while (app.Run()) { }
  return 0;
}
