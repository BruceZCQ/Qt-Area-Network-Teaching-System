#ifndef INFOTABWIDGET_H
#define INFOTABWIDGET_H

#include <QtCore>
#include <QtGui>

class InfoTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit InfoTabWidget(QWidget *parent = 0);
    void closeEvent(QCloseEvent *e);
signals:
    void clearList();
public slots:
    void emptyInfoTabWidget();
};

#endif // INFOTABWIDGET_H
