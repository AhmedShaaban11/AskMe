//
// Created by ahmed on 10/20/2022.
//

#ifndef ASKME_QUESDB_H
#define ASKME_QUESDB_H


class QuesDb {
 private:
  static int GenerateId();
  static bool IsIdOutOfRange(const int &id);
  static bool IsDeletedQuestion(const int &id);
  static bool IsIdExist(const int &id);
  static bool IsParentQuestion(const int &id);
  static int GetDbSize();
  static void PrintThreads(const int &id);
  static void DeleteThreads(const int &id);
  static void LoadData();
  static void SaveData();
 public:
  static bool AddQuestion(const int &parent_id, const int &from_id,
                          const int &to_id, const std::string &que);
  static bool AnswerQuestion(const int &id, const int &to_user_id,
                             const std::string &ans);
  static bool DeleteQuestion(const int &id, const int &from_id);
  static void PrintFeed(const int &num_of_parent_ques);
};


#endif //ASKME_QUESDB_H
