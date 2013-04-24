#include "functionbox.h"
#include "ui_functionbox.h"

FunctionBox::FunctionBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
}

FunctionBox::~FunctionBox()
{
    delete ui;
}
