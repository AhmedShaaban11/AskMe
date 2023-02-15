#include "gpm.h"

void gpm::PrintSeparator(char s, int len) {
  cout << string(len, s) << "\n";
}

string gpm::CorrectPath(const string &path) {
  string res;
  ifstream fin(path);
  bool is_opened = !fin.fail();
  fin.close();
  if (is_opened) {
    res = path;
    return res;
  }
  bool is_outer = (path.substr(0, 3) == "../");
  is_outer ? res = path.substr(3) : res = "../" + path;
  fin.open(res);
  is_opened = !fin.fail();
  fin.close();
  auto last_slash = path.find_last_of('/');
  if (path.substr(last_slash + 1) == ".run") {
    while (res.back() != '/') { res.pop_back(); }
  }
  return is_opened ? res : "";
}

vector<string> gpm::FileToLines(const string &path, const string &del) {
  vector<string> vec;
  string correct_path = CorrectPath(path);
  ifstream fin(correct_path);
  if (gpm::IsStreamFailed(fin, path)) {
    return vec;
  }
  string line;
  while (GetLine(fin, line, del)) {
    vec.push_back(line);
  }
  fin.close();
  return vec;
}

vector<string> gpm::LineToWords(const string &line, const string &del) {
  vector<string> vec;
  int i = 0, j;
  while ((j = (int) line.find(del, i)) != string::npos) {
    vec.push_back(line.substr(i, j - i));
    i = j + (int) del.size();
  }
  vec.push_back(line.substr(i));
  return vec;
}

bool gpm::YesOrNoQn(const string &msg) {
  char c;
  do {
    cout << msg << " (y/n)\n";
    cin >> c;
    c = (char) tolower(c);
    gpm::IgnoreLine();
  } while (c != 'y' && c != 'n');
  return c == 'y';
}

int gpm::InputInt(const string &msg, int lb, int ub) {
  int n;
  bool is_fail;
  do {
    is_fail = false;
    cout << msg << " (";
    cout << (lb == INT_MIN ? "-INF" : std::to_string(lb));
    cout << ":";
    cout << (ub == INT_MAX ? "INF" : std::to_string(ub));
    cout << ")\n";
    cin >> n;
    if (cin.fail()) {
      cin.clear();
      is_fail = true;
    }
    gpm::IgnoreLine();
  } while (is_fail || n < lb || n > ub);
  return n;
}

string gpm::InputString(const string &msg, const char &del) {
  string s;
  cout << msg << "\n";
  getline(cin, s, del);
  if (del != '\n') {
    gpm::IgnoreLine();
  }
  return s;
}

string gpm::InputString(const string &msg, const string &del) {
  char c;
  int idx = 0;
  string txt, tmp;
  cout << msg << "\n";
  while (tmp != del && idx < (int) del.size()) {
    cin.get(c);
    if (c == del[idx]) {
      tmp += c;
      ++idx;
      continue;
    }
    txt += tmp += c;
    tmp = "";
    idx = 0;
  }
  if (del.back() != '\n') {
    gpm::IgnoreLine();
  }
  return txt;
}

bool gpm::GetLine(istream &in, string &str, const string &del) {
  char c;
  int idx = 0;
  string tmp;
  str = "";
  while (!in.eof() && tmp != del && idx < (int) del.size()) {
    in.get(c);
    if (c == del[idx]) {
      tmp += c;
      ++idx;
      continue;
    }
    str += tmp += c;
    tmp = "";
    idx = 0;
  }
  return !in.eof();
}

void gpm::IgnoreLine() {
  cin.ignore(10000, '\n');
}
