SOURCES += main.cpp \
    SetupDialog.cpp \
    ScrollableGrid.cpp \
    Utils.cpp \
    ScrollableGridWithCursor.cpp \
    GridLayout.cpp \
    TestMovieWidget.cpp
HEADERS += SetupDialog.h \
    main.h \
    ScrollableGrid.h \
    DrawingDirection.h \
    ScrollingDirection.h \
    Utils.h \
    ScrollableGridWithCursor.h \
    GridLayout.h \
    TestMovieWidget.h
LIBS += -lavcodec \
    -lavformat \
    -lavutil \
    -lswscale
