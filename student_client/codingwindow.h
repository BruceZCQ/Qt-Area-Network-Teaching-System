#ifndef CODINGWINDOW_H
#define CODINGWINDOW_H

#include <QtCore>
#include <QtGui>
#include "highlighter.h"
#include "qxtglobalshortcut.h"
#include "constvar.h"

namespace Ui {
class CodingWindow;
}

class CodingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CodingWindow(QWidget *parent = 0);
    ~CodingWindow();
public slots:
private slots:
    void searchCusorText();
    void startServer();
    void stopServer();
    void openFile();
    void runCode();
    void setViewWindows();
    void clearViewWin();
    void close();
    void setResultView(QString prePath,QString currentFileName);
    void changeButtonState();
    void showJavaCode();
signals:
    void serverStarted();
    void exitCoding();
private:
    Ui::CodingWindow *ui;
    Highlighter *jspHighlighter;
    Highlighter *javaHighlighter;
    bool isShowViewWin;
    bool isRun;
    bool shouldSavetoServerPath;
    QString jspfilesDir;
    QString currentFilePath;
    QString prePath;
    QString currentFileName;
    void createActions();
};

#endif // CODINGWINDOW_H
