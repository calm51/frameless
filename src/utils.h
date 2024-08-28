#ifndef UTILS_H
#define UTILS_H

#include "./__frameless_include__.h"
#include "./frameless.h"
#include "./titlebar/titlebarlikeandroid.h"
#include "./titlebar/titlebarlikewindows10.h"

FRAMELESS_BEGIN_NAMESPACE


template <typename T3, typename T4>
QPair<Frameless*,T3*> template_windows10(T4&w,const qint32 &titlebar_MinimumHeight,const qint32 &button_MinimumWidth=40,const qint32 &titlebar_FixedHeight=-1){
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
    if (titlebar_FixedHeight>-1){
        titlebar->setFixedHeight(titlebar_FixedHeight);
    }
    fl->resizeto();
    QPair<Frameless*,T3*> pair; pair.first = fl; pair.second = titlebar;
    return pair;
}


#ifndef _FRAMELESS_TEMPLATE_TOPLINE_COLOR
#define _FRAMELESS_TEMPLATE_TOPLINE_COLOR
namespace TopLineColor {
enum Flag{
    Red=1,
    Purple=2,
    Green=3,
    Blue=4
};
}
#endif // _FRAMELESS_TEMPLATE_TOPLINE_COLOR

template <typename T3>
void template_topline_color(QPair<Frameless*,T3*> &fl_tb, const TopLineColor::Flag &tlc){
    __global__ & fg = G();
    if (tlc==TopLineColor::Purple){
        if (fg.currentTheme==Theme::White){
            fl_tb.second->colors[9] = QColor(219,170,240);
        }else if (fg.currentTheme==Theme::Gray){
            fl_tb.second->colors[9] = QColor(82,54,95);
        }
    }else if (tlc==TopLineColor::Red){

    }

    fl_tb.second->load();
}


template <typename T1,typename T2>
void template_dialog_tocenter(T1 *dialog, T2 *parent){
    if (parent){
        const QRect &parentGeometry = parent->geometry();
        const QRect &childGeometry = dialog->geometry();
        const int &x = parentGeometry.x() + (parentGeometry.width() - childGeometry.width()) / 2;
        const int &y = parentGeometry.y() + (parentGeometry.height() - childGeometry.height()) / 2;
        dialog->move(x, y);
    }
}


FRAMELESS_END_NAMESPACE
#endif // UTILS_H
