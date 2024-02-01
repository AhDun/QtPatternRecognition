#ifndef WIDGET_H
#define WIDGET_H

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
#include "analyse.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void IStart();


private slots:
    void receFile();
    void recePrint();

    void on_openfile_clicked();


    void on_start_2_clicked();

private:
    Ui::Widget *ui;
    analyse *analyse1;

};

#endif // WIDGET_H
