#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.setWindowTitle("图像可视化识别");
    w.setFixedSize(w.size());
    w.show();

    return a.exec();
}
