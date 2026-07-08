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
    function_1d.h \
    piecewise_linear_interpolation_function_1d.h \
	linear_interpolation_function_1d.h
SOURCES = main.cpp graph_widget.cpp \
    function_1d.cpp \
    piecewise_linear_interpolation_function_1d.cpp \
	linear_interpolation_function_1d.cpp
