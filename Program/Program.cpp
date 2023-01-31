#include "Program.h"
#include "../GeneralFunctions/general_functions.h"
#include "../Question/Question.h"
#include "../User/User.h"

Program::Program() : is_user_in{false} {

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

int Program::GetChoice(int begin, int end) const {
  cout << "Enter a number from " << begin << " to " << end << " :\n";
  int c;
  cin >> c;
  while (cin.fail() || c < begin || c > end) {
    cout << "Error! Invalid value\n";
    cout << "Enter a number from " << begin << " to " << end << " :\n";
    cin.clear();
    cin.sync();
    cin >> c;
  }
  cin.sync();
  gpm::PrintSeparator('=');
  return c;
}

void Program::LogOut() {
  usr.clear();
  is_user_in = false;
}

bool Program::Run() {
  if (!is_user_in) {
    PrintSignMenu();
    int c = GetChoice(0, 2);
    if (c == 0) {
      users.AddUser();
    } else if (c == 1) {
      usr = users.AccessUser();
      if (!usr.empty()) { is_user_in = true; }
    } else {
      return false;
    }
  } else {
    PrintMenu();
    int c = GetChoice(0, 7);
    if (c == 0) {
      string to_usr;
      bool is_thread = gpm::YesOrNoQn("Thread Question?");
      if (!is_thread) {
        cout << "Enter Receiver Username:\n";
        getline(cin, to_usr);
      }
      bool is_anonymous = gpm::YesOrNoQn("Anonymous Question?");
      if (!is_thread && !users.IsUserFound(to_usr)) {
        cout << "Error! User " << to_usr << " not found.\n";
      } else if (is_anonymous && !users.IsUserAcceptingAnonymous(to_usr)) {
        cout << "Error! " << to_usr << " doesn't accepting anonymous questions.\n";
      } else {
        ques.AddQn(is_anonymous, usr, to_usr);
      }
    } else if (c == 1) {
      cout << "Enter Question ID:\n";
      int id = GetChoice(0, INT_MAX);
      ques.AnsQn(usr, id);
    } else if (c == 2) {
      ques.PrintQuesFrom(usr);
    } else if (c == 3) {
      ques.PrintQuesTo(usr);
    } else if (c == 4) {
      users.PrintUsers();
    } else if (c == 5) {
      cout << "Enter Question ID:\n";
      int id = GetChoice(0, INT_MAX);
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
  gpm::PrintSeparator('=');
  return true;
}
