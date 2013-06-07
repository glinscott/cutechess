TARGET = cutechess-cli
DESTDIR = $$PWD

include(../lib/lib.pri)

CUTECHESS_CLI_VERSION = 0.5.1

macx-xcode {
    DEFINES += CUTECHESS_CLI_VERSION=\"$$CUTECHESS_CLI_VERSION\"
} else {
    OBJECTS_DIR = .obj/
    MOC_DIR = .moc/
    RCC_DIR = .rcc/
    DEFINES += CUTECHESS_CLI_VERSION=\\\"$$CUTECHESS_CLI_VERSION\\\"
}

win32 {
    CONFIG += console
}

mac {
    CONFIG -= app_bundle
}

unix:!mac {
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
    QMAKE_RPATH=
}

QT = core

# Code
include(src/src.pri)

# Resources
include(res/res.pri)
