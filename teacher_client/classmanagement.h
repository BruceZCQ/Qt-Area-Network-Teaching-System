#ifndef CLASSMANAGEMENT_H
#define CLASSMANAGEMENT_H

#include <QtCore>
#include <QtGui>
#include "teachingroomclass.h"


namespace Ui {
    class ClassManagementDialog;
}

class ClassManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassManagementDialog(QWidget *parent = 0);
    ~ClassManagementDialog();
    void setClassCount(int classCount);
    void setClassItems(int rowIndex, int columnIndex,TeachingRoomClass *currentClass);
    void setManageBtn(int rowIndex);
    //bool eventFilter(QObject *o, QEvent *e);
private slots:
    void manageClass(int row, int column);
    void slotNewClassInfo();
    void addNewClassSuccess();
signals:
    void emitNewClassInfo(QString className,QString studentCount);
    void deleteClassbyName(QString className);
private:
    Ui::ClassManagementDialog *ui;
   // QEvent *event;
};

#endif // CLASSMANAGEMENT_H
