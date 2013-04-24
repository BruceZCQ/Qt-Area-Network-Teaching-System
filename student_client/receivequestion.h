#ifndef RECEIVEQUESTION_H
#define RECEIVEQUESTION_H

#include <QtCore>
#include <QtGui>
#include "questionset.h"
#include "constvar.h"

namespace Ui {
    class ReceiveQuestion;
}

class ReceiveQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveQuestion(QWidget *parent = 0);
    ~ReceiveQuestion();
    void setQuestion(QuestionSet *question);
    void exec();
signals:
    void answerSent(QString);
public slots:
    void toTop();
private slots:
    void changeDisplay();
    void answerSentSlot();
    void setTopLevel();

private:
    Ui::ReceiveQuestion *ui;
    QTimer *timer;
   double limitTime;
   QString currentQuestionID;
   void createActions();
};

#endif // RECEIVEQUESTION_H
