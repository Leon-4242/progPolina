QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS += -W -Wall -Werror -Wfloat-equal -Wunused -Wnon-virtual-dtor -isystem $$[QT_INSTALL_HEADERS]

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -g
}

CONFIG(release, debug|release) {
    DEFINES += NDEBUG
    QMAKE_CXXFLAGS += -O2
}

HEADERS = common_defs.h graph_widget.h \
    function_2d.h \
    Newton_interpolation_function_2d.h
SOURCES = main.cpp graph_widget.cpp \
    function_2d.cpp \
    Newton_interpolation_function_2d.cpp
