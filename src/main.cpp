#include <QApplication>
#include <QIcon>
#include <QStyleFactory>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("KuGouConverter");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("KuGouConverter");

    app.setStyle(QStyleFactory::create("Fusion"));

    app.setWindowIcon(QIcon(":/resources/icons/app.png"));

    MainWindow w;
    w.show();

    return app.exec();
}
