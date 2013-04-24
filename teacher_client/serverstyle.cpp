#include "serverstyle.h"

ServerStyle::ServerStyle()
{
}

void ServerStyle::styleWork(QWidget *w)
{
    QFile file(":/appFace/style");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    w->setStyleSheet(stylesheet);
}
