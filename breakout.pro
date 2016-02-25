SOURCES += \
    main.cpp \
    glwidget.cpp \
    brick.cpp

HEADERS += \
    glwidget.h \
    brick.h

RESOURCES += \
    imagens.qrc

QT += opengl

QT += widgets

QT += core gui

LIBS += -L"C:\\Qt\\Qt5.1.1\\5.1.1\\mingw48_32\\lib"/ libglew32
