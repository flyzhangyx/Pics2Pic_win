#include "BmpFile.h"
#include "Pics2Pic.h"
Pics2Pic pic;
BmpImage bmp;
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
        pic.InitPics();
        char* path=(char*)"in/input.bmp";
        bmp.InitColorTable();
        if(!bmp.ReadPic(path))
        {
            system("cls");
            cout<<"��ͼ��ȡ����"<<endl;
            cout<<"�뽫��ͼ����Ϊ<input.bmp>,����<JPG>��������ʽ����ʹ��ϵͳ��ͼ�������ʽתΪ<BMP>"<<endl;
            system("pause");
            system("cls");
            continue;
        }//����ͼ
        bmp.ReadPics(path);//����ͼ
        pic.PicSrcSize();
        BmpImage::IMG* out=pic.CreatePicSrc();
        bmp.StartCreatePic(out,(char*)"out/out.bmp");
        free(out);
        cout<<"����������!"<<endl;
        system("pause");
        system("cls");
    }
    return 0;
}
