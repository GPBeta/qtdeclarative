CONFIG += testcase
TARGET = tst_qdeclarativedebugjs
QT += network script declarative-private testlib
macx:CONFIG -= app_bundle

HEADERS += ../shared/debugutil_p.h

SOURCES +=     tst_qdeclarativedebugjs.cpp \
            ../shared/debugutil.cpp

INCLUDEPATH += ../shared

testDataFiles.files = data
testDataFiles.path = .
DEPLOYMENT += testDataFiles


CONFIG += parallel_test
#temporary
CONFIG += insignificant_test
