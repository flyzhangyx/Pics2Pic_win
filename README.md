# Pics2Pic_win
有几张子图与一张目标图，子图作为源然后拼接生成目标图的由子图拼接而成的图
类似上海失恋博物馆中巨幅女主像：网页原文描述：
这张照片上的是一个有1000多张女孩子的自拍照，而拼接成了一个肖像画。男孩和女孩非常的相爱，他们也坚信自己是能够走到婚姻的殿堂，但是在相处的过程中，男孩子居然对女孩子家暴了，女孩子受不了，最后两个人分手收场。


###
程序运行：[子图]放在跟程序同一级目录下，然后在该目录下新建名为‘in’的文件夹并将要输出的图片[样图]放在里面，同时新建一个‘out’文件夹等待程序生成图片放入
###
Warning：①[子图]与要输出的[样图]需要是‘BMP’格式，建议使用格式工厂批量生成
         ②程序运行后，输入两次数据，第一次是[子图]需要格式化的大小，建议小一点，500以内，100最好。第二次输入是[样图]的格式化输出大小，必须是前面输入的倍数，比如:100/10000。
         ③建议上面第二次输入的数据值小于13000（本来在前面的版本中可以随意，只要你内存够大，但是后面更改了逻辑之后出现FC，也就懒得改了//‘我编译器mingw32，malloc不能太大超过32位限制，改成64位编译器build就行：https://www.cnblogs.com/lexyao/p/11629467.html’
         ⑤建议[子图]尽可能的多，尽可能的让它们的RGB分散，才能让原图更加鲜活。
由下面的几张图生成最后的图：

1：目标图：

![目标图.jpg](http://pic.flyzhangyx.com/input.bmp)

2：源子图：

![1.jpg](http://pic.flyzhangyx.com/IMG_20200310_153914~1.bmp) ![2.jpg](http://pic.flyzhangyx.com/hdImg_6a2001b3089c3c52cb6918cd142252bb15848601546.bmp) ![3.jpg](http://pic.flyzhangyx.com/https___img01_sogoucdn_com_app_a_200678_148163351.bmp) ![4.jpg](http://pic.flyzhangyx.com/psbe.bmp) ![5.jpg](http://pic.flyzhangyx.com/psbe%20%281%29.bmp)

3：效果图：

![out.jpg](http://pic.flyzhangyx.com/out.jpg)

原图地址：http://flyzhangyx.com/out.bmp  (图片比较大，个人站点，下载较慢)
