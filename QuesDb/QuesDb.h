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
  static void AddThreadToParent(const int &thread_id, const int &parent_id);
 public:
  static bool LoadData();
  static void SaveData();
  static void AddQuestion(const int &parent_id, const int &from_id,
                          const int &to_id, const std::string &que);
  static bool AnswerQuestion(const int &id, const int &to_user_id,
                             const std::string &ans);
  static bool DeleteQuestion(const int &id, const int &from_id);
};


#endif //ASKME_QUESDB_H
