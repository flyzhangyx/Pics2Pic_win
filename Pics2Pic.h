#ifndef PICS2PIC_H_INCLUDED
#define PICS2PIC_H_INCLUDED
#include <map>
#include <iostream>
#include <fstream>
#include <io.h>
#include <dir.h>
#include <windows.h>
#include <vector>
using namespace std;
#include "BmpFile.h"
class Pics2Pic
{
public:
    Pics2Pic();
    Pics2Pic(int picsWidth,int picsHeight,int picWidth,int picHeight):PicsWidth(picsWidth),PicsHeight(picsHeight),PicWidth(picWidth),PicHeight(picHeight){} ; //初始化输入图像资源与输出图像的尺寸大小
    ~Pics2Pic(){};
    void AddPicsSrc(int,BmpImage::IMG*);
    void AddPic(BmpImage::IMG*);
    BmpImage::IMG* CreatePicSrc();
    bool StartCreatePic(BmpImage::IMG*,char *);
    void PicSrcSize();
    BmpImage::IMG* FindPicS(int key);
    void InitPics();
    int PicsWidth,PicsHeight;
    int PicWidth,PicHeight;
private:
    BmpImage::IMG Pic;
    BmpImage::IMG* PicsSrc[6*6*6];
};

#endif // PICS2PIC_H_INCLUDED
