#include <QApplication>
#include "mainwindow.h"
#include "qlogging.h"

int main(int argc, char *argv[]) {
    qDebug() << "Now the program starts.";
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}