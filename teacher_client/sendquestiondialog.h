#ifndef SENDQUESTIONDIALOG_H
#define SENDQUESTIONDIALOG_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include "questionset.h"
#include "editquestion.h"
#include "teachingroomstudents.h"


namespace Ui {
    class SendQuestionDialog;
}

class SendQuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendQuestionDialog(QWidget *parent = 0);
    ~SendQuestionDialog();
    void closeEvent(QCloseEvent *e);
    void setCurrentUser(TeachingRoomStudents *user);
    void setQuestionSet(QuestionSet *question);
    void clearQuestionInfo();
private:
    Ui::SendQuestionDialog *ui;
    QHash<int,QuestionSet*> questionList;
    EditQuestion *editQuestion;
    TeachingRoomStudents  *currentStundent;
public slots:
    void changeQuestionData(int quesionIndex);
    void editCurrentQuestion();
    void changeCurrentQuestionIndex(int index);
    void refreshQuestionSetSlot();
private slots:
    void sendQuestionID();
signals:
    void refreshQuestionSet();
    void emitNewValue(QString questionIndex,
                      QString chapterID,
                      QString questionTitle,
                      QString questionContext,
                      QString limitTime,
                      QString questionScore,
                      QString anwser);
    void emtUpdateResult(bool);
    void sentQuestion(QString questionInfo);
};

#endif // SENDQUESTIONDIALOG_H
