#include <QApplication>
#include "glwidget.h"
#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    GLWidget gl_widget;
    gl_widget.setWindowTitle("Breakout");
    gl_widget.setMaximumSize(960, 600);
    gl_widget.setMinimumSize(960, 600);
    gl_widget.show();

    return app.exec();
}
