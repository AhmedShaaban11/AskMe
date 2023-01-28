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

vector<string> FileToLines(const string &file_name);
vector<string> LineToWords(const string &line, const string &delimiter);
string GetTxtTillDel(istream &in = cin, const string &del = "\n.\n");
