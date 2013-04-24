#ifndef TEACHINGDB_H
#define TEACHINGDB_H

#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include "teachingroomclass.h"
#include "teachingroomstudents.h"
#include "questionset.h"
#include "answeredquestion.h"

class TeachingDB
{
public:
    TeachingDB(QString host,QString port);
    ~TeachingDB();
    TeachingRoomStudents*  getStudentsByClassFromDB(QString className,int index);
    int getStudentsCountByClassName(QString className);
    TeachingRoomClass* getClassFromDB(int index);
    int getClassCount();
    bool getConnectionResult();
    void initData();
    void closeDB();
    bool changePassword(QString newPassword);
    bool checkLoginingUser(QString userPassword);
    bool addNewClass(QString className, QString studentCount);
    bool deleteClassbyName(QString className);
    int getQuestionSetSize();
    QuestionSet* getQuestionFromSet(int questionIndex);
    bool updateQuestion(QString questionIndex,
                      QString chapterID,
                      QString questionTitle,
                      QString questionContext,
                      QString limitTime,
                      QString questionScore,
                      QString anwser);
    int getChapterListSize();
    QString getChapterFromList(int chapterIndex);
    bool deleteStudent(QString deleteStudentKey);
     bool deleteStudents(QString className);
    bool setStudentScoreZero(QString setStudentKey);
    bool addQuestion(QString chapterID,
                     QString questionTitle,
                     QString questionContext,
                     QString questionLimitTime,
                     QString questionScore,
                     QString answer);
    TeachingRoomStudents* getStudentByIDandName(QString key);
    QString getQuestionKeyByIndex(int index);
    void getQuestionListByChapterID(QString chapterID);
    int getQuestionListSize();
    QString getStudentStatusByName(QString name);
    QuestionSet * getQuestionByKey(QString key);
    QuestionSet* getQuestionByID(QString questionID);
    QString getStudentScore(QString studentID);
    bool updateStudentScore(QString studentID,int score);
    bool studentAnsweredQuestion(AnsweredQuestion *answeredQuestion);
    void preperGetAnswerQuestionList(QString stundentIDAndName);
    void  getAnswerQuestionList(QString stundentID);
    int getAnswerQuestionListSize();
    AnsweredQuestion* getAnswerQuestion(int index);
private:
    QHash<QString,QString> classList;
    QHash<QString,TeachingRoomStudents*> studentsList;
    QHash<QString,TeachingRoomStudents*> students;
    QHash<QString,TeachingRoomStudents*> studentsSet;
    bool databaseConnectionSuccess;
    QSqlDatabase *db;
    QList<QuestionSet*> questionSetList;
    QHash<QString,QuestionSet*> questionSet;
    QList<QuestionSet*> questionList;
    QHash<QString,QuestionSet*> questionHashList;
    QHash<QString,AnsweredQuestion*> answeredQuenstionList;
    QStringList chapterList;
};

#endif // TEACHINGDB_H
