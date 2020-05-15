#ifndef BMPFILE_H_INCLUDED
#define BMPFILE_H_INCLUDED
#include <map>
#include <iostream>
#include <fstream>
#include <io.h>
#include <dir.h>
#include <windows.h>
#include <vector>
using namespace std;
class BmpImage
{
    friend class Pics2Pic;
public:
    typedef struct
    {
        int height;
        int width;
        unsigned char * imgData;
        int RGB[3];//颜色占比255
    } IMG;
    int color_table[6][6][6];
    BmpImage();
    void ReadPics(char* path);
    bool ReadPic(char* path);
    int ScanBmpColor(IMG* src);
    IMG* Read1Pic(FILE * PicFile);
    IMG* imgscale(IMG* bmpImg,double dy,double dx);
    void EnhanceColor(IMG* src,int RGB,int exp);
    bool StartCreatePic(IMG* bmpImg,char *path);
    int ColorWhich(IMG* bmpImg);
    int bi_search(const int arr[], int start, int last, int key);
    void InitColorTable();


#pragma pack(1)
    typedef struct
    {
        unsigned short bfType;  //文件标识符BM，0x424D 2bit
        unsigned long    Size;//文件的大小 4bit
        unsigned short    bfReserved1; //保留值,必须设置为0 2bit
        unsigned short    bfReserved2; //保留值,必须设置为0 2bit
        unsigned long    bfOffBits;//文件头的最后到图像数据位开始的偏移量 4bit
    } HEADER;

//位图信息头bi
    typedef struct
    {
        unsigned long  Size;//信息头的大小
        long   width;   //图像宽度
        long   height;   //图像高度
        unsigned short   biPlanes; //图像的位面数
        unsigned short   bits;//每个像素的位数
        unsigned long  biCompression;//压缩类型
        unsigned long  imagesize;//图像大小，字节
        long   biXPelsPerMeter; //水平分辨率
        long   biYPelsPerMeter; //垂直分辨率
        unsigned long   biClrUsed; //使用的色彩数
        unsigned long   biClrImportant;//重要的颜色数
    } INFOHEADER;

    typedef struct RGBQuad
    {
        unsigned char rgbBlue; //蓝色分量亮度
        unsigned char rgbGreen;//绿色分量亮度
        unsigned char rgbRed;//红色分量亮度
        unsigned char rgbReserved;
    } Quad;

#pragma pack()
};

#endif // BMPFILE_H_INCLUDED
