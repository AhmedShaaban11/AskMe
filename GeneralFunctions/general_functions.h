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
  const char KUnitSeparator[] = "@@@";
  const char KLineSeparator[] = "~~~\n";
  void PrintSeparator(char s = '-', int len = 30);
  vector<string> FileToLines(const string &file_name, const string &del = "\n");
  vector<string> LineToWords(const string &line, const string &del = ",");
  bool YesOrNoQn(const string &msg);
  int InputInt(const string &msg, int lb = INT_MIN, int ub = INT_MAX);
  string InputString(const string &msg, const char &del = '\n');
  string InputString(const string &msg, const string &del);
  bool GetLine(istream &in, string &str, const string &del = "\n");
  void IgnoreLine();
  template<class T> string ToString(const string &del, const T &head) {
    return head;
  }
  template<class T, class... Ts> string ToString(const string &del, const T &head, const Ts &...rest) {
    return head + del + ToString(del, rest...);
  }
}
