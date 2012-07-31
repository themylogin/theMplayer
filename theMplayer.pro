SOURCES += main.cpp \
    SetupDialog.cpp \
    AbstractMovieGrid.cpp \
    TestMovieGrid.cpp \
    MovieGrid.cpp \
    Movie.cpp \
    MovieFile.cpp \
    MovieFactory.cpp \
    MovieFactoryThread.cpp \
    MovieWidget.cpp \
    ScrollableGrid.cpp \
    Utils.cpp \
    ScrollableGridWithCursor.cpp
HEADERS += SetupDialog.h \
    AbstractMovieGrid.h \
    TestMovieGrid.h \
    main.h \
    MovieGrid.h \
    Movie.h \
    MovieFile.h \
    MovieFactory.h \
    MovieFactoryThread.h \
    MovieWidget.h \
    ScrollableGrid.h \
    DrawingDirection.h \
    ScrollingDirection.h \
    Utils.h \
    ScrollableGridWithCursor.h
LIBS += -lavcodec \
    -lavformat \
    -lavutil \
    -lswscale \
    -llirc_client
