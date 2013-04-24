#ifndef FUNCTIONBOX_H
#define FUNCTIONBOX_H

#include <QDialog>

namespace Ui {
    class FunctionBox;
}

class FunctionBox : public QDialog
{
    Q_OBJECT

public:
    explicit FunctionBox(QWidget *parent = 0);
    ~FunctionBox();

private:
    Ui::FunctionBox *ui;
};

#endif // FUNCTIONBOX_H
