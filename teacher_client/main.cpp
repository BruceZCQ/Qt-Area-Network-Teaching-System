#include <QtGui/QApplication>
#include <QTextCodec>
#include "logindialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication::setQuitOnLastWindowClosed(false);
    //setting db driver directory
    qApp->addLibraryPath(qApp->applicationDirPath () + "/plugins");

    TeachingLoginDialog loginDialog;
    loginDialog.show();

    return a.exec();
}
