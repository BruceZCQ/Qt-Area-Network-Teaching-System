#ifndef SERVERSETTINGDIALOG_H
#define SERVERSETTINGDIALOG_H

#include <QtCore>
#include <QtGui>

namespace Ui {
    class ServerSettingDialog;
}

class ServerSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerSettingDialog(QWidget *parent = 0);
    ~ServerSettingDialog();

    void initDBServerConfData();
    //setting default focus
    void setDefaultFocus();
signals:
    void imClosed();
private slots:
    void settingDBServer();
private:
    Ui::ServerSettingDialog *ui;
};

#endif // SERVERSETTINGDIALOG_H
