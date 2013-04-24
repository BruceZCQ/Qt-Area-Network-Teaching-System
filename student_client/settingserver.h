#ifndef SETTINGSERVER_H
#define SETTINGSERVER_H

#include <QDialog>

namespace Ui {
    class settingServer;
}

class SettingServer : public QDialog
{
    Q_OBJECT

public:
    explicit SettingServer(QWidget *parent = 0);
    ~SettingServer();
    void initServerConfData();

private slots:
    void settingServer();

private:
    Ui::settingServer *ui;
};

#endif // SETTINGSERVER_H
