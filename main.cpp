#include "mwgenwdata.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MWGenWData w;
    w.show();

    return a.exec();
}
