#include "BmpFile.h"
#include "Pics2Pic.h"
Pics2Pic pic;
BmpImage bmp;
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
        pic.InitPics();
        char* path=(char*)"in/input.bmp";
        bmp.InitColorTable();
        if(!bmp.ReadPic(path))
        {
            system("cls");
            cout<<"主图读取错误"<<endl;
            cout<<"请将主图改名为<input.bmp>,若是<JPG>等其他格式，请使用系统绘图软件将格式转为<BMP>"<<endl;
            system("pause");
            system("cls");
            continue;
        }//读主图
        bmp.ReadPics(path);//读子图
        pic.PicSrcSize();
        BmpImage::IMG* out=pic.CreatePicSrc();
        bmp.StartCreatePic(out,(char*)"out/out.bmp");
        free(out);
        cout<<"本次输出完毕!"<<endl;
        system("pause");
        system("cls");
    }
    return 0;
}
