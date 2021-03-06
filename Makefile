#############################################################################
# Makefile for building: my_wc100_arm
# Generated by qmake (2.01a) (Qt 4.8.6) on: Tue Jan 8 19:13:42 2019
# Project:  my_wc100_arm.pro
# Template: app
# Command: /opt/qt-m6g2c/bin/qmake -spec /opt/qt-m6g2c/mkspecs/qws/linux-arm-gnueabi-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile my_wc100_arm.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-linux-gnueabihf-gcc -lts
CXX           = arm-linux-gnueabihf-g++ -lts
DEFINES       = -DQT_SQL_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/qt-m6g2c/mkspecs/qws/linux-arm-gnueabi-g++ -I. -I/opt/qt-m6g2c/include/QtCore -I/opt/qt-m6g2c/include/QtNetwork -I/opt/qt-m6g2c/include/QtGui -I/opt/qt-m6g2c/include/QtSql -I/opt/qt-m6g2c/include -I/opt/qt-m6g2c/include/QtSerialPort -I/opt/qt-m6g2c/include/QtTest -I. -I. -I. -I/opt/tslib/include
LINK          = arm-linux-gnueabihf-g++ -lts
LFLAGS        = -Wl,-rpath,/opt/qt-m6g2c/lib
LIBS          = $(SUBLIBS)  -L/opt/tslib/lib -L/opt/qt-m6g2c/lib -lQtTest -L/opt/tslib/lib -L/opt/qt-m6g2c/lib -lQtSerialPort -lQtSql -lQtGui -lQtNetwork -lQtCore -lrt -lpthread 
AR            = arm-linux-gnueabihf-ar cqs
RANLIB        = 
QMAKE         = /opt/qt-m6g2c/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-linux-gnueabihf-strip
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
		mainbutton.cpp \
		maintancance.cpp \
		mainwindow.cpp \
		testingdialog.cpp \
		signin.cpp \
		systemsetup.cpp \
		keyboard.cpp \
		ttythread.cpp \
		calibration.cpp \
		cac.cpp \
		databasehelper.cpp \
		mainbussniessview.cpp \
		patientmodel.cpp \
		itemmodel.cpp \
		App.cpp \
		itemparametermodel.cpp \
		calibratemodel.cpp \
		calibrateobservermodel.cpp \
		qc_subitemmodel.cpp \
		sampletypemodel.cpp \
		testresultmodel.cpp \
		qualitycontrolmodel.cpp \
		query.cpp \
		systemmonitor.cpp \
		network.cpp \
		systemupdate.cpp \
		other.cpp \
		messagebox.cpp \
		systeminit.cpp \
		frminput.cpp \
		wifibtthread.cpp \
		keyboardthread.cpp \
		myqsqltablemodel.cpp moc_mainbutton.cpp \
		moc_maintancance.cpp \
		moc_mainwindow.cpp \
		moc_testingdialog.cpp \
		moc_signin.cpp \
		moc_systemsetup.cpp \
		moc_keyboard.cpp \
		moc_ttythread.cpp \
		moc_calibration.cpp \
		moc_cac.cpp \
		moc_mainbussniessview.cpp \
		moc_query.cpp \
		moc_systemmonitor.cpp \
		moc_network.cpp \
		moc_systemupdate.cpp \
		moc_other.cpp \
		moc_frminput.cpp \
		moc_wifibtthread.cpp \
		moc_keyboardthread.cpp \
		moc_myqsqltablemodel.cpp \
		qrc_rc.cpp
OBJECTS       = main.o \
		mainbutton.o \
		maintancance.o \
		mainwindow.o \
		testingdialog.o \
		signin.o \
		systemsetup.o \
		keyboard.o \
		ttythread.o \
		calibration.o \
		cac.o \
		databasehelper.o \
		mainbussniessview.o \
		patientmodel.o \
		itemmodel.o \
		App.o \
		itemparametermodel.o \
		calibratemodel.o \
		calibrateobservermodel.o \
		qc_subitemmodel.o \
		sampletypemodel.o \
		testresultmodel.o \
		qualitycontrolmodel.o \
		query.o \
		systemmonitor.o \
		network.o \
		systemupdate.o \
		other.o \
		messagebox.o \
		systeminit.o \
		frminput.o \
		wifibtthread.o \
		keyboardthread.o \
		myqsqltablemodel.o \
		moc_mainbutton.o \
		moc_maintancance.o \
		moc_mainwindow.o \
		moc_testingdialog.o \
		moc_signin.o \
		moc_systemsetup.o \
		moc_keyboard.o \
		moc_ttythread.o \
		moc_calibration.o \
		moc_cac.o \
		moc_mainbussniessview.o \
		moc_query.o \
		moc_systemmonitor.o \
		moc_network.o \
		moc_systemupdate.o \
		moc_other.o \
		moc_frminput.o \
		moc_wifibtthread.o \
		moc_keyboardthread.o \
		moc_myqsqltablemodel.o \
		qrc_rc.o
