#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;    
    //font seting
    QFont keyFont;
    keyFont.setPixelSize(18);
    QFont functionFont;
    functionFont.setPixelSize(14);
    //false and ture
    trueFalseKeyFormat.setFont(keyFont);
    trueFalseKeyFormat.setForeground(Qt::red);
    trueFalseKeyFormat.setFontWeight(QFont::Bold);
    QStringList falseandtrue;
    falseandtrue <<"\\btrue\\b"<<"\\bfalse\\b";
    foreach (const QString &pattern, falseandtrue) {
        rule.pattern = QRegExp(pattern);
        rule.format = trueFalseKeyFormat;
        highlightingRules.append(rule);
    }
    //classkeyformat
    classKeyFormat.setFont(keyFont);
    classKeyFormat.setForeground(Qt::blue);
    classKeyFormat.setFontWeight(QFont::Bold);
    QStringList classKeyList ;
    classKeyList <<"\\bJFrame\\b"<<"\\bhttp-equiv\\b"<<"\\btitle\\b"
                <<"\\bcontent\\b"<<"\\bBODY\\b"<<"\\bbody\\b" <<"\\bpage\\b"
               <<"\\blanguage\\b" <<"\\bpageEncoding\\b"<<"\\bHEAD\\b"<<"\\bDOCTYPE\\b"
               <<"\\bUTF-8\\b"<<"\\bGB2312\\B"<<"\\bGBK\\b"<<"\\bGB18030\\b"<<"\\bHTML\\b"<<"\\butf-8\\b"
              <<"\\bgb2312\\b"<<"\\bgbk\\b"<<"\\bgb18030\\b"<<"\\bhtml\\b"<<"\\bhead\\b" <<"\\bhref\\b"<<"\\bHREF\\b"
             <<"\\bdiv\\b"<<"\\bDIV\\b"<<"\\bli\\b"<<"\\bLI\\b"<<"\\bUL\\b"<<"\\bul\\b"<<"\\bol\\b"<<"\\bOL\\\b"<<"\\bbr\\b"
            <<"\\bform\\b"<<"\\binput\\b"<<"\\bbutton\\b"<<"\\bwidth\\b"<<"\\bheight\\b"<<"\\bdd\\b"<<"\\bdt\\b"<<"\\bdl\\b"
           <<"\\bh1\\b"<<"\\bh2\\b"<<"\\bh3\\b"<<"\\bh4\\b"<<"\\bh5\\b"<<"\\bh6\\b"<<"\\btype\\b"<<"\\ba\\b"<<"\\bleft\\b"
          <<"\\btop\\b"<<"\\bposition\\b"<<"\\babsolute\\b"<<"\\btext-align\\b"<<"\\bcenter\\b"<<"llbfont-size\\b"<<"\\bcolor\\b"
         <<"\\bz-index\\b"<<"\\bstyle\\b"<<"\\bopen\\b"<<"\\bgetElementById\\b"<<"\\bstrong\\b"<<"\\btable\\b"<<"\\btr\\b"
        <<"\\btd\\b"<<"\\bpre\\b"<<"\\bBR\\b"<<"\\bFORM\\b"<<"\\bINPUT\\b"<<"\\bBUTTON\\b"<<"\\bWIDTH\\b"<<"\\bHEIGHT\\b"
       <<"\\bDD\\b"<<"\\bDT\\b"<<"\\bDL\\b"<<"\\bH1\\b"<<"\\bH2\\b"<<"\\bH3\\b"<<"\\bH4\\b"<<"\\bH5\\b"<<"\\bH6\\b"
      <<"\\bTYPE\\b"<<"\\bA\\b"<<"\\bLEFT\\b"<<"\\bTOP\\b"<<"\\bPOSITION\\b"<<"\\bABSOULUTE\\b"<<"\\bTABLE\\b"
     <<"\\bTR\\b"<<"\\bTD\\b"<<"\\bonClick\\b"<<"\\bonBlur\\b"<<"\\bonFocus\\b"<<"\\bonChange \\b"<<"\\bonSubmit\\b"
    <<"\\bonload \\b"<<"\\bonUnload\\b"<<"\\bonMouseOver\\b"<<"\\bonMouseOut\\b"<<"\\bdocument\\b"<<"\\bwrite\\b"
    <<"\\blength\\b"<<"\\bDate\\b"
        /*javakey*/
        << "\\bclass\\b"<< "\\bvoid\\b";

    foreach (const QString &pattern, classKeyList) {
        rule.pattern = QRegExp(pattern);
        rule.format = classKeyFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setFont(keyFont);
    keywordFormat.setForeground(Qt::darkRed);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    /*java key end*/
    keywordPatterns << "\\bchar\\b" << "\\bconst\\b"<<"\\bswitch\\b"<<"\\bthis\\b"
                               << "\\bdouble\\b" << "\\benum\\b" << "\\bfinal\\b"<<"\\bfinally\\b"<<"\\bsynchronized\\b"
                              << "\\binline\\b" << "\\bint\\b"<<"\\babstract\\b"<<"\\bcase\\b"<<"\\bsuper\\b"
                              << "\\blong\\b"<<"\\bassert\\b"<<"\\bboolean\\b"<<"\\breturn\\b"<<"\\btransient\\b"
                              << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"<<"\\bif\\b"<<"\\bstrictfp\\b"
                            << "\\bshort\\b"<<"\\bbreak\\b"<<"\\bbyte\\b"<<"\\bextends\\b"<<"\\bnull\\b"<<"\\btry\\b"
                           << "\\bslots\\b" << "\\bstatic\\b"<<"\\bcatch\\b"<<"\\bfloat\\b"<<"\\binterface\\b"<<"\\bwhile\\b"
                           <<"\\bcontinue\\b"<<"\\bdefault\\b"<<"\\bdo\\b"<<"\\bfor\\b"<<"\\binstanceof\\b"<<"\\bString\\b"
                           << "\\bunsigned\\b" << "\\bvirtual\\b"<<"\\belse\\b"<<"\\bgoto\\b"<<"\\bnative\\b"<<"\\bInteger\\b"
                            << "\\bvolatile\\b"<<"\\bimport\\b"<<"\\bimplements\\b"<<"\\bnew\\b"<<"\\bpackage\\b"
                          << "\\bimplements\\b"<<"\\bthrow\\b"<<"\\bthrows\\b"
                             /*html*/
                          <<"\\bMETA\\b" <<"\\bmeta\\b"<<"\\bid\\b"<<"\\bsrc\\b"<<"\\bborder\\b"
                        /*javascript*/
                     <<"\\bfunction\\b"<<"\\bvar\\b"<<"\\bscript\\b"<<"\\bimg\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    packeageClassFormat.setFont(keyFont);
    packeageClassFormat.setFontWeight(QFont::Bold);
    packeageClassFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\java[a-z]+\\b");
    rule.format = packeageClassFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::gray);

    singleQuotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\'.*\'");
    rule.format = singleQuotationFormat;
    highlightingRules.append(rule);


    doubleQuotationFormat.setForeground(Qt::darkCyan);
    rule.pattern = QRegExp("\".*\"");
    rule.format = doubleQuotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFont(functionFont);
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);
    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
