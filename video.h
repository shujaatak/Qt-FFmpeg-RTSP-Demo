#ifndef VIDEO_H
#define VIDEO_H

#include <QMainWindow>
#include "FFmpeg.h"
namespace Ui {
class Video;
}

class Video : public QMainWindow
{
    Q_OBJECT

public:
    explicit Video(QWidget *parent = 0);
    ~Video();
    void paintEvent(QPaintEvent *);
    void setFFmpeg(FFmpeg * ff);

private:
    Ui::Video *ui;
    FFmpeg * ffmpeg;
};

#endif // VIDEO_H
