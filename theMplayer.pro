SOURCES += main.cpp \
    SetupDialog.cpp \
    TestMovieGrid.cpp \
    MovieGrid.cpp \
    Movie.cpp \
    MovieFile.cpp \
    MovieWidget.cpp \
    ScrollableGrid.cpp \
    Utils.cpp \
    ScrollableGridWithCursor.cpp \
    MovieWidgetFactory.cpp \
    MovieWidget_Movie.cpp \
    MovieWidget_Directory.cpp \
    GridLayout.cpp
HEADERS += SetupDialog.h \
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
    MovieWidgetFactory.h \
    MovieWidget_Movie.h \
    MovieWidget_Directory.h \
    GridLayout.h
LIBS += -lavcodec \
    -lavformat \
    -lavutil \
    -lswscale
