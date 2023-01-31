#include "Program.h"
#include "../GeneralFunctions/general_functions.h"
#include "../Question/Question.h"
#include "../User/User.h"

Program::Program() {

}

Program::~Program() {

}

void Program::PrintSignMenu() const {
  vector<string> vec = {"SignUp", "LogIn", "Exit"};
  for (int i = 0; i < (int) vec.size(); ++i) {
    cout << i << " - " << vec[i] << "\n";
  }
  gpm::PrintSeparator('=');
}

void Program::PrintMenu() const {
  vector<string> vec = {
      "Ask",
      "Answer",
      "Print Questions From Me",
      "Print Question To Me",
      "Print Available Users",
      "Delete Question",
      "Delete your Account",
      "LogOut"
  };
  for (int i = 0; i < (int) vec.size(); ++i) {
    cout << i << " - " << vec[i] << "\n";
  }
  gpm::PrintSeparator('=');
}

bool Program::IsUserIn() const {
  return !usr.empty();
}

void Program::LogOut() {
  usr.clear();
}

bool Program::ContinueRun() const {
  gpm::PrintSeparator('=');
  return true;
}

bool Program::Run() {
  if (!IsUserIn()) {
    PrintSignMenu();
    int c = gpm::InputInt("Enter a number:", 0, 2);
    if (c == 0) {
      users.AddUser();
    } else if (c == 1) {
      usr = users.AccessUser();
    } else {
      return false;
    }
  } else {
    PrintMenu();
    int c = gpm::InputInt("Enter a number:", 0, 7);
    if (c == 0) {
      int parent_id = -1;
      string to_usr;
      bool is_thread = gpm::YesOrNoQn("Thread Question?");
      if (is_thread) {
        parent_id = gpm::InputInt("Enter Parent Question ID:", 0);
        if (!ques.IsQnFound(parent_id)) {
          cout << "Error! Question (" << parent_id << ") isn't found.\n";
          return ContinueRun();
        }
        to_usr = ques.GetToUsr(parent_id);
      } else {
        to_usr = gpm::InputString("Enter Receiver Username:");
        if (!users.IsUserFound(to_usr)) {
          cout << "Error! User " << to_usr << " not found.\n";
          return ContinueRun();
        }
      }
      bool is_anonymous = gpm::YesOrNoQn("Anonymous Question?");
      if (is_anonymous && !users.IsUserAcceptingAnonymous(to_usr)) {
        cout << "Error! " << to_usr << " doesn't accepting anonymous questions.\n";
        return ContinueRun();
      }
      ques.AddQn(parent_id, is_anonymous, usr, to_usr);
    } else if (c == 1) {
      int id = gpm::InputInt("Enter Question ID:", 0);
      ques.AnsQn(usr, id);
    } else if (c == 2) {
      ques.PrintQuesFrom(usr);
    } else if (c == 3) {
      ques.PrintQuesTo(usr);
    } else if (c == 4) {
      users.PrintUsers();
    } else if (c == 5) {
      int id = gpm::InputInt("Enter Question ID:", 0);
      ques.DeleteQn(id, usr);
    } else if (c == 6) {
      string s;
      bool is_sure = gpm::YesOrNoQn("Are you sure?");
      if (is_sure && users.DeleteUser(usr)) {
        ques.DeleteAllQues(usr);
        LogOut();
      }
    } else {
      LogOut();
    }
  }
  return ContinueRun();
}
