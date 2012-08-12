#############################################################################
# Makefile for building: theMplayer
# Generated by qmake (2.01a) (Qt 4.8.2) on: ?? ???. 13 03:34:12 2012
# Project:  theMplayer.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile theMplayer.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -march=i686 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -std=c++0x -march=i686 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt/mkspecs/linux-g++ -I. -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I.
LINK          = g++
LFLAGS        = -Wl,-O1,--sort-common,--as-needed,-z,relro -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lavcodec -lavformat -lavutil -lswscale -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		SetupDialog.cpp \
		Utils.cpp \
		GridLayout.cpp \
		SetupDialogPreview.cpp \
		GridLayoutScroller.cpp \
		GridLayoutScrollerWithCursor.cpp \
		Movie.cpp \
		MovieCollection.cpp \
		MovieCollectionModel.cpp moc_SetupDialog.cpp \
		moc_Movie.cpp \
		moc_MovieCollection.cpp
OBJECTS       = main.o \
		SetupDialog.o \
		Utils.o \
		GridLayout.o \
		SetupDialogPreview.o \
		GridLayoutScroller.o \
		GridLayoutScrollerWithCursor.o \
		Movie.o \
		MovieCollection.o \
		MovieCollectionModel.o \
		moc_SetupDialog.o \
		moc_Movie.o \
		moc_MovieCollection.o
DIST          = /usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/common/gcc-base.conf \
		/usr/share/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt/mkspecs/common/g++-base.conf \
		/usr/share/qt/mkspecs/common/g++-unix.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/release.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		theMplayer.pro
QMAKE_TARGET  = theMplayer
DESTDIR       = 
TARGET        = theMplayer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: theMplayer.pro  /usr/share/qt/mkspecs/linux-g++/qmake.conf /usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/common/gcc-base.conf \
		/usr/share/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt/mkspecs/common/g++-base.conf \
		/usr/share/qt/mkspecs/common/g++-unix.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/release.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -o Makefile theMplayer.pro
/usr/share/qt/mkspecs/common/unix.conf:
/usr/share/qt/mkspecs/common/linux.conf:
/usr/share/qt/mkspecs/common/gcc-base.conf:
/usr/share/qt/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt/mkspecs/common/g++-base.conf:
/usr/share/qt/mkspecs/common/g++-unix.conf:
/usr/share/qt/mkspecs/qconfig.pri:
/usr/share/qt/mkspecs/modules/qt_phonon.pri:
/usr/share/qt/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt/mkspecs/features/qt_functions.prf:
/usr/share/qt/mkspecs/features/qt_config.prf:
/usr/share/qt/mkspecs/features/exclusive_builds.prf:
/usr/share/qt/mkspecs/features/default_pre.prf:
/usr/share/qt/mkspecs/features/release.prf:
/usr/share/qt/mkspecs/features/default_post.prf:
/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt/mkspecs/features/warn_on.prf:
/usr/share/qt/mkspecs/features/qt.prf:
/usr/share/qt/mkspecs/features/unix/thread.prf:
/usr/share/qt/mkspecs/features/moc.prf:
/usr/share/qt/mkspecs/features/resources.prf:
/usr/share/qt/mkspecs/features/uic.prf:
/usr/share/qt/mkspecs/features/yacc.prf:
/usr/share/qt/mkspecs/features/lex.prf:
/usr/share/qt/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile theMplayer.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/theMplayer1.0.0 || $(MKDIR) .tmp/theMplayer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/theMplayer1.0.0/ && $(COPY_FILE) --parents SetupDialog.h main.h Utils.h GridLayout.h SetupDialogPreview.h GridLayoutDrawingDirection.h GridLayoutScrollingDirection.h GridLayoutScroller.h GridLayoutScrollerWithCursor.h Movie.h MovieCollection.h MovieCollectionModel.h .tmp/theMplayer1.0.0/ && $(COPY_FILE) --parents main.cpp SetupDialog.cpp Utils.cpp GridLayout.cpp SetupDialogPreview.cpp GridLayoutScroller.cpp GridLayoutScrollerWithCursor.cpp Movie.cpp MovieCollection.cpp MovieCollectionModel.cpp .tmp/theMplayer1.0.0/ && (cd `dirname .tmp/theMplayer1.0.0` && $(TAR) theMplayer1.0.0.tar theMplayer1.0.0 && $(COMPRESS) theMplayer1.0.0.tar) && $(MOVE) `dirname .tmp/theMplayer1.0.0`/theMplayer1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/theMplayer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_SetupDialog.cpp moc_Movie.cpp moc_MovieCollection.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_SetupDialog.cpp moc_Movie.cpp moc_MovieCollection.cpp
moc_SetupDialog.cpp: GridLayout.h \
		SetupDialogPreview.h \
		SetupDialog.h
	/usr/bin/moc $(DEFINES) $(INCPATH) SetupDialog.h -o moc_SetupDialog.cpp

