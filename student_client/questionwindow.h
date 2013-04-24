#ifndef QUESTIONWINDOW_H
#define QUESTIONWINDOW_H

#include <QtCore>
#include <QtGui>
#include <windows.h>
#include "constvar.h"
#include "database.h"
#include "questionset.h"
#include "questionwidget.h"
#include "constvar.h"


namespace Ui {
class QuestionWindow;
}

class QuestionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuestionWindow(QWidget *parent = 0);
    ~QuestionWindow();
    void setDatabase(ServerDataBase *database);
public slots:
    void showFullScreen();
private slots:
    void close();
    void startQuestion();
    void setQuestionCount(QString value);
    void removeWidgetFormStackWidget();
    void prePage();
    void nextPage();
    void changeTime();
    void settingTime(QString value);
    void clearAll();
private:
    Ui::QuestionWindow *ui;
    void createActions();
    ServerDataBase *database;
    void preperQuestionList();
    enum FLAGS{START,STOP};
    int flags;
    QTimer *deleteWidget;
    void stopQuestion();
    void addQuestion(int id);
    QTimer *startQuestionTimer;
    int endTime;
    int startTime;
    void answerEnd();
signals:
};

#endif // QUESTIONWINDOW_H
