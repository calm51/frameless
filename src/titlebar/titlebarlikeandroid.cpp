﻿#include "titlebarlikeandroid.h"

#include "ui_titlebarlikeandroid.h"

#include <qpainter.h>
#include "../frameless.h"
#include <QPointer>
//#include "__frameless_include__.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

FRAMELESS_BEGIN_NAMESPACE


TitlebarLikeAndroid::TitlebarLikeAndroid(Frameless *fl,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitlebarLikeAndroid)
{
    ui->setupUi(this);
    this->fl = fl;
    this->_window = parent;

    connect(&GLOBAL.SIGNAL,&__signal__::themeChanged,this,[=](){this->loadthemesetting();});


}

TitlebarLikeAndroid::~TitlebarLikeAndroid(){
    delete ui;
    ____<<"~TitlebarLikeAndroid";
}




void TitlebarLikeAndroid::load(){
    //    this->setFixedHeight(fl.titlebar_MinimumHeight);
    load_round4();

}

void TitlebarLikeAndroid::loadthemesetting(){
    border_top_width = GLOBAL.theme_config[GLOBAL.currentTheme].border_top_width;
    border_bottom_width = GLOBAL.theme_config[GLOBAL.currentTheme].border_bottom_width;
    colors = GLOBAL.theme_config[GLOBAL.currentTheme].TitlebarLikeAndroid_colors;

    load();
}

void TitlebarLikeAndroid::load_round4(bool en){
    if (en){
        ui->widget->setStyleSheet(QString(R"(
QWidget#widget{
border:0px solid rgb(0,0,0);
border-top-width:%1px;
border-bottom-width:%2px;
border-top-color:%3;
border-bottom-color:%4;
border-top-left-radius:0px; border-top-right-radius:0px;
}
        )").arg(QString::number(border_top_width),QString::number(border_bottom_width),GLOBAL.qcolor2qss(colors.at(1)),GLOBAL.qcolor2qss(colors.at(2)))
                                  ); // .arg(QString::number(fl->round4.at(0)),QString::number(fl->round4.at(1)))
        // ui->widget_4->setContentsMargins(0,border_top_width,0,border_bottom_width);
    }else{
        ui->widget->setStyleSheet(QString(R"(
QWidget#widget{
border:0px solid rgb(0,0,0);
border-top-width:%1px;
border-bottom-width:%2px;
border-top-color:%3;
border-bottom-color:%4;
border-top-left-radius:0px; border-top-right-radius:0px;
}
        )").arg(QString::number(border_top_width),QString::number(border_bottom_width),GLOBAL.qcolor2qss(colors.at(1)),GLOBAL.qcolor2qss(colors.at(2)))
                                  );
    }

}


FRAMELESS_END_NAMESPACE
