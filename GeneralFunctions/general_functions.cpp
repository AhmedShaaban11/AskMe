#include "general_functions.h"

void gpm::PrintSeparator(char s, int len) {
  cout << string(len, s) << "\n";
}

vector<string> gpm::FileToLines(const string &file_name) {
  vector<string> vec;
  ifstream fin(file_name);
  if (fin.fail()) {
    cout << "Error! cannot open " << file_name << "\n";
    return vec;
  }
  string line;
  while (getline(fin, line)) {
    vec.push_back(line);
  }
  fin.close();
  return vec;
}

vector<string> gpm::LineToWords(const string &line, const string &delimiter) {
  vector<string> vec;
  int i = 0, j;
  while ((j = (int) line.find(delimiter, i)) != string::npos) {
    vec.push_back(line.substr(i, j - i));
    i = j + (int) delimiter.size();
  }
  vec.push_back(line.substr(i));
  return vec;
}

string gpm::GetTxtTillDel(istream &in, const string &del) {
  cout << "Enter Question text: (End with '" << del << "')\n";
  char c;
  int idx = 0;
  string text, tmp;
  while (tmp != del && idx < (int) del.size()) {
    in.get(c);
    if (c == del[idx]) {
      tmp += c;
      ++idx;
      continue;
    }
    text += tmp += c;
    tmp = "";
  }
  return text;
}

bool gpm::YesOrNoQn(const string &msg) {
  char c;
  do {
    cout << msg << " (y/n)\n";
    cin >> c;
    c = (char) tolower(c);
    cin.ignore(10000, '\n');
  } while (c != 'y' && c != 'n');
  return c == 'y';
}
