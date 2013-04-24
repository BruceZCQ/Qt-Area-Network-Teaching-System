#ifndef QUESTIONSET_H
#define QUESTIONSET_H

#include <QtCore>

class QuestionSet
{
public:
    QuestionSet();
    void setQustionID(QString id);
    void setChapterID(QString id);
    void setQuestionTitle(QString title);
    void setQuestionContent(QString content);
    void setQuestionLimitTime(QString limitTime);
    void setQuestionPublicDate(QString publicDate);
    void setQuestionScore(QString score);
    void setQuestionAnwser(QString anwser);
    QString getQuestionID();
    QString getChapterID();
    QString getQuestionTitle();
    QString getQuestionContent();
    QString getQuestionLimitTime();
    QString getQuestionPublicDate();
    QString getQuestionScore();
    QString getQuestionAnwser();
private:
    QString questionID;
    QString chapterID;
    QString questionTitle;
    QString questionContent;
    QString questionLimitTime;
    QString questionPublicDate;
    QString questionScore;
    QString questionAnwser;
};

#endif // QUESTIONSET_H
