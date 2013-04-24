#ifndef SETTINGSERVER_H
#define SETTINGSERVER_H

#include <QDialog>

namespace Ui {
    class settingDBServer;
}

class SettingDBServer : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDBServer(QWidget *parent = 0);
    ~SettingDBServer();
    void initDBServerConfData();

private slots:
    void settingDBServer();
signals:
    void imClosed();

private:
    Ui::settingDBServer *ui;
};

#endif // SETTINGSERVER_H
