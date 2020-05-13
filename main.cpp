#include <iostream>
#include "BmpFile.h"
#include "Pics2Pic.h"
Pics2Pic pic;
int main()
{
    int y,x;
    while(1)
    {
        cout <<"每一张子图的宽(高):"<< endl;
        scanf("%d",&x);
        cout <<"输出大图的宽(高)[尽可能大,保证是上面子图宽(高)的倍数]:"<< endl;
        scanf("%d",&y);
        pic=Pics2Pic(x,x,y,y);
        BmpImage bmp;
        char* path=(char*)"input.bmp";
        bmp.ReadPic(path);//读主图
        bmp.ReadPics(path);//读子图
        pic.CreatePicSrc();
        cout<<"本次输出完毕!"<<endl;
        system("pause");
        system("cls");
    }
    return 0;
}
