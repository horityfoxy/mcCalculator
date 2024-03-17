#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Calculator");

    QString mediumFont = "assets/fonts/Inter-Medium.ttf";

    int basicFont = QFontDatabase::addApplicationFont(mediumFont);

    QString fontName = QFontDatabase::applicationFontFamilies(basicFont).at(0);
    QApplication::setFont(QFont(fontName));

    w.show();
    return a.exec();
}
