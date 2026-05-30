#include "ui/mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile qssFile(":/style.qss");

    if (qssFile.open(QFile::ReadOnly)) {
        const QString stylesheet = QLatin1String(qssFile.readAll());
        app.setStyleSheet(stylesheet);
        qssFile.close();
    } else {
        qWarning() << "Failed to load qss file!";
    }

    MainWindow w;
    w.show();

    return QApplication::exec();
}