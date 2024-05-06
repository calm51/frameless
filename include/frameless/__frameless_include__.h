#ifndef __FRAMELESS_INCLUDE___H
#define __FRAMELESS_INCLUDE___H
#pragma once
#pragma execution_character_set("utf-8")

#ifdef I_AM_LIBRARY
#define LIB_EXPORT Q_DECL_EXPORT
//#define LIB_EXPORT __declspec(dllexport)
#else
#define LIB_EXPORT Q_DECL_IMPORT
//#define LIB_EXPORT __declspec(dllimport)
#endif

//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>
//#include <string.h>
//#include <stdlib.h>
//using namespace std;

#include <QApplication>
#include <QMainWindow>
#include <QDialog>
#include <qthreadpool.h>
#include <qmutex.h>
#include <quuid.h>
#include <qjsonobject.h>
#include<QJsonArray>
#include <QProcess>
#include <QList>
#include <QTextStream>
#include <qdir.h>
#include <qjsondocument.h>
#include <QDebug>
#include <QTimer>
#include <qdatetime.h>
#include <QThread>
#include <QTime>
#include <QCoreApplication>
#include <QThreadPool>
#include <QApplication>
#include <QTranslator>
#include <QtWidgets/qfileiconprovider.h>
#include <QSize>

#include <QColor>
#include <QGraphicsDropShadowEffect>
#include <QMap>
#include <QString>
#include <QtGlobal>
#include <qlist.h>

#if defined Q_OS_ANDROID
#include "QtAndroid"
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#endif

//Q_DECLARE_METATYPE(std::function<void()>)


#define FRAMELESS_BEGIN_NAMESPACE namespace Frameless {
#define FRAMELESS_END_NAMESPACE }
FRAMELESS_BEGIN_NAMESPACE

#ifndef ____
#define ____ qDebug()
#endif

#ifndef _FRAMELESS_THEME_ENUM
#define _FRAMELESS_THEME_ENUM
namespace Theme {
    extern LIB_EXPORT const QString &Light;
    extern LIB_EXPORT const QString &Dark;
    extern LIB_EXPORT const QString &White;
    extern LIB_EXPORT const QString &Gray;
}
#endif // _FRAMELESS_THEME_ENUM

namespace OS {
extern LIB_EXPORT const QString &WIN;
extern LIB_EXPORT const QString &ANDROID_;
extern LIB_EXPORT const QString &LINUX;
extern LIB_EXPORT const QString &OSX;
}

class LIB_EXPORT __signal__ : public QObject {
    Q_OBJECT
public:
    __signal__();
signals:
    //    void run(std::function<void()> c_fn);
    void themeChanged();
};

class LIB_EXPORT __slots__ : public QObject {
    Q_OBJECT
public:
    __slots__();
public slots:
    //    void run(std::function<void()> c_fn);
};

struct LIB_EXPORT __args__ {
};

struct LIB_EXPORT __themeconf__ {
    int shadow_size = 13;
    //    int resize_rect_out = 6;
    //    int resize_rect_in = 2;
    //    int resize_rect_corner = resize_rect_in+6;
    QColor shadow_color = QColor(140,140,140);
    QList<int> round4 = {6,6,3,3};
    //    bool allow_showMaximized = true;
    //    bool allow_showMinimized = true;
    //    int titlebar_MinimumHeight = round4.at(0)>round4.at(1)?round4.at(0):round4.at(1);
    int border_width = 0;
    QList<QColor> Frameless_colors = {
        QColor(241,241,241), // titlebar background color
        QColor(255,255,255), // central widget background color

        QColor(160,160,160) // border color
    };

    // ==============================================

    int border_top_width = 1;
    int border_bottom_width = 1;
    //    QList<bool> hide_button = {false,false,false};
    QList<QColor> TitlebarLikeWindows10_colors = {

        QColor(241,241,241), // all button background color

        QColor(228,228,228), // button hover background color
        QColor(212,212,212), // button pressed background color
        QColor(102,102,102, 200), // button color
        QColor(0,0,0), // button hover pressed color

        QColor(232,30,47), // close button hover background color
        QColor(236,118,128), // close button pressed background color
        QColor(30,30,30, 200), // close button color
        QColor(255,255,255), // close button hover pressed color

        QColor(167,240,178), // border top color  167,240,178 170,224,240
        QColor(238,238,238) // border bottom color

    };

    // ==============================================

    QList<QColor> TitlebarLikeAndroid_colors = {

        QColor(241,241,241), // all button background color

        QColor(167,240,178), // border top color
        QColor(238,238,238) // border bottom color

    };


};

// __declspec(dllexport) __declspec(dllimport)
class LIB_EXPORT __global__ {

public:
    __global__();

    __args__ ARGS;
    __signal__ SIGNAL;
    __slots__ SLOTS;
    QMap<QString,__themeconf__> theme_config;
    QString currentTheme = "Light";
    void swithTheme(const QString &key);
    inline const __themeconf__ & currentThemeConf(){return theme_config[currentTheme];}

    void signal_connect_slots();

    QString qcolor2qss(const QColor &c);

#if defined Q_OS_WIN
    QString os = "WIN";
#elif defined Q_OS_ANDROID
    QString os = "ANDROID";
#elif defined Q_OS_LINUX
    QString os = "LINUX";
#elif defined Q_OS_OSX
    QString os = "OSX";
#else
    QString os = "";
#endif

};

extern __global__& GLOBAL;
LIB_EXPORT __global__& G();




FRAMELESS_END_NAMESPACE

#endif // __FRAMELESS_INCLUDE___H


