#include <QApplication>
#include <QDebug>
#include "settingwindow.h"
#include "setting.h"
#include "webenginewrapper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Setting s;
    if (s.isEmpty() || argc != 1)
    {
        MainWindow main;
        main.show();
        a.exec();
    }
    WebEngineWrapper danmu(&a);
    danmu.display();
    return a.exec();
}
