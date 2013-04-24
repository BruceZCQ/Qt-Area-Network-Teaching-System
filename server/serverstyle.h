#ifndef SERVERSTYLE_H
#define SERVERSTYLE_H

#include <QtCore>
#include <QtGui>

class ServerStyle
{
public:
    ServerStyle();
    void styleWork(QWidget *w);
    void styleNoWork(QWidget *w);
};

#endif // SERVERSTYLE_H
