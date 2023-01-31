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
  const char KSmallSeparator[] = "------------------------------";
  const char KBigSeparator[] = "==============================";
  vector<string> FileToLines(const string &file_name);
  vector<string> LineToWords(const string &line, const string &delimiter);
  string GetTxtTillDel(istream &in = cin, const string &del = "\n.\n");
  template<class T> string ToString(const string &del, const T &head) {
    return head;
  }
  template<class T, class... Ts> string ToString(const string &del, const T &head, const Ts &...rest) {
    return head + del + ToString(del, rest...);
  }
}
