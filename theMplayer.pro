SOURCES += main.cpp \
    SetupDialog.cpp \
    ScrollableGrid.cpp \
    Utils.cpp \
    ScrollableGridWithCursor.cpp \
    GridLayout.cpp \
    SetupDialogPreview.cpp
HEADERS += SetupDialog.h \
    main.h \
    ScrollableGrid.h \
    DrawingDirection.h \
    ScrollingDirection.h \
    Utils.h \
    ScrollableGridWithCursor.h \
    GridLayout.h \
    SetupDialogPreview.h
LIBS += -lavcodec \
    -lavformat \
    -lavutil \
    -lswscale
