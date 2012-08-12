SOURCES += main.cpp \
    SetupDialog.cpp \
    Utils.cpp \
    GridLayout.cpp \
    SetupDialogPreview.cpp \
    GridLayoutScroller.cpp \
    GridLayoutScrollerWithCursor.cpp \
    Movie.cpp \
    MovieCollection.cpp
HEADERS += SetupDialog.h \
    main.h \
    Utils.h \
    GridLayout.h \
    SetupDialogPreview.h \
    GridLayoutDrawingDirection.h \
    GridLayoutScrollingDirection.h \
    GridLayoutScroller.h \
    GridLayoutScrollerWithCursor.h \
    Movie.h \
    MovieCollection.h
LIBS += -lavcodec \
    -lavformat \
    -lavutil \
    -lswscale
