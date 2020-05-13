//
// Created by HASEE on 2020/5/5.
//

#include "BmpFile.h"
#include "Pics2Pic.h"
#include <malloc.h>
extern Pics2Pic pic;
BmpImage::BmpImage()
{
};
void BmpImage::EnhanceColor(IMG* src,int RGB,int exp)
{
    //RGB:2/1/0
    int time=0;
    for(int i=0; i<src->height; i++)
        for(int j=0; j<src->width; j++)
        {
            if((int)src->imgData[3*i*src->height+3*j+RGB]<255-exp)
            {
                src->imgData[3*i*src->height+3*j+RGB]=src->imgData[3*i*src->height+3*j+RGB]+exp;
            }
            else
            {
                while(1)
                {
                    time++;
                    exp=exp/2;
                    if(time==8)
                    {
                        time=0;
                        break;
                    }
                    if((int)src->imgData[3*i*src->height+3*j+RGB]<255-exp)
                    {
                        src->imgData[3*i*src->height+3*j+RGB]=src->imgData[3*i*src->height+3*j+RGB]+exp;
                        break;
                    }
                }
            }
        }
};
int BmpImage::ScanBmpColor(IMG* src)
{
    int key;
    double RGB[3]= {0,0,0};
    for(int i=0; i<src->height; i++)
        for(int j=0; j<src->width; j++)
        {
            RGB[0]+=((double)src->imgData[3*i*src->height+3*j+0]);
            RGB[1]+=((double)src->imgData[3*i*src->height+3*j+1]);
            RGB[2]+=((double)src->imgData[3*i*src->height+3*j+2]);
        }
    //归一化
    RGB[0]/=src->height*src->width;
    RGB[1]/=src->height*src->width;
    RGB[2]/=src->height*src->width;
    printf("R:%3.0f,G:%3.0f,B:%3.0f\n",RGB[2],RGB[1],RGB[0]);
    key=RGB[2]>=RGB[1]?(RGB[2]>RGB[0]?2:0):(RGB[1]>=RGB[0]?1:0);
    //Update RGB INFO
    src->RGB[0]=RGB[0];
    src->RGB[1]=RGB[1];
    src->RGB[2]=RGB[2];
    return key;
};

void BmpImage::ReadPics(char* path)
{
    long handle;
    const char *to_search="*.bmp";                                          //用于查找的句柄
    struct _finddata_t fileinfo;                                     //文件信息的结构体
    handle=_findfirst(to_search,&fileinfo);                          //第一次查找
    if(-1==handle)
    {
        return ;
    }
    else
    {
        FILE* PicFile;
        PicFile=fopen(fileinfo.name,"rb");
        IMG* imgSrcData = Read1Pic(PicFile);
        fclose(PicFile);
        double y_scale= (double)pic.PicsHeight/imgSrcData->height;
        double x_scale= (double)pic.PicsWidth/imgSrcData->width;
        IMG* img=imgscale(imgSrcData,x_scale,y_scale);
        EnhanceColor(img,ScanBmpColor(img),50);
        //pic.StartCreatePic(img);
        pic.AddPicsSrc(img,ScanBmpColor(img));
    }
    while(!_findnext(handle,&fileinfo))                              //循环查找其他符合的文件，直到找不到其他的为止
    {
        FILE* PicFile;
        PicFile=fopen(fileinfo.name,"rb");
        IMG* imgSrcData = Read1Pic(PicFile);
        fclose(PicFile);
        double y_scale= (double)pic.PicsHeight/imgSrcData->height;
        double x_scale= (double)pic.PicsWidth/imgSrcData->width;
        IMG* img=imgscale(imgSrcData,x_scale,y_scale);
        EnhanceColor(img,ScanBmpColor(img),50);
        ScanBmpColor(img);
        //pic.StartCreatePic(img);
        pic.AddPicsSrc(img,ScanBmpColor(img));
    }
    _findclose(handle);                                              //关闭句柄
    printf("All Done.\n");
};

BmpImage::IMG* BmpImage::Read1Pic(FILE * PicFile)
{
    int offset=0;
    HEADER header;
    INFOHEADER infoheader;
    unsigned char point;
    if(PicFile==NULL)
    {
        cout<<"ERROR WHEN OPEN\n"<<endl;
        return 0;
    }
    fread(&header,14L,1,PicFile);
    fread(&infoheader,40L,1,PicFile);
    IMG* img=(IMG *)malloc(sizeof(IMG));
    unsigned char * imgData=(unsigned char*)malloc(sizeof(unsigned char)*infoheader.width*3*infoheader.height);
    offset = (3*infoheader.width)%4;
    if(offset != 0)
    {
        offset = 4 - offset;
    }
    for (int i=0; i<infoheader.height; i++)
    {
        for (int j=0; j<infoheader.width; j++)
        {
            for (int k=0; k<3; k++)
            {
                fread(&point, sizeof(unsigned char), 1, PicFile);
                imgData[(infoheader.height-1-i)*3*infoheader.width+j*3+k] = point;
            }
        }
        if (offset != 0)
        {
            for (int j=0; j<offset; j++)
            {
                fread(&point, sizeof(unsigned char), 1, PicFile);
            }
        }
    }
    img->height=infoheader.height;
    img->width=infoheader.width;
    img->imgData=imgData;
    return img;
};
void BmpImage::ReadPic(char *path)
{
    FILE* PicFile;
    PicFile=fopen(path,"rb");
    IMG* imgSrcData = Read1Pic(PicFile);
    fclose(PicFile);
    pic.AddPic(imgSrcData);
};
BmpImage::IMG* BmpImage::imgscale(IMG* bmpImg,double dy,double dx)
{
    //图片缩放处理
    IMG* bmpImgSca;
    int width = 0;
    int height = 0;
    int channels = 3;
    int step = 0;
    int Sca_step = 0;
    int i, j, k;
    width = bmpImg->width;
    height = bmpImg->height;
    int pre_i,pre_j,after_i,after_j;//缩放前对应的像素点坐标
    //初始化缩放后图片的信息
    bmpImgSca = (IMG*)malloc(sizeof(IMG));
    bmpImgSca->width = (int)(bmpImg->width*dy + 0.5);
    bmpImgSca->height = (int)(bmpImg->height*dx + 0.5);
    step = channels * width;
    Sca_step = channels * bmpImgSca->width;
    bmpImgSca->imgData = (unsigned char*)malloc(sizeof(unsigned char)*bmpImgSca->width*bmpImgSca->height*channels);
    //初始化缩放图像
    for(i=0; i<bmpImgSca->height; i++)
    {
        for(j=0; j<bmpImgSca->width; j++)
        {
            for(k=0; k<3; k++)
            {
                bmpImgSca->imgData[(bmpImgSca->height-1-i)*Sca_step+j*3+k] = 0;
            }
        }
    }
    //坐标变换
    for(i = 0; i < bmpImgSca->height; i++)
    {
        for(j = 0; j < bmpImgSca->width; j++)
        {
            after_i = i;
            after_j = j;
            pre_i = (int)(after_i / dx + 0.5);
            pre_j = (int)(after_j / dy + 0.5);
            if(pre_i >= 0 && pre_i < height && pre_j >= 0 && pre_j < width)//在原图范围内
                for(k=0; k<3; k++)
                {
                    bmpImgSca->imgData[i * Sca_step + j*3 +k] = bmpImg->imgData[pre_i * step + pre_j*3 + k];
                }
        }
    }
    free(bmpImg);
    return bmpImgSca;
};
