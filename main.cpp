#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "view/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;

    QString locale = QLocale::system().name();

    if (translator.load("://mandala_" + locale + ".qm") ||
        translator.load("://mandala_" + locale.left(2) + ".qm")) {
        app.installTranslator(&translator);
    }

    MainWindow window;
    window.show();

    return app.exec();
}
