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
        int RGB[3];//��ɫռ��255
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
        unsigned short bfType;  //�ļ���ʶ��BM��0x424D 2bit
        unsigned long    Size;//�ļ��Ĵ�С 4bit
        unsigned short    bfReserved1; //����ֵ,��������Ϊ0 2bit
        unsigned short    bfReserved2; //����ֵ,��������Ϊ0 2bit
        unsigned long    bfOffBits;//�ļ�ͷ�����ͼ������λ��ʼ��ƫ���� 4bit
    } HEADER;

//λͼ��Ϣͷbi
    typedef struct
    {
        unsigned long  Size;//��Ϣͷ�Ĵ�С
        long   width;   //ͼ����
        long   height;   //ͼ��߶�
        unsigned short   biPlanes; //ͼ���λ����
        unsigned short   bits;//ÿ�����ص�λ��
        unsigned long  biCompression;//ѹ������
        unsigned long  imagesize;//ͼ���С���ֽ�
        long   biXPelsPerMeter; //ˮƽ�ֱ���
        long   biYPelsPerMeter; //��ֱ�ֱ���
        unsigned long   biClrUsed; //ʹ�õ�ɫ����
        unsigned long   biClrImportant;//��Ҫ����ɫ��
    } INFOHEADER;

    typedef struct RGBQuad
    {
        unsigned char rgbBlue; //��ɫ��������
        unsigned char rgbGreen;//��ɫ��������
        unsigned char rgbRed;//��ɫ��������
        unsigned char rgbReserved;
    } Quad;

#pragma pack()
};

#endif // BMPFILE_H_INCLUDED
