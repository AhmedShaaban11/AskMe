#include "general_functions.h"

vector<string> FileToLines(const string &file_name) {
  vector<string> vec;
  ifstream fin(file_name);
  if (fin.fail()) {
    cout << "Error! cannot open " << file_name << "\n";
  }
  string line;
  while (getline(fin, line)) {
    vec.push_back(line);
  }
  fin.close();
  return vec;
}

vector<string> LineToWords(const string &line, const string &delimiter) {
  vector<string> vec;
  int i = 0, j;
  while ((j = (int) line.find(delimiter, i)) < (int) line.size()) {
    vec.push_back(line.substr(i, j));
    i = j + (int) delimiter.size();
  }
  vec.push_back(line.substr(i));
  return vec;
}