DIST          = /opt/qt-m6g2c/mkspecs/common/unix.conf \
		/opt/qt-m6g2c/mkspecs/common/linux.conf \
		/opt/qt-m6g2c/mkspecs/common/gcc-base.conf \
		/opt/qt-m6g2c/mkspecs/common/gcc-base-unix.conf \
		/opt/qt-m6g2c/mkspecs/common/g++-base.conf \
		/opt/qt-m6g2c/mkspecs/common/g++-unix.conf \
		/opt/qt-m6g2c/mkspecs/common/qws.conf \
		/opt/qt-m6g2c/mkspecs/qconfig.pri \
		/opt/qt-m6g2c/mkspecs/features/qt_functions.prf \
		/opt/qt-m6g2c/mkspecs/features/qt_config.prf \
		/opt/qt-m6g2c/mkspecs/features/exclusive_builds.prf \
		/opt/qt-m6g2c/mkspecs/features/default_pre.prf \
		/opt/qt-m6g2c/mkspecs/features/debug.prf \
		/opt/qt-m6g2c/mkspecs/features/default_post.prf \
		/opt/qt-m6g2c/mkspecs/features/qtestlib.prf \
		/opt/qt-m6g2c/mkspecs/features/serialport.prf \
		/opt/qt-m6g2c/mkspecs/features/declarative_debug.prf \
		/opt/qt-m6g2c/mkspecs/features/shared.prf \
		/opt/qt-m6g2c/mkspecs/features/warn_on.prf \
		/opt/qt-m6g2c/mkspecs/features/qt.prf \
		/opt/qt-m6g2c/mkspecs/features/unix/thread.prf \
		/opt/qt-m6g2c/mkspecs/features/moc.prf \
		/opt/qt-m6g2c/mkspecs/features/resources.prf \
		/opt/qt-m6g2c/mkspecs/features/uic.prf \
		/opt/qt-m6g2c/mkspecs/features/yacc.prf \
		/opt/qt-m6g2c/mkspecs/features/lex.prf \
		/opt/qt-m6g2c/mkspecs/features/include_source_dir.prf \
		my_wc100_arm.pro
QMAKE_TARGET  = my_wc100_arm
DESTDIR       = 
TARGET        = my_wc100_arm

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

$(TARGET): ui_mainbutton.h ui_maintancance.h ui_mainwindow.h ui_testingdialog.h ui_signin.h ui_systemsetup.h ui_keyboard.h ui_calibration.h ui_query.h ui_systemupdate.h ui_other.h ui_frminput.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: my_wc100_arm.pro  /opt/qt-m6g2c/mkspecs/qws/linux-arm-gnueabi-g++/qmake.conf /opt/qt-m6g2c/mkspecs/common/unix.conf \
		/opt/qt-m6g2c/mkspecs/common/linux.conf \
		/opt/qt-m6g2c/mkspecs/common/gcc-base.conf \
		/opt/qt-m6g2c/mkspecs/common/gcc-base-unix.conf \
		/opt/qt-m6g2c/mkspecs/common/g++-base.conf \
		/opt/qt-m6g2c/mkspecs/common/g++-unix.conf \
		/opt/qt-m6g2c/mkspecs/common/qws.conf \
		/opt/qt-m6g2c/mkspecs/qconfig.pri \
		/opt/qt-m6g2c/mkspecs/features/qt_functions.prf \
		/opt/qt-m6g2c/mkspecs/features/qt_config.prf \
		/opt/qt-m6g2c/mkspecs/features/exclusive_builds.prf \
		/opt/qt-m6g2c/mkspecs/features/default_pre.prf \
		/opt/qt-m6g2c/mkspecs/features/debug.prf \
		/opt/qt-m6g2c/mkspecs/features/default_post.prf \
		/opt/qt-m6g2c/mkspecs/features/qtestlib.prf \
		/opt/qt-m6g2c/mkspecs/features/serialport.prf \
		/opt/qt-m6g2c/mkspecs/features/declarative_debug.prf \
		/opt/qt-m6g2c/mkspecs/features/shared.prf \
		/opt/qt-m6g2c/mkspecs/features/warn_on.prf \
		/opt/qt-m6g2c/mkspecs/features/qt.prf \
		/opt/qt-m6g2c/mkspecs/features/unix/thread.prf \
		/opt/qt-m6g2c/mkspecs/features/moc.prf \
		/opt/qt-m6g2c/mkspecs/features/resources.prf \
		/opt/qt-m6g2c/mkspecs/features/uic.prf \
		/opt/qt-m6g2c/mkspecs/features/yacc.prf \
		/opt/qt-m6g2c/mkspecs/features/lex.prf \
		/opt/qt-m6g2c/mkspecs/features/include_source_dir.prf \
		/opt/qt-m6g2c/lib/libQtTest.prl \
		/opt/qt-m6g2c/lib/libQtCore.prl \
		/opt/qt-m6g2c/lib/libQtSerialPort.prl \
		/opt/qt-m6g2c/lib/libQtSql.prl \
		/opt/qt-m6g2c/lib/libQtGui.prl \
		/opt/qt-m6g2c/lib/libQtNetwork.prl
	$(QMAKE) -spec /opt/qt-m6g2c/mkspecs/qws/linux-arm-gnueabi-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile my_wc100_arm.pro
