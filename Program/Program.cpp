#include "Program.h"
#include "../GeneralFunctions/general_functions.h"
#include "../Question/Question.h"
#include "../User/User.h"

Program::Program() {
  sign_menu_.emplace_back("SignUp");
  sign_menu_.emplace_back("LogIn");
  sign_menu_.emplace_back("Exit");
  features_menu_.emplace_back("Ask");
  features_menu_.emplace_back("Answer");
  features_menu_.emplace_back("Print Questions From Me");
  features_menu_.emplace_back("Print Questions To Me");
  features_menu_.emplace_back("Print Feed");
  features_menu_.emplace_back("Print Available Users");
  features_menu_.emplace_back("Delete a Question");
  features_menu_.emplace_back("Delete your Account");
  features_menu_.emplace_back("LogOut");
}

Program::~Program() {
  sign_menu_.clear();
  features_menu_.clear();
}

void Program::PrintSignMenu() const {
  for (int i = 0; i < (int) sign_menu_.size(); ++i) {
    cout << i << " - " << sign_menu_[i] << "\n";
  }
  gpm::PrintSeparator('=');
}

void Program::PrintFeaturesMenu() const {
  for (int i = 0; i < (int) features_menu_.size(); ++i) {
    cout << i << " - " << features_menu_[i] << "\n";
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
    int c = gpm::InputInt("Enter a number:", 0, (int) sign_menu_.size() - 1);
    if (c == 0) {
      users.AddUser();
    } else if (c == 1) {
      usr = users.AccessUser();
    } else {
      return false;
    }
  } else {
    PrintFeaturesMenu();
    int c = gpm::InputInt("Enter a number:", 0, (int) features_menu_.size() - 1);
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
      ques.PrintFeed();
    } else if (c == 5) {
      users.PrintUsers();
    } else if (c == 6) {
      int id = gpm::InputInt("Enter Question ID:", 0);
      ques.DeleteQn(id, usr);
    } else if (c == 7) {
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
