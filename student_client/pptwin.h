#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <Qt>
#include <QNetworkProxyFactory>
#include "windows.h"

namespace Ui {
    class PPTWin;
}

class PPTView : public QDialog
{
    Q_OBJECT

public:
    explicit PPTView(QWidget *parent = 0);
    ~PPTView();
    void keyPressEvent(QKeyEvent *e);
    void setServerConf();
    void setHost(QString hostAddress);
    void clearData();
    void initPPTList(int pptID,QString chapterName);
signals:
public slots:
private slots:
    void pptPressed(QTreeWidgetItem *, int);
   void reloadPPT();
private:
   void createActions();
    Ui::PPTWin *ui;
    QString hostAddress;
    int screenWidth;
    int screenHeigth;
    int courseID;
    QHash<int,QString> pptList;
    QHash<QString,QString> pointList;
    void setCurrentPPT(int courseID);
};

#endif // MAINWINDOW_H