/opt/qt-m6g2c/mkspecs/common/unix.conf:
/opt/qt-m6g2c/mkspecs/common/linux.conf:
/opt/qt-m6g2c/mkspecs/common/gcc-base.conf:
/opt/qt-m6g2c/mkspecs/common/gcc-base-unix.conf:
/opt/qt-m6g2c/mkspecs/common/g++-base.conf:
/opt/qt-m6g2c/mkspecs/common/g++-unix.conf:
/opt/qt-m6g2c/mkspecs/common/qws.conf:
/opt/qt-m6g2c/mkspecs/qconfig.pri:
/opt/qt-m6g2c/mkspecs/features/qt_functions.prf:
/opt/qt-m6g2c/mkspecs/features/qt_config.prf:
/opt/qt-m6g2c/mkspecs/features/exclusive_builds.prf:
/opt/qt-m6g2c/mkspecs/features/default_pre.prf:
/opt/qt-m6g2c/mkspecs/features/debug.prf:
/opt/qt-m6g2c/mkspecs/features/default_post.prf:
/opt/qt-m6g2c/mkspecs/features/qtestlib.prf:
/opt/qt-m6g2c/mkspecs/features/serialport.prf:
/opt/qt-m6g2c/mkspecs/features/declarative_debug.prf:
/opt/qt-m6g2c/mkspecs/features/shared.prf:
/opt/qt-m6g2c/mkspecs/features/warn_on.prf:
/opt/qt-m6g2c/mkspecs/features/qt.prf:
/opt/qt-m6g2c/mkspecs/features/unix/thread.prf:
/opt/qt-m6g2c/mkspecs/features/moc.prf:
/opt/qt-m6g2c/mkspecs/features/resources.prf:
/opt/qt-m6g2c/mkspecs/features/uic.prf:
/opt/qt-m6g2c/mkspecs/features/yacc.prf:
/opt/qt-m6g2c/mkspecs/features/lex.prf:
/opt/qt-m6g2c/mkspecs/features/include_source_dir.prf:
/opt/qt-m6g2c/lib/libQtTest.prl:
/opt/qt-m6g2c/lib/libQtCore.prl:
/opt/qt-m6g2c/lib/libQtSerialPort.prl:
/opt/qt-m6g2c/lib/libQtSql.prl:
/opt/qt-m6g2c/lib/libQtGui.prl:
/opt/qt-m6g2c/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -spec /opt/qt-m6g2c/mkspecs/qws/linux-arm-gnueabi-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile my_wc100_arm.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/my_wc100_arm1.0.0 || $(MKDIR) .tmp/my_wc100_arm1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/my_wc100_arm1.0.0/ && $(COPY_FILE) --parents mainbutton.h maintancance.h mainwindow.h testingdialog.h signin.h systemsetup.h keyboard.h ttythread.h calibration.h cac.h databasehelper.h mainbussniessview.h patientmodel.h itemmodel.h App.h itemparametermodel.h calibratemodel.h calibrateobservermodel.h qc_subitemmodel.h sampletypemodel.h testresultmodel.h qualitycontrolmodel.h query.h systemmonitor.h network.h systemupdate.h other.h messagebox.h systeminit.h frminput.h wifibtthread.h keyboardthread.h myqsqltablemodel.h .tmp/my_wc100_arm1.0.0/ && $(COPY_FILE) --parents rc.qrc .tmp/my_wc100_arm1.0.0/ && $(COPY_FILE) --parents main.cpp mainbutton.cpp maintancance.cpp mainwindow.cpp testingdialog.cpp signin.cpp systemsetup.cpp keyboard.cpp ttythread.cpp calibration.cpp cac.cpp databasehelper.cpp mainbussniessview.cpp patientmodel.cpp itemmodel.cpp App.cpp itemparametermodel.cpp calibratemodel.cpp calibrateobservermodel.cpp qc_subitemmodel.cpp sampletypemodel.cpp testresultmodel.cpp qualitycontrolmodel.cpp query.cpp systemmonitor.cpp network.cpp systemupdate.cpp other.cpp messagebox.cpp systeminit.cpp frminput.cpp wifibtthread.cpp keyboardthread.cpp myqsqltablemodel.cpp .tmp/my_wc100_arm1.0.0/ && $(COPY_FILE) --parents mainbutton.ui maintancance.ui mainwindow.ui testingdialog.ui signin.ui systemsetup.ui keyboard.ui calibration.ui query.ui systemupdate.ui other.ui frminput.ui .tmp/my_wc100_arm1.0.0/ && $(COPY_FILE) --parents syszux/tr_zh.ts syszux/tr_en.ts .tmp/my_wc100_arm1.0.0/ && (cd `dirname .tmp/my_wc100_arm1.0.0` && $(TAR) my_wc100_arm1.0.0.tar my_wc100_arm1.0.0 && $(COMPRESS) my_wc100_arm1.0.0.tar) && $(MOVE) `dirname .tmp/my_wc100_arm1.0.0`/my_wc100_arm1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/my_wc100_arm1.0.0


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

