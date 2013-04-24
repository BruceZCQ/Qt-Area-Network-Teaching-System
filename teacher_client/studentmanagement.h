#ifndef STUDENTMANAGEMENT_H
#define STUDENTMANAGEMENT_H

#include <Qtcore>
#include <QtGui>
#include "teachingroomstudents.h"

namespace Ui {
    class StudentManagement;
}

class StudentManagement : public QDialog
{
    Q_OBJECT

public:
    explicit StudentManagement(QWidget *parent = 0);
    ~StudentManagement();
    void setClassList(QStringList classNameList);
    void addStudentItem(QString className,QList<TeachingRoomStudents*> studentList);
private slots:
    void selectClass(QTreeWidgetItem*,int);
    void slotRefreshData();
    void exec();
signals:
    void refreshData();
    void emitAddClass();
private:
    Ui::StudentManagement *ui;
    QStringList classNameList;
    QHash<QString,QList<TeachingRoomStudents*> > studentsList;
    void setStudentList(QString className="ALL");
    QString currentClass;
};

#endif // STUDENTMANAGEMENT_H
