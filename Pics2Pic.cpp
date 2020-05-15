//
// Created by HASEE on 2020/5/5.
//
#include "Pics2Pic.h"
#include "BmpFile.h"
#include <malloc.h>
extern Pics2Pic pic;
extern BmpImage bmp;
Pics2Pic::Pics2Pic()
{
};
BmpImage::IMG* Pics2Pic::CreatePicSrc()
{
    int pics_num=PicHeight/PicsHeight;
    BmpImage::IMG *PicOut=(BmpImage::IMG *)malloc(sizeof(BmpImage::IMG));
    unsigned char* imgoutdata=(unsigned char*)malloc(3*sizeof(unsigned char)*PicHeight*PicWidth);
    //int RGB[3]= {0};
    for(int i=0; i<pics_num; i++)
    {
        for(int j=0; j<pics_num; j++)
        {
            /***/
            BmpImage::IMG img;
            //int rgb;
            unsigned char* imgdata=(unsigned char*)malloc(3*sizeof(unsigned char)*PicsHeight*PicsWidth);
            for(int k=0; k<PicsHeight; k++)
            {
                for(int l=0; l<PicsHeight; l++)
                {
                    imgdata[k*3*PicsHeight+l*3+0]= Pic.imgData[3*i*PicsHeight*PicWidth+j*3*PicsHeight+k*3*PicWidth+l*3+0];//£¿
                    imgdata[k*3*PicsHeight+l*3+1]= Pic.imgData[3*i*PicsHeight*PicWidth+j*3*PicsHeight+k*3*PicWidth+l*3+1];
                    imgdata[k*3*PicsHeight+l*3+2]= Pic.imgData[3*i*PicsHeight*PicWidth+j*3*PicsHeight+k*3*PicWidth+l*3+2];
                }
            }
            img.imgData=imgdata;
            img.height=PicsHeight;
            img.width=PicsWidth;
            bmp.ScanBmpColor(&img);
            //cout<<bmp.ColorWhich(&img)<<endl;
            if(pic.FindPicS(bmp.ColorWhich(&img))==NULL)
            {
                cout<<"err"<<endl;
                //return NULL;
            }
            BmpImage::IMG* imgsrc = pic.FindPicS(bmp.ColorWhich(&img));
            //cout<<bmp.ColorWhich(imgsrc)<<endl;
            free(imgdata);
            for(int k=0; k<PicsHeight; k++)
            {
                for(int l=0; l<PicsHeight; l++)
                {
                    //cout<<"?"<<endl;
                    imgoutdata[3*i*PicsHeight*PicWidth+j*3*PicsHeight+k*3*PicWidth+l*3+0]=imgsrc->imgData[k*3*PicsHeight+l*3+0];//£¿
                    imgoutdata[3*i*PicsHeight*PicWidth+j*3*PicsHeight+k*3*PicWidth+l*3+0]=imgsrc->imgData[k*3*PicsHeight+l*3+1];
                    imgoutdata[3*i*PicsHeight*PicWidth+j*3*PicsHeight+k*3*PicWidth+l*3+0]=imgsrc->imgData[k*3*PicsHeight+l*3+2];
                }
            }
        }
    }
    //printf("\n%d/%d/%d\n",RGB[2],RGB[1],RGB[0]);
    PicOut->imgData=imgoutdata;
    PicOut->height = PicHeight;
    PicOut->width = PicWidth;
    return PicOut;
};
void Pics2Pic::InitPics()
{
    for(int i=0; i<6*6*6; i++)
    {
        PicsSrc[i]= NULL;
    }
}

void Pics2Pic::AddPicsSrc(int key,BmpImage::IMG* src)
{
    PicsSrc[key]=src;
};
BmpImage::IMG* Pics2Pic::FindPicS(int key)
{
    if(PicsSrc[key]!=NULL)
    {
        return PicsSrc[key];
    }
    else
    {
        int k=key;
        int time=0;
        while(1)
        {
            time++;
            if(time==1)
            {
                for(int i=k+1; i<k+2&&i<6*6*6; i++)
                {
                    if(PicsSrc[i]!=NULL)
                    {
                        return PicsSrc[i];
                    }
                }
                for(int i=k-1; i>k-2&&i>=0; i--)
                {
                    if(PicsSrc[i]!=NULL)
                    {
                        return PicsSrc[i];
                    }
                }
            }
            //**********************
            k=key;
            k=k-1*time;
            for(int i=k-1; i>k-2&&i>=0&&k>=0&&k<6*6*6; i--)
            {
                if(PicsSrc[i]!=NULL)
                {
                    return PicsSrc[i];
                }
            }
            k=key;
            k=k+1*time;
            for(int i=k+1; i<k+2&&i<6*6*6&&k>=0&&k<6*6*6; i++)
            {
                if(PicsSrc[i]!=NULL)
                {
                    return PicsSrc[i];
                }
            }
        }
    }
    return NULL;
};

void Pics2Pic::AddPic(BmpImage::IMG * PIC)
{
    Pic.height=PIC->height;
    Pic.width=PIC->width;
    Pic.imgData=PIC->imgData;
    Pic.RGB[0]=PIC->RGB[0];
    Pic.RGB[1]=PIC->RGB[1];
    Pic.RGB[2]=PIC->RGB[2];
    free(PIC);
};
void Pics2Pic::PicSrcSize()
{
    int i=0;
    while(i++<216)
    {
        if(PicsSrc[i]!=NULL)
        {
            printf("%d|",i);
        }
    }
};
