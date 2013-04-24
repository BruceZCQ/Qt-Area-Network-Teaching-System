#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QtCore>
#include <QtGui>
#include "serverconst.h"

class CustomStudentTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit CustomStudentTableWidget(QWidget *parent = 0);
    void setColumnWidth(int column,int width);
    
signals:
    
public slots:
    
};

#endif // CUSTOMTABLEWIDGET_H
