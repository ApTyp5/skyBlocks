#include "skyblockseditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkyBlocksEditor w;
    w.showMaximized();
    return a.exec();
}
