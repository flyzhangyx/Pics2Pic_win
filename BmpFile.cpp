//
// Created by HASEE on 2020/5/5.
//

#include "BmpFile.h"
#include "Pics2Pic.h"
#include <malloc.h>
#include <string.h>
extern Pics2Pic pic;
extern BmpImage bmp;
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
            if((int)src->imgData[3*i*src->height+3*j+RGB]<255-exp&&(int)src->imgData[3*i*src->height+3*j+RGB]>-1*exp)
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
                    if((int)src->imgData[3*i*src->height+3*j+RGB]<255-exp&&(int)src->imgData[3*i*src->height+3*j+RGB]>-1*exp)
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
    //printf("\nR:%3.0f,G:%3.0f,B:%3.0f\n",RGB[2],RGB[1],RGB[0]);
    key=RGB[2]>=RGB[1]?(RGB[2]>RGB[0]?2:0):(RGB[1]>=RGB[0]?1:0);
    //Update RGB INFO
    src->RGB[0]=RGB[0];
    src->RGB[1]=RGB[1];
    src->RGB[2]=RGB[2];
    //printf("\nColor Num :%d\n",ColorWhich(src));
    return key;
};
void BmpImage::InitColorTable(){
    int color_num=0;
    for(int i1=0;i1<12;i1++)//init
    {
        for(int i2=0;i2<12;i2++)
        {
            for(int i3=0;i3<12;i3++)
            {
                color_table[i1][i2][i3]=color_num;
                color_num++;
            }
        }
    }
}
int BmpImage::ColorWhich(IMG* bmpImg)
{
    //共6*6*6种颜色
    int RGB[13]= {0/*1*/,21/*2*/,42,63,84,105,126,147,168,189,210,231,255};
    /*if(bmpImg->RGB[2]>255)
    {
        cout<<bmpImg->RGB[2]<<endl;
    }
    if(bmpImg->RGB[1]>255)
    {src->
        cout<<bmpImg->RGB[1]<<endl;
    }
    if(bmpImg->RGB[0]>255)
    {src->
        cout<<bmpImg->RGB[0]<<endl;
    }*/
    return color_table[bi_search(RGB,0,12,bmpImg->RGB[2])-1][bi_search(RGB,0,12,bmpImg->RGB[1])-1][bi_search(RGB,0,12,bmpImg->RGB[0])-1];
};
int BmpImage::bi_search(const int arr[], int start, int last, int key)
{
    if(key==0)
    {
        key++;
    }
    if (start > last)
        return start;
    int mid = start + (last - start) / 2;    //直接平均可能會溢位，所以用此算法
    if (arr[mid] > key)
        return bi_search(arr, start, mid - 1, key);
    else if (arr[mid] < key)
        return bi_search(arr, mid + 1, last, key);
    else
        return mid;        //最後檢測相等是因為多數搜尋狀況不是大於要不就小於
}
void BmpImage::ReadPics(char* path)
{
    long handle;
    const char *to_search="*.bmp";                                          //用于查找的句柄
    struct _finddata_t fileinfo;                                     //文件信息的结构体
    handle =_findfirst(to_search,&fileinfo);                          //第一次查找
    if(-1==handle)
    {
        return ;
    }
    else
    {
        FILE* PicFile;
        PicFile=fopen(fileinfo.name,"rb");
        if(PicFile==NULL)
        {
            cout<<"Can`t open :";
            cout<<fileinfo.name<<endl;
        }
        else
        {
            IMG* imgSrcData = Read1Pic(PicFile);
            fclose(PicFile);
            /***/
            char *path1=(char*)malloc(strlen(fileinfo.name)*2*sizeof(char));
            memset(path1,0,strlen(fileinfo.name)*2*sizeof(char));
            strcpy(path1,"out/");
            strcat(path1,fileinfo.name);
            /***/
            cout<<fileinfo.name;
            cout<<":";
            double y_scale= (double)pic.PicsHeight/imgSrcData->height;
            double x_scale= (double)pic.PicsWidth/imgSrcData->width;
            IMG* img=imgscale(imgSrcData,x_scale,y_scale);//Already malloc
            EnhanceColor(img,ScanBmpColor(img),30);
            /***/
            StartCreatePic(img,path1);
            free(path1);
            /***/
            cout<<ColorWhich(img)<<endl;
            pic.AddPicsSrc(ColorWhich(img),img);
        }
    }
    while(!_findnext(handle,&fileinfo))                              //循环查找其他符合的文件，直到找不到其他的为止
    {
        FILE* PicFile;
        PicFile=fopen(fileinfo.name,"rb");
        if(PicFile==NULL)
        {
            cout<<"Can`t open :";
            cout<<fileinfo.name<<endl;
        }
        else
        {
            IMG* imgSrcData = Read1Pic(PicFile);
            fclose(PicFile);
            /***/
            char *path1=(char*)malloc(strlen(fileinfo.name)*2*sizeof(char));
            memset(path1,0,strlen(fileinfo.name)*2*sizeof(char));
            strcpy(path1,"out/");
            strcat(path1,fileinfo.name);
            /***/
            cout<<fileinfo.name;
            cout<<":";
            double y_scale= (double)pic.PicsHeight/imgSrcData->height;
            double x_scale= (double)pic.PicsWidth/imgSrcData->width;
            IMG* img=imgscale(imgSrcData,x_scale,y_scale);
            EnhanceColor(img,ScanBmpColor(img),30);
            /***/
            StartCreatePic(img,path1);
            free(path1);
            /***/
            cout<<ColorWhich(img)<<endl;
            pic.AddPicsSrc(ColorWhich(img),img);
        }
    }
    _findclose(handle);                                              //关闭句柄
    printf("\nPics Read All Down\n");
};

