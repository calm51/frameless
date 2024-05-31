#ifndef UTILS_H
#define UTILS_H

#include "./__frameless_include__.h"
#include "./frameless.h"
#include "./titlebar/titlebarlikeandroid.h"
#include "./titlebar/titlebarlikewindows10.h"

FRAMELESS_BEGIN_NAMESPACE


template <typename T3, typename T4>
QPair<Frameless*,T3*> template_windows10(T4&w,const qint32 &titlebar_MinimumHeight,const qint32 &button_MinimumWidth=40){
    Frameless *fl = new Frameless(&w);
    fl->titlebar_MinimumHeight = titlebar_MinimumHeight; // 24-40 28-44 28-46
    fl->init(w); fl->loadthemesetting(); w.fl = fl;
#ifndef Q_OS_ANDROID
    TitlebarLikeWindows10 *titlebar = new TitlebarLikeWindows10(fl,button_MinimumWidth,&w);
    titlebar->loadthemesetting();
    titlebar->setWindowIcon(w.windowIcon());
    fl->set_titlebar(*titlebar);
#else
    TitlebarLikeAndroid *titlebar = new TitlebarLikeAndroid(fl,&w);
    titlebar->loadthemesetting();
    titlebar->setFixedHeight(fl->titlebar_MinimumHeight);
    fl->set_titlebar(*titlebar);
#endif
    QPair<Frameless*,T3*> pair; pair.first = fl; pair.second = titlebar;
    return pair;
}


FRAMELESS_END_NAMESPACE
#endif // UTILS_H
