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
      "Delete your Account",
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

void Program::LogOut() {
  usr = nullptr;
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
      if (usr) {
        is_user_in = true;
      }
    } else {
      return false;
    }
  } else {
    PrintMenu();
    int c = GetChoice(0, 6);
    if (c == 0) {
      string s;
      do {
        cout << "Thread Question? (y/n)\n";
        getline(cin, s);
      } while (s != "y" && s != "n");
      if (s == "y") {
        cout << "Type Parent ID:\n";
        int parent_id = GetChoice(0, INT_MAX);
        ques.AddTh(usr->GetUsername(), parent_id);
      } else {
        string to_usr;
        cout << "Enter Receiver Username:\n";
        getline(cin, to_usr);
        if (!users.IsUserFound(to_usr)) {
          cout << "Error! User not found\n";
        } else {
          ques.AddQn(usr->GetUsername(), to_usr);
        }
      }
    } else if (c == 1) {
      cout << "Enter Question ID:\n";
      int id = GetChoice(0, INT_MAX);
      ques.AnsQn(usr->GetUsername(), id);
    } else if (c == 2) {
      for (const Question* const &qn : ques.GetQuesFrom(usr->GetUsername())) {
        qn->Print();
        cout << KSmallSeparator;
      }
    } else if (c == 3) {
      for (const Question *const &qn: ques.GetQuesTo(usr->GetUsername())) {
        qn->Print();
        cout << KSmallSeparator;
      }
    } else if (c == 4) {
      cout << "Users:\n";
      cout << "------\n";
      users.PrintUsers();
    } else if (c == 5) {
      string s;
      do {
        cout << "Are you sure? (y/n)\n";
        getline(cin, s);
        if (s == "n") {
          break;
        } else if (s == "y") {
          string username = usr->GetUsername();
          if (!users.DeleteUser(username)) { break; }
          ques.DeleteQuesFrom(username);
          ques.DeleteQuesTo(username);
          LogOut();
        }
      } while (s != "y" && s != "n");
    } else {
      LogOut();
    }
  }
  cout << KBigSeparator;
  return true;
}
