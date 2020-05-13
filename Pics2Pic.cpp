//
// Created by HASEE on 2020/5/5.
//
#include "Pics2Pic.h"
#include "BmpFile.h"
extern Pics2Pic pic;
Pics2Pic::Pics2Pic()
{
};
void Pics2Pic::AddPicsSrc(BmpImage::IMG* src,int key)
{
    PicsSrc.insert(pair<BmpImage::IMG*, int>(src, key));
};
BmpImage::IMG* Pics2Pic::CreatePicSrc(){
    cout<<Pic.height<<endl;
};
void Pics2Pic::AddPic(BmpImage::IMG * PIC)
{
    Pic.height=PIC->height;
    Pic.width=PIC->width;
    Pic.imgData=PIC->imgData;
    Pic.RGB[0]=PIC->RGB[0];
    Pic.RGB[1]=PIC->RGB[1];
    Pic.RGB[2]=PIC->RGB[2];
};
bool Pics2Pic::StartCreatePic(BmpImage::IMG* bmpImg)
{
    FILE *PicFile;
    BmpImage::HEADER bmpFileHeader;
    BmpImage::INFOHEADER bmpInfoHeader;
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
    PicFile = fopen("out/out.bmp", "wb");
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
    fwrite(&bmpFileHeader, sizeof(BmpImage::HEADER), 1, PicFile);
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
    fwrite(&bmpInfoHeader, sizeof(BmpImage::INFOHEADER), 1, PicFile);
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
}
