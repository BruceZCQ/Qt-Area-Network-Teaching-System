#include "style.h"

Style::Style()
{
}

void Style::styleWork(QWidget *w)
{
    QFile file(":/style/style");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    w->setStyleSheet(stylesheet);
}

void Style::styleNoWork(QWidget *w)
{
//    QFile file(":/style/style");
//    file.open(QFile::ReadOnly);
//    QTextStream filetext(&file);
//    QString stylesheet = filetext.readAll();
    w->setStyleSheet("");
}