compiler_moc_header_make_all: moc_mainbutton.cpp moc_maintancance.cpp moc_mainwindow.cpp moc_testingdialog.cpp moc_signin.cpp moc_systemsetup.cpp moc_keyboard.cpp moc_ttythread.cpp moc_calibration.cpp moc_cac.cpp moc_mainbussniessview.cpp moc_query.cpp moc_systemmonitor.cpp moc_network.cpp moc_systemupdate.cpp moc_other.cpp moc_frminput.cpp moc_wifibtthread.cpp moc_keyboardthread.cpp moc_myqsqltablemodel.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainbutton.cpp moc_maintancance.cpp moc_mainwindow.cpp moc_testingdialog.cpp moc_signin.cpp moc_systemsetup.cpp moc_keyboard.cpp moc_ttythread.cpp moc_calibration.cpp moc_cac.cpp moc_mainbussniessview.cpp moc_query.cpp moc_systemmonitor.cpp moc_network.cpp moc_systemupdate.cpp moc_other.cpp moc_frminput.cpp moc_wifibtthread.cpp moc_keyboardthread.cpp moc_myqsqltablemodel.cpp
moc_mainbutton.cpp: mainbutton.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) mainbutton.h -o moc_mainbutton.cpp

moc_maintancance.cpp: signin.h \
		messagebox.h \
		cac.h \
		ttythread.h \
		App.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		maintancance.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) maintancance.h -o moc_maintancance.cpp

moc_mainwindow.cpp: mainbutton.h \
		testingdialog.h \
		myqsqltablemodel.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		ttythread.h \
		App.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		calibration.h \
		calibrateobservermodel.h \
		databasehelper.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		query.h \
		systemmonitor.h \
		systemupdate.h \
		network.h \
		other.h \
		systeminit.h \
		mainwindow.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_testingdialog.cpp: myqsqltablemodel.h \
		testingdialog.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) testingdialog.h -o moc_testingdialog.cpp

moc_signin.cpp: messagebox.h \
		signin.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) signin.h -o moc_signin.cpp

moc_systemsetup.cpp: wifibtthread.h \
		App.h \
		keyboard.h \
		keyboardthread.h \
		systemsetup.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) systemsetup.h -o moc_systemsetup.cpp

moc_keyboard.cpp: keyboardthread.h \
		keyboard.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) keyboard.h -o moc_keyboard.cpp

