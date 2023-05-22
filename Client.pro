QT          += core gui network
LIBS        += -lgmp
INCLUDEPATH += /usr/include src include forms

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# We only need to build the .cpp files
# the rest can be deleted at the end of the project

SOURCES_DIR = src
HEADERS_DIR = include
FORMS_DIR   = forms

SOURCES += $$files($$SOURCES_DIR/*.cpp) main.cpp
HEADERS += $$files($$HEADERS_DIR/*.hpp)
FORMS   += $$files($$FORMS_DIR/*.ui)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resource.qrc
