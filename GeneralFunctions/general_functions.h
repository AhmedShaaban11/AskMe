#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;
using std::ifstream;
using std::istream;
using std::cout;
using std::cin;

namespace gpm {
  void PrintSeparator(char s = '-', int len = 30);
  vector<string> FileToLines(const string &file_name);
  vector<string> LineToWords(const string &line, const string &delimiter);
  string GetTxtTillDel(istream &in = cin, const string &del = "\n.\n");
  bool YesOrNoQn(const string &msg);
  int InputInt(const string &msg, int lb = INT_MIN, int ub = INT_MAX);
  template<class T> string ToString(const string &del, const T &head) {
    return head;
  }
  template<class T, class... Ts> string ToString(const string &del, const T &head, const Ts &...rest) {
    return head + del + ToString(del, rest...);
  }
}
