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
    Pics2Pic(int picsWidth,int picsHeight,int picWidth,int picHeight):PicsWidth(picsWidth),PicWidth(picWidth),PicsHeight(picsHeight),PicHeight(picHeight) {}; //��ʼ������ͼ����Դ�����ͼ��ĳߴ��С
    void AddPicsSrc(BmpImage::IMG*,int);
    void AddPic(BmpImage::IMG*);
    BmpImage::IMG* CreatePicSrc();
    bool StartCreatePic(BmpImage::IMG*);
    int PicsWidth,PicsHeight;
    int PicWidth,PicHeight;
private:
    map<BmpImage::IMG* ,int> PicsSrc;
    BmpImage::IMG Pic;
};


#endif // PICS2PIC_H_INCLUDED
