#ifndef ANALYSE_H
#define ANALYSE_H


#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QIODevice>
#include <QDebug>
#include <QColor>
#include <QStringList>
#include <stdio.h>
#include <QTime>
#include <QThread>
#include <QObject>
#include <math.h>


class analyse : public QThread
{
    Q_OBJECT
public:
    analyse(QObject *parent = 0);

public:
    void Iamge();
    int channel(int h,int s,int l);
    void Value2Init();
    void Value2Write(int x,int y,bool v);
    bool Value2Read(int x,int y);
    void print(int x);
    char* printBuf();

    QImage File;
    QImage File1;
    QImage File2;
    QImage File3;
    QString FileAddr;

    char Value2[320*240/8];
    char PrintBuf[500];
    bool PrintLook;
    bool IamgeLook;
    int angle;
    int color;

signals:
    void sendFile();
    void snedPrint();

public slots:
    void IStart();

protected:
    void run();

};

#endif // ANALYSE_H
