#include <iostream>
#include "BmpFile.h"
#include "Pics2Pic.h"
Pics2Pic pic;
int main()
{
    int y,x;
    while(1)
    {
        cout <<"ÿһ����ͼ�Ŀ�(��):"<< endl;
        scanf("%d",&x);
        cout <<"�����ͼ�Ŀ�(��)[�����ܴ�,��֤��������ͼ��(��)�ı���]:"<< endl;
        scanf("%d",&y);
        pic=Pics2Pic(x,x,y,y);
        BmpImage bmp;
        char* path=(char*)"input.bmp";
        bmp.ReadPic(path);//����ͼ
        bmp.ReadPics(path);//����ͼ
        pic.CreatePicSrc();
        cout<<"����������!"<<endl;
        system("pause");
        system("cls");
    }
    return 0;
}
