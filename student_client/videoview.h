#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

#include <QtCore>
#include <QtGui>

namespace Ui {
    class VideoView;
}

class VideoView : public QWidget
{
    Q_OBJECT

public:
    explicit VideoView(QWidget *parent = 0);
    ~VideoView();
    void setBasePath(QString basePath);
    void paintEvent(QPaintEvent *e);
private slots:
    void chooseCurrentVideo();
private:
    Ui::VideoView *ui;
    QString basePath;
    QProcess *process;
    void createActions();
    QString currentVideo;
    void startVideo();
};

#endif // VIDEOVIEW_H
