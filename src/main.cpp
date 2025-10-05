#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle(QObject::tr("Game of Life") + QString(
#ifdef DEBUG
                              " [Debug]"
#endif
                              ));
    window.show();

    return app.exec();
}