moc_ttythread.cpp: App.h \
		ttythread.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) ttythread.h -o moc_ttythread.cpp

moc_calibration.cpp: keyboard.h \
		keyboardthread.h \
		calibrateobservermodel.h \
		calibration.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) calibration.h -o moc_calibration.cpp

moc_cac.cpp: ttythread.h \
		App.h \
		cac.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) cac.h -o moc_cac.cpp

moc_mainbussniessview.cpp: patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		App.h \
		calibrateobservermodel.h \
		ttythread.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		myqsqltablemodel.h \
		mainbussniessview.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) mainbussniessview.h -o moc_mainbussniessview.cpp

moc_query.cpp: ttythread.h \
		App.h \
		messagebox.h \
		query.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) query.h -o moc_query.cpp

moc_systemmonitor.cpp: systemmonitor.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) systemmonitor.h -o moc_systemmonitor.cpp

moc_network.cpp: network.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) network.h -o moc_network.cpp

moc_systemupdate.cpp: network.h \
		keyboard.h \
		keyboardthread.h \
		systemupdate.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) systemupdate.h -o moc_systemupdate.cpp

moc_other.cpp: other.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) other.h -o moc_other.cpp

moc_frminput.cpp: frminput.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) frminput.h -o moc_frminput.cpp

moc_wifibtthread.cpp: App.h \
		wifibtthread.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) wifibtthread.h -o moc_wifibtthread.cpp

moc_keyboardthread.cpp: keyboardthread.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) keyboardthread.h -o moc_keyboardthread.cpp

moc_myqsqltablemodel.cpp: myqsqltablemodel.h
	/opt/qt-m6g2c/bin/moc $(DEFINES) $(INCPATH) myqsqltablemodel.h -o moc_myqsqltablemodel.cpp

compiler_rcc_make_all: qrc_rc.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_rc.cpp
qrc_rc.cpp: rc.qrc \
		syszux/tr_en.qm \
		syszux/tr_zh.qm \
		syszux/syszuxpinyin \
		image/System.png \
		image/LastPage.png \
		image/update.gif \
		image/Home.png \
		image/Save.png \
		image/FirstPag.png \
		image/Update.png \
		image/export.png \
		image/Maintainance.png \
		image/Testing.png \
		image/Shutdown.png \
		image/test.gif \
		image/NextPage.png \
		image/Calibrate.png \
		image/download1.png \
		image/Run.png \
		image/Query.png \
		image/PassWorld.png \
		image/PreviousPage.png \
		image/checkbox_checked.png \
		image/Clean.png \
		image/poweroff.gif \
		image/History.png \
		image/arrow_left.png \
		image/Stop.png \
		image/backGround.png \
		image/download2.png \
		image/Initialize_logo.gif \
		image/Left.png \
		image/power.ico \
		icons/BatteryIcon5.png \
		icons/WirelessIcon2.png \
		icons/WirelessIcon3.png \
		icons/WirelessIcon4.png \
		icons/BatteryIcon2.png \
		icons/WirelessIcon1.png \
		icons/BatteryIcon.png \
		icons/BatteryIcon1.png \
		icons/BatteryIcon4.png \
		icons/WirelessIcon.png \
		icons/Bluetooth2.png \
		icons/BatteryIcon3.png \
		icons/Bluetooth1.png
	/opt/qt-m6g2c/bin/rcc -name rc rc.qrc -o qrc_rc.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainbutton.h ui_maintancance.h ui_mainwindow.h ui_testingdialog.h ui_signin.h ui_systemsetup.h ui_keyboard.h ui_calibration.h ui_query.h ui_systemupdate.h ui_other.h ui_frminput.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainbutton.h ui_maintancance.h ui_mainwindow.h ui_testingdialog.h ui_signin.h ui_systemsetup.h ui_keyboard.h ui_calibration.h ui_query.h ui_systemupdate.h ui_other.h ui_frminput.h
ui_mainbutton.h: mainbutton.ui
	/opt/qt-m6g2c/bin/uic mainbutton.ui -o ui_mainbutton.h

ui_maintancance.h: maintancance.ui
	/opt/qt-m6g2c/bin/uic maintancance.ui -o ui_maintancance.h

ui_mainwindow.h: mainwindow.ui
	/opt/qt-m6g2c/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_testingdialog.h: testingdialog.ui
	/opt/qt-m6g2c/bin/uic testingdialog.ui -o ui_testingdialog.h

