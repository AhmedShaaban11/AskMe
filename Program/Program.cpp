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
  cout << KBigSeparator << "\n";
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
  cout << KBigSeparator << "\n";
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
  cout << KBigSeparator << "\n";
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
      string s;
      do {
        cout << "Thread Question? (y/n)\n";
        getline(cin, s);
      } while (s != "y" && s != "n");
      string a;
      do {
        cout << "Are you Anonymous? (y/n)\n";
        getline(cin, a);
      } while (a != "y" && a != "n");
      string to_usr;
      int parent_id = -1;
      if (s == "y") {
        cout << "Type Parent ID:\n";
        parent_id = GetChoice(0, INT_MAX);
        to_usr = ques.GetToUsr(parent_id);
        if (!users.IsUserFound(to_usr)) {
          cout << "Error! User not found\n";
        } else if (a == "y" && !users.IsUserAcceptingAnonymous(to_usr)) {
          cout << "Error! User doesn't accept anonymous questions.\n";
        } else {
          ques.AddTh(usr, parent_id, a == "y");
        }
      } else {
        cout << "Enter Receiver Username:\n";
        getline(cin, to_usr);
        if (!users.IsUserFound(to_usr)) {
          cout << "Error! User not found\n";
        } else if (a == "y" && !users.IsUserAcceptingAnonymous(to_usr)) {
          cout << "Error! User doesn't accept anonymous questions.\n";
        } else {
          ques.AddQn(usr, to_usr, a == "y");
        }
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
      cout << "Users:\n";
      cout << "------\n";
      users.PrintUsers();
    } else if (c == 5) {
      cout << "Enter Question ID:\n";
      int id = GetChoice(0, INT_MAX);
      ques.DeleteQn(id, usr);
    } else if (c == 6) {
      string s;
      do {
        cout << "Are you sure? (y/n)\n";
        getline(cin, s);
        if (s == "n") {
          break;
        } else if (s == "y") {
          if (!users.DeleteUser(usr)) { break; }
          ques.DeleteAllQues(usr);
          LogOut();
        }
      } while (s != "y" && s != "n");
    } else {
      LogOut();
    }
  }
  cout << KBigSeparator << "\n";
  return true;
}
