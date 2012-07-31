SOURCES += main.cpp \
    SetupDialog.cpp \
    AbstractMovieGrid.cpp \
    TestMovieGrid.cpp \
    MovieGrid.cpp \
    Movie.cpp \
    MovieFile.cpp \
    MovieWidget.cpp \
    ScrollableGrid.cpp \
    Utils.cpp \
    ScrollableGridWithCursor.cpp \
    MovieWidgetFactoryThread.cpp \
    MovieWidgetFactory.cpp
HEADERS += SetupDialog.h \
    AbstractMovieGrid.h \
    TestMovieGrid.h \
    main.h \
    MovieGrid.h \
    Movie.h \
    MovieFile.h \
    MovieWidget.h \
    ScrollableGrid.h \
    DrawingDirection.h \
    ScrollingDirection.h \
    Utils.h \
    ScrollableGridWithCursor.h \
    MovieWidgetFactoryThread.h \
    MovieWidgetFactory.h
LIBS += -lavcodec \
    -lavformat \
    -lavutil \
    -lswscale \
    -llirc_client
