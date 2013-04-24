#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QtCore>
#include <QtGui>

class CustomTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit CustomTabWidget(QWidget *parent = 0);
    void addTab(QWidget *widget, const QIcon &icon, const QString &label);
    void addTab( QWidget * page, const QString & label);
    void setTabsClosable(int index);
    void setTabsClosable(bool boo);
private :
    void setProfileByCount();
    void setProfileByIndex(int index);
private slots:
    void removeTab(int index);
signals:

public slots:    
    void setCurrentIndex(int index);
};

#endif // CUSTOMTABWIDGET_H
