#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QtCore>
#include <QtGui>

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = 0);
    ~SignUpDialog();
    void initData(QString className);
    void clearClassList();
signals:
    void emitRegisterData(QString studentID,
                          QString userName,
                          QString sex,
                          QString className);
private:
    Ui::SignUpDialog *ui;
public slots:
    void accept();
private slots:
    void acceptDialog();
};

#endif // SIGNUPDIALOG_H