BmpImage::IMG* BmpImage::Read1Pic(FILE * PicFile)
{
    int offset=0;
    HEADER header;
    INFOHEADER infoheader;
    unsigned char point;
    if(PicFile==NULL)
    {
        cout<<"ERROR WHEN OPEN (Read1Pic)\n"<<endl;
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
bool BmpImage::ReadPic(char *path)
{
    FILE* PicFile;
    PicFile=fopen(path,"rb");
    if(PicFile==NULL)
    {
        return false;
    }
    else
    {
        IMG* imgSrcData = Read1Pic(PicFile);
        fclose(PicFile);
        double y_scale= (double)pic.PicHeight/imgSrcData->height;
        double x_scale= (double)pic.PicWidth/imgSrcData->width;
        IMG* img=imgscale(imgSrcData,x_scale,y_scale);
        pic.AddPic(img);
    }
    return true;
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
bool BmpImage::StartCreatePic(IMG* bmpImg,char *path)
{
    FILE *PicFile;
    HEADER bmpFileHeader;
    INFOHEADER bmpInfoHeader;
    int width = 0;
    int height = 0;
    int step = 0;
    int channels = 1;
    int i, j;
    int offset;
    unsigned char point = '\0';
    width = bmpImg->width;
    height = bmpImg->height;
    channels = 3;
    step = width * channels;
    PicFile = fopen(path, "wb");
    if (!PicFile)
    {
        return false;
    }
    bmpFileHeader.bfType = 0x4D42;//BM
    //Byte Fill
    offset = step%4;
    if (offset != 0)
    {
        offset=4-offset;
        step += 4-offset;
    }
    bmpFileHeader.Size = height*step + 54;
    bmpFileHeader.bfReserved1 = 0;
    bmpFileHeader.bfReserved2 = 0;
    bmpFileHeader.bfOffBits = 54;
    fwrite(&bmpFileHeader, sizeof(HEADER), 1, PicFile);
    bmpInfoHeader.Size = 40;
    bmpInfoHeader.width = width;
    bmpInfoHeader.height = height;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.bits = 24;
    bmpInfoHeader.biCompression = 0;
    bmpInfoHeader.imagesize = height*step;
    bmpInfoHeader.biXPelsPerMeter = 0;
    bmpInfoHeader.biYPelsPerMeter = 0;
    bmpInfoHeader.biClrUsed = 0;
    bmpInfoHeader.biClrImportant = 0;
    fwrite(&bmpInfoHeader, sizeof(INFOHEADER), 1, PicFile);
    for (i=bmpImg->height-1; i>-1; i--)
    {
        for (j=0; j<bmpImg->width; j++)
        {
            point = bmpImg->imgData[i*width*3+j*3+0];
            fwrite(&point, sizeof(unsigned char), 1, PicFile);
            point = bmpImg->imgData[i*width*3+j*3+1];
            fwrite(&point, sizeof(unsigned char), 1, PicFile);
            point = bmpImg->imgData[i*width*3+j*3+2];
            fwrite(&point, sizeof(unsigned char), 1, PicFile);
        }
        if (offset!=0)
        {
            for (j=0; j<offset; j++)
            {
                point = 0;
                fwrite(&point, sizeof(unsigned char), 1, PicFile);
            }
        }
    }
    fclose(PicFile);
    return true;
};
