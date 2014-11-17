#include "video.h"
#include "ui_video.h"
#include <QPainter>
Video::Video(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Video)
{
    ui->setupUi(this);
    ffmpeg=NULL;
}

Video::~Video()
{
    delete ui;
}
void Video::setFFmpeg(FFmpeg *ff)
{
    ffmpeg=ff;
}

void Video::paintEvent(QPaintEvent *)
{
    if(ffmpeg->picture.data!=NULL)
    {
     QPainter painter(this);
    if(ffmpeg->mutex.tryLock(1000))
    {

        QImage image=QImage(ffmpeg->picture.data[0],ffmpeg->width,ffmpeg->height,QImage::Format_RGB888);
        QPixmap  pix =  QPixmap::fromImage(image);
        painter.drawPixmap(0, 0, 640, 480, pix);
        update();
        ffmpeg->mutex.unlock();
    }
    }
}