ui_signin.h: signin.ui
	/opt/qt-m6g2c/bin/uic signin.ui -o ui_signin.h

ui_systemsetup.h: systemsetup.ui
	/opt/qt-m6g2c/bin/uic systemsetup.ui -o ui_systemsetup.h

ui_keyboard.h: keyboard.ui
	/opt/qt-m6g2c/bin/uic keyboard.ui -o ui_keyboard.h

ui_calibration.h: calibration.ui
	/opt/qt-m6g2c/bin/uic calibration.ui -o ui_calibration.h

ui_query.h: query.ui
	/opt/qt-m6g2c/bin/uic query.ui -o ui_query.h

ui_systemupdate.h: systemupdate.ui
	/opt/qt-m6g2c/bin/uic systemupdate.ui -o ui_systemupdate.h

ui_other.h: other.ui
	/opt/qt-m6g2c/bin/uic other.ui -o ui_other.h

ui_frminput.h: frminput.ui
	/opt/qt-m6g2c/bin/uic frminput.ui -o ui_frminput.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		mainbutton.h \
		testingdialog.h \
		myqsqltablemodel.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		ttythread.h \
		App.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		calibration.h \
		calibrateobservermodel.h \
		databasehelper.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		query.h \
		systemmonitor.h \
		systemupdate.h \
		network.h \
		other.h \
		systeminit.h \
		frminput.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainbutton.o: mainbutton.cpp mainbutton.h \
		ui_mainbutton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainbutton.o mainbutton.cpp

maintancance.o: maintancance.cpp maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		ttythread.h \
		App.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		ui_maintancance.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maintancance.o maintancance.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		mainbutton.h \
		testingdialog.h \
		myqsqltablemodel.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		ttythread.h \
		App.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		calibration.h \
		calibrateobservermodel.h \
		databasehelper.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		query.h \
		systemmonitor.h \
		systemupdate.h \
		network.h \
		other.h \
		systeminit.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

testingdialog.o: testingdialog.cpp testingdialog.h \
		myqsqltablemodel.h \
		ui_testingdialog.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		App.h \
		calibrateobservermodel.h \
		ttythread.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		databasehelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o testingdialog.o testingdialog.cpp

signin.o: signin.cpp signin.h \
		messagebox.h \
		ui_signin.h \
		App.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o signin.o signin.cpp

systemsetup.o: systemsetup.cpp systemsetup.h \
		wifibtthread.h \
		App.h \
		keyboard.h \
		keyboardthread.h \
		ui_systemsetup.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		calibrateobservermodel.h \
		ttythread.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		myqsqltablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o systemsetup.o systemsetup.cpp

keyboard.o: keyboard.cpp keyboard.h \
		keyboardthread.h \
		ui_keyboard.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o keyboard.o keyboard.cpp

ttythread.o: ttythread.cpp ttythread.h \
		App.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ttythread.o ttythread.cpp

calibration.o: calibration.cpp calibration.h \
		keyboard.h \
		keyboardthread.h \
		calibrateobservermodel.h \
		ui_calibration.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		App.h \
		ttythread.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		systemsetup.h \
		wifibtthread.h \
		myqsqltablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calibration.o calibration.cpp

cac.o: cac.cpp cac.h \
		ttythread.h \
		App.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cac.o cac.cpp

databasehelper.o: databasehelper.cpp databasehelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o databasehelper.o databasehelper.cpp

mainbussniessview.o: mainbussniessview.cpp mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		App.h \
		calibrateobservermodel.h \
		ttythread.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		myqsqltablemodel.h \
		databasehelper.h \
		calibration.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainbussniessview.o mainbussniessview.cpp

patientmodel.o: patientmodel.cpp patientmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o patientmodel.o patientmodel.cpp

itemmodel.o: itemmodel.cpp itemmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o itemmodel.o itemmodel.cpp

App.o: App.cpp App.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o App.o App.cpp

itemparametermodel.o: itemparametermodel.cpp itemparametermodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o itemparametermodel.o itemparametermodel.cpp

calibratemodel.o: calibratemodel.cpp calibratemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calibratemodel.o calibratemodel.cpp

calibrateobservermodel.o: calibrateobservermodel.cpp calibrateobservermodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calibrateobservermodel.o calibrateobservermodel.cpp

qc_subitemmodel.o: qc_subitemmodel.cpp qc_subitemmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qc_subitemmodel.o qc_subitemmodel.cpp

