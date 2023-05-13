QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    coin.cpp \
    enemy.cpp \
    food.cpp \
    ground.cpp \
    home.cpp \
    main.cpp \
    mycustomgraphicsview.cpp \
    player.cpp \
    power.cpp \
    walls.cpp

HEADERS += \
    board.h \
    coin.h \
    enemy.h \
    food.h \
    ground.h \
    home.h \
    mycustomgraphicsview.h \
    player.h \
    power.h \
    walls.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