moc_Movie.cpp: Movie.h
	/usr/bin/moc $(DEFINES) $(INCPATH) Movie.h -o moc_Movie.cpp

moc_MovieCollection.cpp: GridLayout.h \
		GridLayoutScrollerWithCursor.h \
		GridLayoutScroller.h \
		GridLayoutDrawingDirection.h \
		GridLayoutScrollingDirection.h \
		MovieCollectionModel.h \
		MovieCollection.h
	/usr/bin/moc $(DEFINES) $(INCPATH) MovieCollection.h -o moc_MovieCollection.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp main.h \
		MovieCollection.h \
		GridLayout.h \
		GridLayoutScrollerWithCursor.h \
		GridLayoutScroller.h \
		GridLayoutDrawingDirection.h \
		GridLayoutScrollingDirection.h \
		MovieCollectionModel.h \
		SetupDialog.h \
		SetupDialogPreview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

SetupDialog.o: SetupDialog.cpp SetupDialog.h \
		GridLayout.h \
		SetupDialogPreview.h \
		main.h \
		Utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SetupDialog.o SetupDialog.cpp

Utils.o: Utils.cpp Utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Utils.o Utils.cpp

GridLayout.o: GridLayout.cpp GridLayout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GridLayout.o GridLayout.cpp

SetupDialogPreview.o: SetupDialogPreview.cpp SetupDialogPreview.h \
		GridLayout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SetupDialogPreview.o SetupDialogPreview.cpp

GridLayoutScroller.o: GridLayoutScroller.cpp GridLayoutScroller.h \
		GridLayout.h \
		GridLayoutDrawingDirection.h \
		GridLayoutScrollingDirection.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GridLayoutScroller.o GridLayoutScroller.cpp

GridLayoutScrollerWithCursor.o: GridLayoutScrollerWithCursor.cpp GridLayoutScrollerWithCursor.h \
		GridLayoutScroller.h \
		GridLayout.h \
		GridLayoutDrawingDirection.h \
		GridLayoutScrollingDirection.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GridLayoutScrollerWithCursor.o GridLayoutScrollerWithCursor.cpp

Movie.o: Movie.cpp Movie.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Movie.o Movie.cpp

MovieCollection.o: MovieCollection.cpp MovieCollection.h \
		GridLayout.h \
		GridLayoutScrollerWithCursor.h \
		GridLayoutScroller.h \
		GridLayoutDrawingDirection.h \
		GridLayoutScrollingDirection.h \
		MovieCollectionModel.h \
		Movie.h \
		Utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MovieCollection.o MovieCollection.cpp

MovieCollectionModel.o: MovieCollectionModel.cpp MovieCollectionModel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MovieCollectionModel.o MovieCollectionModel.cpp

moc_SetupDialog.o: moc_SetupDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_SetupDialog.o moc_SetupDialog.cpp

moc_Movie.o: moc_Movie.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Movie.o moc_Movie.cpp

moc_MovieCollection.o: moc_MovieCollection.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MovieCollection.o moc_MovieCollection.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

