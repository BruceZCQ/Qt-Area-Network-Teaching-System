#include "customtextedit.h"

CustomTextEdit::CustomTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    defaultFormat = this->currentCharFormat();
    QGridLayout *mainLayout = new QGridLayout;
    searchBar = new QLineEdit;
    searchBar->hide();
    mainLayout->addWidget(searchBar,1,1,0,0,Qt::AlignLeft|Qt::AlignTop);
    setLayout(mainLayout);
    connect(searchBar,SIGNAL(textChanged(QString)),SLOT(searchCusorText(QString)));
    connect(searchBar,SIGNAL(editingFinished()),SLOT(searchCusorText()));
    connect(searchBar,SIGNAL(returnPressed()),SLOT(searchCusorText()));
}

void CustomTextEdit::setSearchBarFocus()
{
    searchBar->show();
    searchBar->setFocus();
}

void CustomTextEdit::setSize()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    searchBar->setMaximumWidth(screenRect.width()/3);
    searchBar->setMinimumWidth(screenRect.width()/3);
    QTextEdit::setMinimumWidth(screenRect.width()/3);
}

void CustomTextEdit::searchCusorText(){
    searchCusorText(searchBar->text());
}

void CustomTextEdit::searchCusorText(QString searchTxt)
{
    if(searchTxt.length() == 0){
        this->moveCursor(QTextCursor::Start);
        this->setCurrentCharFormat(defaultFormat);
    }
    else{
        if(this->find(searchTxt/*,QTextDocument::FindWholeWords*/)){
            QTextCharFormat seachKeyFormat;
            seachKeyFormat.setForeground(Qt::darkYellow);
            seachKeyFormat.setFontWeight(QFont::Bold);
            this->textCursor().setCharFormat(seachKeyFormat);
        }
        else{
            this->moveCursor(QTextCursor::Start);
        }
    }
}

void CustomTextEdit::removeSeachBarFocus()
{
    searchBar->clear();
    searchBar->hide();
}

void CustomTextEdit::seachText(QString searchTxt)
{
    searchCusorText(searchTxt);
    searchBar->show();
    searchBar->setText(searchTxt);
}