sampletypemodel.o: sampletypemodel.cpp sampletypemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sampletypemodel.o sampletypemodel.cpp

testresultmodel.o: testresultmodel.cpp testresultmodel.h \
		itemparametermodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o testresultmodel.o testresultmodel.cpp

qualitycontrolmodel.o: qualitycontrolmodel.cpp qualitycontrolmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qualitycontrolmodel.o qualitycontrolmodel.cpp

query.o: query.cpp query.h \
		ttythread.h \
		App.h \
		messagebox.h \
		ui_query.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		calibrateobservermodel.h \
		maintancance.h \
		signin.h \
		cac.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		myqsqltablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o query.o query.cpp

systemmonitor.o: systemmonitor.cpp systemmonitor.h \
		i2c-dev.h \
		App.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o systemmonitor.o systemmonitor.cpp

network.o: network.cpp network.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o network.o network.cpp

systemupdate.o: systemupdate.cpp systemupdate.h \
		network.h \
		keyboard.h \
		keyboardthread.h \
		ui_systemupdate.h \
		App.h \
		messagebox.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o systemupdate.o systemupdate.cpp

other.o: other.cpp other.h \
		ui_other.h \
		mainbussniessview.h \
		patientmodel.h \
		itemmodel.h \
		qc_subitemmodel.h \
		qualitycontrolmodel.h \
		itemparametermodel.h \
		calibratemodel.h \
		sampletypemodel.h \
		testresultmodel.h \
		App.h \
		calibrateobservermodel.h \
		ttythread.h \
		maintancance.h \
		signin.h \
		messagebox.h \
		cac.h \
		systemsetup.h \
		wifibtthread.h \
		keyboard.h \
		keyboardthread.h \
		myqsqltablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o other.o other.cpp

messagebox.o: messagebox.cpp messagebox.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o messagebox.o messagebox.cpp

systeminit.o: systeminit.cpp systeminit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o systeminit.o systeminit.cpp

frminput.o: frminput.cpp frminput.h \
		ui_frminput.h \
		App.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o frminput.o frminput.cpp

wifibtthread.o: wifibtthread.cpp wifibtthread.h \
		App.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wifibtthread.o wifibtthread.cpp

keyboardthread.o: keyboardthread.cpp keyboardthread.h \
		keyboard.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o keyboardthread.o keyboardthread.cpp

myqsqltablemodel.o: myqsqltablemodel.cpp myqsqltablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myqsqltablemodel.o myqsqltablemodel.cpp

moc_mainbutton.o: moc_mainbutton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainbutton.o moc_mainbutton.cpp

moc_maintancance.o: moc_maintancance.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maintancance.o moc_maintancance.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_testingdialog.o: moc_testingdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_testingdialog.o moc_testingdialog.cpp

moc_signin.o: moc_signin.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_signin.o moc_signin.cpp

moc_systemsetup.o: moc_systemsetup.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_systemsetup.o moc_systemsetup.cpp

moc_keyboard.o: moc_keyboard.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_keyboard.o moc_keyboard.cpp

moc_ttythread.o: moc_ttythread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ttythread.o moc_ttythread.cpp

moc_calibration.o: moc_calibration.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_calibration.o moc_calibration.cpp

moc_cac.o: moc_cac.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_cac.o moc_cac.cpp

moc_mainbussniessview.o: moc_mainbussniessview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainbussniessview.o moc_mainbussniessview.cpp

moc_query.o: moc_query.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_query.o moc_query.cpp

moc_systemmonitor.o: moc_systemmonitor.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_systemmonitor.o moc_systemmonitor.cpp

moc_network.o: moc_network.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_network.o moc_network.cpp

moc_systemupdate.o: moc_systemupdate.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_systemupdate.o moc_systemupdate.cpp

moc_other.o: moc_other.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_other.o moc_other.cpp

moc_frminput.o: moc_frminput.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_frminput.o moc_frminput.cpp

moc_wifibtthread.o: moc_wifibtthread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_wifibtthread.o moc_wifibtthread.cpp

moc_keyboardthread.o: moc_keyboardthread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_keyboardthread.o moc_keyboardthread.cpp

moc_myqsqltablemodel.o: moc_myqsqltablemodel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_myqsqltablemodel.o moc_myqsqltablemodel.cpp

qrc_rc.o: qrc_rc.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_rc.o qrc_rc.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

