SOURCES += main.cpp \
    SetupDialog.cpp \
    Utils.cpp \
    GridLayout.cpp \
    SetupDialogPreview.cpp \
    GridLayoutScroller.cpp \
    GridLayoutScrollerWithCursor.cpp
HEADERS += SetupDialog.h \
    main.h \
    Utils.h \
    GridLayout.h \
    SetupDialogPreview.h \
    GridLayoutDrawingDirection.h \
    GridLayoutScrollingDirection.h \
    GridLayoutScroller.h \
    GridLayoutScrollerWithCursor.h
LIBS += -lavcodec \
    -lavformat \
    -lavutil \
    -lswscale
