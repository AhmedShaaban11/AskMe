//
// Created by ahmed on 10/20/2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "QuesDb.h"
#include "../Question/Question.h"

const char KDataPath[] = "../data/ques_data.txt";

std::vector<Question> data;

bool QuesDb::LoadData() {
  if (!data.empty()) { // if data loaded before
    return false;
  }
  std::ifstream fin(KDataPath, std::ios::in);
  assert(!fin.fail());
  while (fin.peek() != EOF) {
    Question question;
    fin >> question;
    data.push_back(question);
  }
  fin.close();
  return true;
}

void QuesDb::SaveData() {
  std::ofstream fout(KDataPath, std::ios::out);
  assert(!fout.fail());
  for (const Question &question : data) {
    fout << question;
  }
  fout.close();
}
