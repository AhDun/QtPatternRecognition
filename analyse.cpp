#include "analyse.h"

analyse::analyse(QObject *parent) : QThread(parent)
{


}

void analyse::run()
{
//    while(1){
//        IamgeH(FileAddr);
//        emit sendFile();
//        IamgeLook = 1;
//        while(IamgeLook);
//    }
}

int analyse::channel(int h, int s, int l)
{
    if(h > 240 || h < 20){
        if(s > 100 && l >  100){
            return 1;
        }
    }
    else if(h > 240 || h < 20){
        if(s > 100 && l >  100){
            return 2;
        }
    }
    else if(h > 240 || h < 20){
        if(s > 100 && l >  100){
            return 3;
        }
    }
    return 0;
}
void analyse::Value2Write(int x, int y, bool v)
{
    if (v) {
        Value2[(x * 40) + (y / 8)] |= (0x80 >> (y % 8));
    }
    else {
        Value2[(x * 40) + (y / 8)] &= ~(0x80 >> (y % 8));
    }
}
bool analyse::Value2Read(int x, int y)
{
    if (Value2[(x * 40) + (y / 8)] & (0x80 >> (y % 8))) {
        return 1;
    }
    else {
        return 0;
    }
}

void analyse::Value2Init()
{
    for(int x = 0; x < 240; x++){
        for(int y = 0; y < 320 ; y++){
            Value2Write(x,y,0);
        }
    }
}
void analyse::Iamge()
{
    File = QImage(FileAddr);
    File1 = QImage(":/new/prefix1/qrc/void.jpg");
    File2 = QImage(":/new/prefix1/qrc/void.jpg");
    File3 = QImage(":/new/prefix1/qrc/void.jpg");

    int h,s,l;
    int r=0,g=0,b=0;
    bool along = 0;
    bool alongLock = 1;
    bool Lock = 0;
    bool All[361];
    int XMax = 0,XMin = 320;
    int YMax = 0,YMin = 320;
    Value2Init();
    print(sprintf(printBuf(),"开始处理"));

    for(int y = 0; y < 240; y++){
        for(int x = 0 ; x < 320; x++){
            File.pixelColor(x,y).getHsl(&h,&s,&l);
            switch(channel(h,s,l)){
                case 1:r++;break;
                case 2:g++;break;
                case 3:b++;break;
            }

        }
    }
    if(r > g && r > b){
          color = 1;
    }
    else if(g > r && g > b){
          color = 2;
    }
    else if(b > g && b > r){
          color = 3;
    }else{
        color = 0;
    }


    for(int y = 0; y < 240; y++){
        for(int x = 0 ; x < 320; x++){
            File.pixelColor(x,y).getHsl(&h,&s,&l);
            if(channel(h,s,l) == color){
                File1.setPixelColor(x,y,QColor::fromHsl(h,s,l));
                Value2Write(y,x,1);
                if(XMin > x){
                    XMin = x;
                }
                if(x > XMax){
                    XMax = x;
                    //File2.setPixelColor(x,y,QColor::fromHsl(h,s,l));
                }
                if(YMin > y){
                    YMin = y;
                }
                if(y > YMax){
                    YMax = y;
                    //File2.setPixelColor(x,y,QColor::fromHsl(h,s,l));
                }
            }else{
                Value2Write(y,x,0);
            }
            if(Value2Read(y,x)){
                File2.setPixel(x,y,0x00000000);
                File3.setPixelColor(x,y,QColor::fromHsl(h,s,l));
            }else{
                File2.setPixel(x,y,0xFFFFFFFF);
            }

        }
    }
    print(sprintf(printBuf(),"XMax:%d XMax:%d",XMax,XMin));
    print(sprintf(printBuf(),"YMax:%d YMax:%d",YMax,YMin));
    int cr,cx,cy;
    if(XMax - XMin > YMax - YMin){
        cr = (YMax - YMin)/2.5;
    }else{
        cr = (XMax - XMin)/2.5;
    }
    cx = XMin + (XMax - XMin)/2;
    cy = YMin + (YMax - YMin)/2;
    print(sprintf(printBuf(),"r:%d x:%d y:%d",cr,cx,cy));
    for(int i = 0;i <= 360;i++){
        int x = cr*cos(i*M_PI / 180) + cx;
        int y = cr*sin(i*M_PI / 180) + cy;

        if(Value2Read(y,x)){
            //File3.setPixel(x,y,0x00000000);
            All[i] = 1;

        }else{
            File3.setPixel(x,y,0x00000000);
            All[i] = 0;
        }

    }
    int i = 0;
    angle = 0;
    while(1){
        if(All[i] == 1){
            if(along == 0){
                if(alongLock == 0){
                    angle++;
                    alongLock = 1;
                    print(sprintf(printBuf(),"在%d度方向，有一个角",i));
                }
            }
            along = 1;

        }else{
            if(Lock == 1){
                break;
            }else{
                if(along == 1){
                  alongLock = 0;
                }
                along = 0;
            }
        }
        i++;
        if(i >= 360){
            i = 0;
            if(Lock == 1){
                break;
            }
            Lock = 1;
        }
    }
    print(sprintf(printBuf(),"完成处理"));
}
char* analyse::printBuf()
{
    for(int i = 0; i < 500;i++){
        PrintBuf[i] = 0;
    }
    return &PrintBuf[0];
}
void analyse::print(int x)
{
    PrintLook = 1;
    emit snedPrint();
    while(PrintLook);
}
void analyse::IStart()
{
    Iamge();
    emit sendFile();
    qDebug() << "OK";
}




