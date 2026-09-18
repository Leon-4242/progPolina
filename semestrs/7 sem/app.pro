QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -W -Wall -Werror -Wfloat-equal -Wunused -Wnon-virtual-dtor -isystem $$[QT_INSTALL_HEADERS]

OBJECTS_DIR = build/obj
MOC_DIR     = build/moc
DESTDIR     = build/bin

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -g
}

CONFIG(release, debug|release) {
    DEFINES += NDEBUG
    QMAKE_CXXFLAGS += -O2
}

CORE_H =  
CORE_S = main.cpp

GUI_H = 
GUI_S = 

HEADERS += \
		$$CORE_H \
		$$GUI_H \

SOURCES += \
		$$CORE_S\
		$$GUI_H
