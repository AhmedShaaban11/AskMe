#include <iostream>
#include "SignUp/SignUp.h"
#include "UsersDb/UsersDb.h"
#include "QuesDb/QuesDb.h"
#include "User/User.h"
#include "LogIn/LogIn.h"

const char KSeparator[] = "====================\n";
const char KSmallSeparator[] = "------------------\n";

bool SignUpMenu();
void SignUpInput();
void LogInInput();
bool UserMenu(User *ptr);
void AnswerQuestionInput(User *ptr);
void DeleteQuestionInput(User *ptr);
void AskQuestionInput(User *ptr);
void FeedInput();

int main() {
  while (SignUpMenu()) { }
  return 0;
}

bool SignUpMenu() {
  std::cout << KSeparator;
  std::cout << "1. Sign Up\n";
  std::cout << "2. Log In\n";
  std::cout << "3. Exit\n";
  std::cout << KSmallSeparator;
  int choice = -1;
  while (choice < 1 || choice > 3) {
    std::cout << "Enter your choice:\n";
    std::cin >> choice;
    if (std::cin.fail()) { std::cin.clear(); }
    std::cin.sync();
  }
  if (choice == 1) {
    SignUpInput();
  } else if (choice == 2) {
    LogInInput();
  } else {
    return false;
  }
  return true;
}

void SignUpInput() {
  std::cout << KSeparator;
  std::cout << "Enter your username, email, password, and (0/1) for accepting anonymous questions (respectively):\n";
  std::string username, email, password;
  bool is_accepting_anonymous;
  std::cin >> username >> email >> password >> is_accepting_anonymous;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.sync();
    std::cout << "Invalid input.\n";
    return;
  }
  std::cin.sync();
  if (SignUp::Sign(username, email, password, is_accepting_anonymous)) {
    std::cout << "Signed up successfully.\n";
  } else {
    std::cout << "Failed to sign up.\n";
  }
}

void LogInInput() {
  std::cout << KSeparator;
  std::cout << "Enter your username, and password (respectively):\n";
  std::string username, password;
  std::cin >> username >> password;
  std::cin.sync();
  User *ptr = new User(LogIn::LogInUser(username, password));
  if (LogIn::IsLoggedIn()) {
    std::cout << "Logged in successfully.\n";
    while (UserMenu(ptr)) { }
  } else {
    std::cout << "Failed to log in.\n";
    delete ptr;
  }
}

bool UserMenu(User *ptr) {
  std::cout << KSeparator;
  std::cout << "1. Print Questions To Me\n";
  std::cout << "2. Print Questions From Me\n";
  std::cout << "3. Answer Question\n";
  std::cout << "4. Delete Question\n";
  std::cout << "5. Ask Question\n";
  std::cout << "6. List System Users\n";
  std::cout << "7. Feed\n";
  std::cout << "8. Log Out\n";
  std::cout << KSmallSeparator;
  int choice = -1;
  while (choice < 1 || choice > 8) {
    std::cout << "Enter your choice:\n";
    std::cin >> choice;
    if (std::cin.fail()) { std::cin.clear(); }
    std::cin.sync();
  }
  if (choice == 1) {
    ptr->PrintQuestionsTo();
  } else if (choice == 2) {
    ptr->PrintQuestionsFrom();
  } else if (choice == 3) {
    AnswerQuestionInput(ptr);
  } else if (choice == 4) {
    DeleteQuestionInput(ptr);
  } else if (choice == 5) {
    AskQuestionInput(ptr);
  } else if (choice == 6) {
    UsersDb::ListSystemUsers();
  } else if (choice == 7) {
    FeedInput();
  } else {
    ptr->LogOut();
    return false;
  }
  return true;
}

void AnswerQuestionInput(User *ptr) {
  std::cout << KSeparator;
  std::cout << "Enter the question id:\n";
  int id;
  std::cin >> id;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.sync();
    std::cout << "Invalid input.\n";
    return;
  }
  std::cin.sync();
  std::cout << "Enter the answer:\n";
  std::string answer;
  getline(std::cin >> std::ws, answer);
  if (ptr->Answer(id, answer)) {
    std::cout << "Answered successfully.\n";
  } else {
    std::cout << "Failed to answer.\n";
  }
}

void DeleteQuestionInput(User *ptr) {
  std::cout << KSeparator;
  std::cout << "Enter the question id:\n";
  int id;
  std::cin >> id;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.sync();
    std::cout << "Invalid input.\n";
    return;
  }
  std::cin.sync();
  if (ptr->DeleteQuestion(id)) {
    std::cout << "Deleted successfully.\n";
  } else {
    std::cout << "Failed to delete.\n";
  }
}

void AskQuestionInput(User *ptr) {
  std::cout << KSeparator;
  std::cout << "Enter the id of the user, id of the parent question(-1 if not exist), and is it anonymous or not(0/1) (respectively):\n";
  int to_id, parent_id;
  bool is_anonymous;
  std::cin >> to_id >> parent_id >> is_anonymous;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.sync();
    std::cout << "Invalid input.\n";
    return;
  }
  std::cin.sync();
  std::cout << "Enter the question:\n";
  std::string question;
  getline(std::cin >> std::ws, question);
  if (ptr->Ask(to_id, question, is_anonymous, parent_id)) {
    std::cout << "Asked successfully.\n";
  } else {
    std::cout << "Failed to ask.\n";
  }
}

void FeedInput() {
  std::cout << KSeparator;
  std::cout << "Enter the number of questions to show:\n";
  int number;
  std::cin >> number;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.sync();
    std::cout << "Invalid input.\n";
    return;
  }
  std::cin.sync();
  QuesDb::PrintFeed(number);
}
