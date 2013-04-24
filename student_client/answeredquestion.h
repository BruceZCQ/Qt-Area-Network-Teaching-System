#ifndef ANSWEREDQUESTION_H
#define ANSWEREDQUESTION_H

#include <QtCore>

class AnsweredQuestion
{
public:
    AnsweredQuestion();
    QString getQuestionID();
    QString getStudentID();
    QString getStudentAnswer();
    QString getQuestionTitle();
    QString getCorrectAnswer();
    QString getQuestionScore();
    QString getStudentScore();
    void setQuestionID(QString questionID);
    void setStudentID(QString studentID);
    void setStudentAnswer(QString StudentAnswer);
    void setQuestionTitle(QString questionTitle);
    void setCorrectAnswer(QString correctAnswer);
    void setQuestionScore(QString questionScore);
    void setStudentScore(QString studentScore);
private:
    QString questonID;
    QString studentID;
    QString  StudentAnswer;
    QString questionTitle;
    QString correctAnswer;
    QString questionScore;
    QString studentScore;
};

#endif // ANSWEREDQUESTION_H
