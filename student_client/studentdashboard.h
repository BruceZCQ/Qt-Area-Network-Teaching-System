#ifndef STUDENTDASHBOARD_H
#define STUDENTDASHBOARD_H

#include <QtCore>
#include <QtGui>
#include <windows.h>
#include <QtNetwork>
#include "constvar.h"
#include "qxtglobalshortcut.h"
#include "style.h"
#include "constvar.h"
#include "codingwindow.h"
#include  "questionwindow.h"
#include "receivequestion.h"
#include "database.h"
#include "pptwin.h"
#include "videoview.h"
#include "showbroadcastcontent.h"

namespace Ui {
class StudentDashBoard;
}

class StudentDashBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentDashBoard(QWidget *parent = 0);
    ~StudentDashBoard();
    void paintEvent(QPaintEvent *);
    void moveEvent(QMoveEvent *e);
    void setDataBase(ServerDataBase *database);
    void setHost(QString hostAddress);
    void setCurrentStudent(QString studentID);
    bool connectQuestionServer( );
public slots:
    void showFullScreen();
    void hide();
private:
    Ui::StudentDashBoard *ui;
    QTimer *timer;
    QTimer *messageCheck;
    bool hasMessage;
    QString message;
    CodingWindow *codingWin;
    QuestionWindow *questionWin;
    QTcpSocket *socket;
    int questionId;
    ServerDataBase *database;
    PPTView *pptWin;
    QString serverIP;
    QString studentID;
    VideoView *videoViewWin;
    QLabel *statusLabel;
    QTimer *broadCastTimer;
    QTimer *clearBroadCastContent;
    QTimer *clearHelpContent;
    ShowBroadCastContent *showBroadCastWin;
    void createActions();
    void createGlobalActions();
private slots:
    void changeMessageState(QString answer);
    void statusMessage();
    void showHelpInfo();
    void receiveQuestionID();
    void viewPPt();
    void quitApp();
    void newQuestion();
    void sendStudentStatus();
    void refreshDataFromDB();
    void showBroadCastContent();
    void clearBroadCast();
    //exercise
    void exerciseQuestion();
    void viewVideos();
signals:
    void exitApp();
    void refreshDatabase();
};

#endif // STUDENTDASHBOARD_H
