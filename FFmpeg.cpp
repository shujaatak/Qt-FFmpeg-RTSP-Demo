/*
 * FFmpeg.cpp
 *
 *  Created on: 2014年2月25日
 *      Author: ny
 */

#include "FFmpeg.h"



FFmpeg::FFmpeg()
{
    pCodecCtx = NULL;
    videoStream=-1;

}

FFmpeg::~FFmpeg()
{
    sws_freeContext(pSwsCtx);
}

int FFmpeg::initial(QString & url)
{
    int err;
    rtspURL=url;
    AVCodec *pCodec;
    av_register_all();
    avformat_network_init();
    pFormatCtx = avformat_alloc_context();
    pFrame=av_frame_alloc();
    err = avformat_open_input(&pFormatCtx, rtspURL.toStdString().c_str(), NULL,
                              NULL);
    if (err < 0)
    {
        printf("Can not open this file");
        return -1;
    }
    if (avformat_find_stream_info(pFormatCtx,NULL) < 0)
    {
        printf("Unable to get stream info");
        return -1;
    }
    int i = 0;
    videoStream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1)
    {
        printf("Unable to find video stream");
        return -1;
    }
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    width=pCodecCtx->width;
    height=pCodecCtx->height;
    avpicture_alloc(&picture,PIX_FMT_RGB24,pCodecCtx->width,pCodecCtx->height);
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    pSwsCtx = sws_getContext(width, height, PIX_FMT_YUV420P, width,
            height, PIX_FMT_RGB24,
            SWS_BICUBIC, 0, 0, 0);

    if (pCodec == NULL)
    {
        printf("Unsupported codec");
        return -1;
    }
    printf("video size : width=%d height=%d \n", pCodecCtx->width,
           pCodecCtx->height);
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        printf("Unable to open codec");
        return -1;
    }
    printf("initial successfully");
    return 0;
}

int FFmpeg::h264Decodec()
{
    int frameFinished=0;
    while (av_read_frame(pFormatCtx, &packet) >= 0)
    {
        if(packet.stream_index==videoStream)
        {
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
            if (frameFinished)
            {
                printf("***************ffmpeg decodec*******************\n");
                mutex.lock();
                int rs = sws_scale(pSwsCtx, (const uint8_t* const *) pFrame->data,
                                   pFrame->linesize, 0,
                                   height, picture.data, picture.linesize);
                mutex.unlock();
                if (rs == -1)
                {
                    printf("__________Can open to change to des imag_____________e\n");
                    return -1;
                }
            }
        }
    }
    return 1;

}
