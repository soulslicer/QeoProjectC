greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets
QT += network core

QEOHOME = $$(QEO_HOME)
isEmpty(QEOHOME) {
    error(\"QEO_HOME\" not set)
}

TEMPLATE = app

TARGET = sample-qwebview
PLATFORM = i686-linux

INCLUDEPATH += \
    $(QEO_HOME)/c/include \
    $(QEO_HOME)/c/platform/include

SOURCES += \
    src/main.cpp \
    src/qeowebviewjavascriptinterface.cpp \
    src/otcdialog.cpp

HEADERS += \
    src/qeowebviewjavascriptinterface.h \
    src/otcdialog.h

DEFINES += QT_NO_DEBUG_OUTPUT

QMAKE_CXXFLAGS += -m32
QMAKE_LFLAGS += -m32 -Wl,-rpath,$(QEO_HOME)/c/lib/$$PLATFORM

LIBS = -L$(QEO_HOME)/c/lib/$$PLATFORM -lqeo -lqeoutil

FORMS += res/otcdialog.ui

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()
