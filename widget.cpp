#include "widget.h"
#include "ui_widget.h"
#include "analyse.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->start->setEnabled(false);
    ui->start_2->setEnabled(false);


    analyse1 = new analyse(this);
    connect(analyse1,&analyse::sendFile,this,&Widget::receFile);
    connect(analyse1,&analyse::snedPrint,this,&Widget::recePrint);
    connect(this,&Widget::IStart,analyse1,&analyse::IStart);
    qDebug() << QThread::currentThread();

    QPalette pe;
    QFont ft;
    ft.setPointSize(20);
    pe.setColor(QPalette::WindowText, Qt::red);
    ui->result->setPalette(pe);
    ui->result->setFont(ft);
}

Widget::~Widget()
{
    delete ui;
    delete analyse1;
}


void Widget::receFile()
{
   ui->yuangimage->setPixmap(QPixmap::fromImage(analyse1->File));
   ui->muimage->setPixmap(QPixmap::fromImage(analyse1->File1));
   ui->yaimage->setPixmap(QPixmap::fromImage(analyse1->File2));
   ui->analyse->setPixmap(QPixmap::fromImage(analyse1->File3));
   ui->start->setEnabled(true);
   ui->start_2->setEnabled(true);
   QString result = "识别结果: ";
   switch (analyse1->color) {
   case 1: result.append("红色的");break;
   case 2: result.append("绿色的");break;
   case 3: result.append("蓝色的");break;
   default:result.append("未知颜色的");break;
   }
   switch (analyse1->angle) {
   case 0:
   case 1:
        result.append("圆形");break;
   case 3:
       result.append("三角形");break;
   case 5:
       result.append("五角形");break;
   case 4:
       result.append("矩形");break;
   default:
       result.append("未知形状");break;
   }
   ui->result->setText(result);
}

void Widget::recePrint()
{
    ui->textBrowser->append(analyse1->PrintBuf);
    analyse1->PrintLook = 0;
}






void Widget::on_openfile_clicked()
{
    analyse1->FileAddr = QFileDialog::getOpenFileName(nullptr,tr("打开源图像"),qApp->applicationDirPath()+"/test",tr("*.png"));
    ui->lineEdit->setText(analyse1->FileAddr);
    emit IStart();
}



void Widget::on_start_2_clicked()
{
    emit IStart();
}
