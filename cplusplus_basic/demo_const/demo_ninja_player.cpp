extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libavdevice/avdevice.h"
}

void open_rtsp(const char *rtsp)
{
    unsigned int    i;
    int             ret;
    int             video_st_index = -1;
    int             audio_st_index = -1;
    AVFormatContext *ifmt_ctx = NULL;
    AVPacket        pkt;
    AVStream        *st = NULL;
    char            errbuf[64];
    AVDictionary *optionsDict = NULL;
    av_register_all();                                                          // Register all codecs and formats so that they can be used.
    avformat_network_init();                                                    // Initialization of network components
    av_init_packet(&pkt);                                                       // initialize packet.
    pkt.data = NULL;
    pkt.size = 0;
    bool nRestart = false;
    AVStream *pVst;
    uint8_t* buffer_rgb = NULL;
    AVCodecContext *pVideoCodecCtx = NULL;
    AVFrame         *pFrame = av_frame_alloc();
    AVFrame         *pFrameRGB = av_frame_alloc();
    int got_picture;
    SwsContext  *img_convert_ctx = NULL;
    AVCodec *pVideoCodec = NULL;
    av_dict_set(&optionsDict, "rtsp_transport", "tcp", 0);
    av_dict_set(&optionsDict, "stimeout", "2000000", 0);
    if ((ret = avformat_open_input(&ifmt_ctx, rtsp, 0, &optionsDict)) < 0) {
        printf("Could not open input file '%s' (error '%s')\n", rtsp, av_make_error_string(errbuf, sizeof(errbuf), ret));
        goto EXIT;
    }
 
    if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)) < 0) {
        printf("Could not open find stream info (error '%s')\n", av_make_error_string(errbuf, sizeof(errbuf), ret));
        goto EXIT;
    }
 
    for (i = 0; i < ifmt_ctx->nb_streams; i++) {
        av_dump_format(ifmt_ctx, i, rtsp, 0);
    }
 
    for (i = 0; i < ifmt_ctx->nb_streams; i++) 
    {
        st = ifmt_ctx->streams[i];
        switch (st->codec->codec_type) 
        {
            case AVMEDIA_TYPE_AUDIO: audio_st_index = i; break;
            case AVMEDIA_TYPE_VIDEO: video_st_index = i; break;
            default: break;
        }
    }
    if (-1 == video_st_index) {
        printf("No H.264 video stream in the input file\n");
        goto EXIT;
    }
 
    if (!nRestart)
    {
        pVst = ifmt_ctx->streams[video_st_index];
        pVideoCodecCtx = pVst->codec;
        pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
        if (pVideoCodec == NULL)
            return;
        if (avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0)
            return;
    }
    while (1)
    {
        do {
            ret = av_read_frame(ifmt_ctx, &pkt);
            if (pkt.stream_index == video_st_index)
            {
                fprintf(stdout, "pkt.size=%d,pkt.pts=%lld, pkt.data=0x%x.\n", pkt.size, pkt.pts, (unsigned int)pkt.data);
                int av_result = avcodec_decode_video2(pVideoCodecCtx, pFrame, &got_picture, &pkt);
 
                if (av_result < 0)
                {
                    fprintf(stderr, "decode failed: inputbuf = 0x%x , input_framesize = %d\n", pkt.data, pkt.size);
                    return;
                }
#if 0
                if (got_picture)
                {
                    int bytes = avpicture_get_size(AV_PIX_FMT_RGB24, pVideoCodecCtx->width, pVideoCodecCtx->height);
                    buffer_rgb = (uint8_t *)av_malloc(bytes);
                    avpicture_fill((AVPicture *)pFrameRGB, buffer_rgb, AV_PIX_FMT_RGB24, pVideoCodecCtx->width, pVideoCodecCtx->height);
                    img_convert_ctx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height, pVideoCodecCtx->pix_fmt, pVideoCodecCtx->width, pVideoCodecCtx->height, AV_PIX_FMT_BGR24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
                    if (img_convert_ctx == NULL)
                    {
                        printf("can't init convert context!\n");
                        return;
                    }
                    sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pVideoCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
                    IplImage *pRgbImg = cvCreateImage(cvSize(pVideoCodecCtx->width, pVideoCodecCtx->height), 8, 3);
                    memcpy(pRgbImg->imageData, buffer_rgb, pVideoCodecCtx->width * 3 * pVideoCodecCtx->height);
                    Mat Img = cvarrToMat(pRgbImg, true);
                    DetectFace(Img);
                    cvReleaseImage(&pRgbImg);
                    sws_freeContext(img_convert_ctx);
                    av_free(buffer_rgb);
                }
#endif
            }
        } while (ret == AVERROR(EAGAIN));
        if (ret < 0) {
            printf("Could not read frame ---(error '%s')\n", av_make_error_string(errbuf, sizeof(errbuf), ret));
            goto EXIT;
        }
        av_packet_unref(&pkt);
    }
EXIT:
    if (NULL != ifmt_ctx) {
        avcodec_close(pVideoCodecCtx);
        avformat_close_input(&ifmt_ctx);
        av_free(pFrame);
        av_free(pFrameRGB);
        ifmt_ctx = NULL;
    }
    return;
}