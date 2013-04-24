#include <QtGui/QApplication>
#include <QtCore>
#include <QTextCodec>
#include "loginserverdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //setting db driver directory
    qApp->addLibraryPath(qApp->applicationDirPath () + "/plugins");
    LoginServerDialog login;
    login.show();

    return a.exec();
}
