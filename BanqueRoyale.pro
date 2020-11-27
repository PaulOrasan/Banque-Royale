QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/bazadate.cpp \
    sources/despre.cpp \
    sources/globals.cpp \
    sources/hasher.cpp \
    sources/imprumutamenu.cpp \
    sources/istorictranzactii.cpp \
    sources/loginmenu.cpp \
    sources/main.cpp \
    sources/menuprincipal.cpp \
    sources/profil.cpp \
    sources/registerdialog.cpp \
    sources/schimbareparola.cpp \
    sources/setarepin.cpp \
    sources/statusbancar.cpp \
    sources/transfermenu.cpp \
    sources/tranzactie.cpp \
    sources/user.cpp \
    sources/vizualizareistoric.cpp \

HEADERS += \
    headers/bazadate.h \
    headers/despre.h \
    headers/globals.h \
    headers/hasher.h \
    headers/imprumutamenu.h \
    headers/istorictranzactii.h \
    headers/loginmenu.h \
    headers/menuprincipal.h \
    headers/profil.h \
    headers/registerdialog.h \
    headers/schimbareparola.h \
    headers/setarepin.h \
    headers/statusbancar.h \
    headers/transfermenu.h \
    headers/tranzactie.h \
    headers/user.h \
    headers/vizualizareistoric.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resouces.qrc

FORMS += \
    ui/despre.ui \
    ui/imprumutamenu.ui \
    ui/loginmenu.ui \
    ui/menuprincipal.ui \
    ui/profil.ui \
    ui/registerdialog.ui \
    ui/schimbareparola.ui \
    ui/setarepin.ui \
    ui/statusbancar.ui \
    ui/transfermenu.ui \
    ui/vizualizareistoric.ui \
