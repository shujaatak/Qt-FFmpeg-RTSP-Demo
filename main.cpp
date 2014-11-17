#include "login.h"
#include <QApplication>
#include <QString>
#include <stdio.h>
#include "FFmpeg.h"
#include <qthread.h>
#include "video.h"
#include <unistd.h>


/**
 * @brief The RtspThread class
 * Receive Thread
 */
class RtspThread : public QThread
{
public :
    void run();
    void setRtspURL(QString url);
    void setFFmpeg(FFmpeg * ff);
private:
    QString  rtspURL;// user input url
    FFmpeg * ffmpeg;//mian thread and rtspthread use the some ffmpeg object
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;// login Doialog
    Video video;//mainwindow for display video
    FFmpeg * ffmpeg;//global data for ffmpeg event
    ffmpeg=new FFmpeg();
    video.setFFmpeg(ffmpeg);
    RtspThread rtspthread;
    login.show();

    if(login.exec()==QDialog::Accepted)
    {
        printf("%s\n",login.getRtspURL().toStdString().c_str());
        rtspthread.setRtspURL(login.getRtspURL());
        rtspthread.setFFmpeg(ffmpeg);
        rtspthread.start();
        video.show();
        return a.exec();
    }else
    {
        return 0;
    }

}

void  RtspThread::run()
{
    ffmpeg->initial(rtspURL);
    ffmpeg->h264Decodec();
}

void RtspThread::setRtspURL(QString url)
{
    rtspURL=url;
}
void RtspThread::setFFmpeg(FFmpeg * ff)
{
    ffmpeg=ff;
}

