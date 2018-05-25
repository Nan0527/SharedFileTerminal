#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 分页组件的css,这个内容应该放到普通文件中然后加载
    QString qss = QString(".QLabel[page=\"true\"] { padding: 1px; }")
            + QString(".QLabel[currentPage=\"true\"] { color: rgb(190, 0, 0);}")
            + QString(".QLabel[page=\"true\"]:hover { color: white; border-radius: 4px; background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(53, 121, 238, 255), stop:1 rgba(0, 202, 237, 255));}");
    a.setStyleSheet(qss);

    MainWindow w;
    w.show();
    w.setWindowTitle("共享档案终端");
//    w.setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);//隐藏边框并置顶
 //    w.setFixedSize(600, 400);//设置初始化的比例
//    w.showMaximized();//初始化时最大化

    return a.exec();
}
