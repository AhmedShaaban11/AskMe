#include "Program.h"
#include "../GeneralFunctions/general_functions.h"
#include "../Question/Question.h"
#include "../User/User.h"

Program::Program() : is_user_in{false} {
  usr = nullptr;
}

Program::~Program() {
  usr = nullptr;
}

void Program::PrintSignMenu() const {
  vector<string> vec = {"SignUp", "LogIn", "Exit"};
  for (int i = 0; i < (int) vec.size(); ++i) {
    cout << i << " - " << vec[i] << "\n";
  }
  cout << KBigSeparator;
}

void Program::PrintMenu() const {
  vector<string> vec = {
      "Ask",
      "Answer",
      "Print Questions From Me",
      "Print Question To Me",
      "Print Available Users",
      "LogOut"
  };
  for (int i = 0; i < (int) vec.size(); ++i) {
    cout << i << " - " << vec[i] << "\n";
  }
  cout << KBigSeparator;
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
  cout << KBigSeparator;
  return c;
}

bool Program::Run() {
  if (!is_user_in) {
    PrintSignMenu();
    int c = GetChoice(0, 2);
    if (c == 0) {
      users.AddUser();
    } else if (c == 1) {
      usr = users.AccessUser();
      if (usr) {
        is_user_in = true;
      }
    } else {
      return false;
    }
  } else {
    PrintMenu();
    int c = GetChoice(0, 5);
    if (c == 0) {
      string to_usr;
      cout << "Enter Receiver Username:\n";
      getline(cin, to_usr);
      if (!users.IsUserFound(to_usr)) {
        cout << "Error! User not found\n";
      } else {
        ques.AddQn(usr->GetUsername(), to_usr);
      }
    } else if (c == 1) {
      cout << "Enter Question ID:\n";
      int id = GetChoice(0, INT_MAX);
      ques.AnsQn(usr->GetUsername(), id);
    } else if (c == 2) {
      for (const Question* const &qn : ques.GetQuesFrom(usr->GetUsername())) {
        qn->Print();
      }
    } else if (c == 3) {
      for (const Question* const &qn : ques.GetQuesTo(usr->GetUsername())) {
        qn->Print();
      }
    } else {
      usr = nullptr;
      is_user_in = false;
    }
  }
  cout << KBigSeparator;
  return true;
}
