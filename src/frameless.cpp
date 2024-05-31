#include "frameless.h"
#pragma execution_character_set("utf-8")
#include <QThread>
#include <qapplication.h>
#include "./custom/widget_background.h"

#include <qtoolbutton.h>

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
#include "qx11info_x11.h"
#endif
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
#include <X11/Xlib.h>
#endif

#ifdef Q_OS_WIN
#include <windows.h>
#endif

//QCoreApplication::instance()
//QCoreApplication::notify();

FRAMELESS_BEGIN_NAMESPACE


Frameless::Frameless(QObject *parent)
    : QObject{parent}{

    connect(&GLOBAL.SIGNAL,&__signal__::themeChanged,this,[=](){
        this->loadthemesetting();
    });
}

Frameless::~Frameless(){
    //    DELETE_OBJ_IF_HAD_NEW(shadow);
    //    DELETE_OBJ_IF_HAD_NEW(titlebar_main_layout);
    //    DELETE_OBJ_IF_HAD_NEW(titlebar_main_widget);
    //    DELETE_OBJ_IF_HAD_NEW(central_main_layout);
    //    DELETE_OBJ_IF_HAD_NEW(central_main_widget);
    //    DELETE_OBJ_IF_HAD_NEW(background_main_layout);
    //    DELETE_OBJ_IF_HAD_NEW(background_main_widget);

    ____<<"~Frameless";
}

void Frameless::app(QApplication &a){
}

void Frameless::_new_widget(){
    //    _window->setWindowFlag(Qt::X11BypassWindowManagerHint,true);
    _window->setWindowFlag(Qt::FramelessWindowHint);
    _window->setAttribute(Qt::WA_TranslucentBackground);
    _window->setAttribute(Qt::WA_StyledBackground);
    _window->setAttribute(Qt::WA_Hover);
    // _window->setMouseTracking(true);

    background_main_widget = new Widget_background(_window);
    background_main_widget->setObjectName(QString("background_main_widget"));


    central_main_widget = new QWidget(_window);
    central_main_widget->setObjectName(QString("central_main_widget"));

    titlebar_main_widget = new QWidget(_window);
    titlebar_main_widget->setObjectName(QString("titlebar_main_widget"));
    titlebar_main_widget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    menubar_main_widget = new QWidget(_window);
    menubar_main_widget->setObjectName(QString("menubar_main_widget"));
    menubar_main_widget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    bottombar_main_widget = new QWidget(_window);
    bottombar_main_widget->setObjectName(QString("bottombar_main_widget"));
    bottombar_main_widget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    background_main_layout = new QGridLayout(background_main_widget);
    background_main_layout->setSpacing(0);

    central_main_layout = new QGridLayout(central_main_widget);
    central_main_layout->setSpacing(0);

    titlebar_main_layout = new QGridLayout(titlebar_main_widget);
    titlebar_main_layout->setContentsMargins(0,0,0,0);
    titlebar_main_layout->setSpacing(0);

    menubar_main_layout = new QGridLayout(menubar_main_widget);
    menubar_main_layout->setContentsMargins(0,0,0,0);
    menubar_main_layout->setSpacing(0);

    bottombar_main_layout = new QGridLayout(bottombar_main_widget);
    bottombar_main_layout->setContentsMargins(0,0,0,0);
    bottombar_main_layout->setSpacing(0);

    background_main_layout->addWidget(central_main_widget,0,0,1,1);

    central_main_layout->addWidget(titlebar_main_widget,0,0,1,1);
    central_main_layout->addWidget(menubar_main_widget,1,0,1,1);
    central_main_layout->addWidget(central_widget,2,0,1,1);
    central_main_layout->addWidget(bottombar_main_widget,3,0,1,1);

#ifndef Q_OS_ANDROID
    shadow = new QGraphicsDropShadowEffect(central_main_widget);
    central_main_widget->setGraphicsEffect(shadow);
#endif

}

void Frameless::init(QMainWindow &w){
    this->_window = &w;
    central_widget = w.centralWidget();
    _new_widget();
    w.setCentralWidget(background_main_widget);
#ifndef Q_OS_ANDROID
    w.installEventFilter(this);
#endif
}

void Frameless::init(QWidget &w){

}

void Frameless::init(QDialog &w){
    this->_window = &w;
    central_layout = qobject_cast<QGridLayout*>(w.layout());
    if (central_layout){
        auto lay = qobject_cast<QGridLayout*>(central_layout);
        lay->setContentsMargins(0,0,0,0);
        lay->setSpacing(0);
        central_widget = lay->itemAt(0)->widget();
        _new_widget();
        lay->removeWidget(central_widget);
        lay->addWidget(background_main_widget,0,0,1,1);
    }else{
        central_layout = qobject_cast<QVBoxLayout*>(w.layout());
        if (central_layout){
            auto lay = qobject_cast<QVBoxLayout*>(central_layout);
            lay->setContentsMargins(0,0,0,0);
            lay->setSpacing(0);
            _new_widget();
            ____<<lay->count();
            for (int var = 0; var < lay->count(); ++var) {
                auto item = lay->itemAt(var);
                central_widget = item->widget();
                if (central_widget){
                    central_main_layout->addWidget(central_widget,var+1,0,1,1);
                }else{
                    central_main_layout->addLayout(item->layout(),var+1,0,1,1);
                }
                lay->removeItem(item);
            }
            lay->addWidget(background_main_widget,0);
        }

    }

#ifndef Q_OS_ANDROID
    w.installEventFilter(this);
#endif
}

void Frameless::load(){
    if (titlebar_MinimumHeight<=0){
        titlebar_MinimumHeight = 4;
    }
    background_main_widget->setStyleSheet("#background_main_widget{"
                                          "background:rgba(0,0,0,0);"
                                          "}");
    //    central_main_widget->setStyleSheet(QString(R"(
    //#central_main_widget{
    //background:%1;
    //border:solid; border-width:0px;
    //border-top-left-radius:%2px; border-top-right-radius:%3px;
    //border-bottom-left-radius:%4px; border-bottom-right-radius:%5px;
    //border:%6px solid %7;
    //})").arg(GLOBAL.qcolor2qss(colors.at(1)))
    //                                       .arg(QString::number(round4.at(0)),QString::number(round4.at(1)),QString::number(round4.at(2)),QString::number(round4.at(3)))
    //                                       .arg(QString::number(border_width),GLOBAL.qcolor2qss(colors.at(2))));
    //    titlebar_main_widget->setStyleSheet(QString(R"(
    //#titlebar_main_widget{
    //background:%1;
    //border:solid; border-width:0px;
    //border-top-left-radius:%2px; border-top-right-radius:%3px;
    //})").arg(GLOBAL.qcolor2qss(colors.at(0)))
    //                                        .arg(QString::number(round4.at(0)),QString::number(round4.at(1))));

    showNormal(true);

    titlebar_main_widget->setMinimumHeight(titlebar_MinimumHeight);

    central_main_layout->setContentsMargins(border_width,border_width,border_width,border_width);

    if (_window->isMaximized()){
#ifndef Q_OS_ANDROID
        if(shadow){
            shadow->setColor(shadow_color);
        }
#endif
    }else{
#ifndef Q_OS_ANDROID
        background_main_layout->setContentsMargins(shadow_size,shadow_size,shadow_size,shadow_size);
        if(shadow){
            shadow->setColor(shadow_color);
            shadow->setOffset(0, 0);
            shadow->setBlurRadius(shadow_size);
        }
#else
        background_main_layout->setContentsMargins(0,0,0,0);
#endif
    }

}

void Frameless::loadthemesetting(){
    shadow_size = GLOBAL.currentThemeConf().shadow_size;
    //    resize_rect_out = GLOBAL.theme_config[GLOBAL.currentTheme].resize_rect_out;
    //    resize_rect_in = GLOBAL.theme_config[GLOBAL.currentTheme].resize_rect_in;
    //    resize_rect_corner = GLOBAL.theme_config[GLOBAL.currentTheme].resize_rect_corner;
    shadow_color = GLOBAL.theme_config[GLOBAL.currentTheme].shadow_color;
    round4 = GLOBAL.theme_config[GLOBAL.currentTheme].round4;
    //    allow_showMaximized = GLOBAL.theme_config[GLOBAL.currentTheme].allow_showMaximized;
    //    allow_showMinimized = GLOBAL.theme_config[GLOBAL.currentTheme].allow_showMinimized;
    //    titlebar_MinimumHeight = GLOBAL.theme_config[GLOBAL.currentTheme].titlebar_MinimumHeight;
    border_width = GLOBAL.theme_config[GLOBAL.currentTheme].border_width;
    colors = GLOBAL.theme_config[GLOBAL.currentTheme].Frameless_colors;

    load();

    //#ifdef Q_OS_ANDROID
    //    if (GLOBAL.currentTheme=="Dark"){
    //        QtAndroid::runOnAndroidThread([]() {
    //            QAndroidJniObject activity = QtAndroid::androidActivity();
    //            activity.callMethod<void>("toStatusbarTextWhite", "()V");
    //        });
    //    }else{
    //        QtAndroid::runOnAndroidThread([]() {
    //            QAndroidJniObject activity = QtAndroid::androidActivity();
    //            activity.callMethod<void>("toStatusbarTextBlack", "()V");
    //        });
    //    }
    //#endif

}


void Frameless::set_titlebar(QWidget &titlebar){
    titlebar_widget = &titlebar;
    titlebar_main_layout->addWidget(&titlebar,0,0,1,1);
#ifndef Q_OS_ANDROID
    foreach (QWidget*wi, titlebar.findChildren<QToolButton*>()) {
        wi->installEventFilter(this);
    }
#endif
}

bool Frameless::is_titlebar(const QPoint &pos){
    int x = pos.x();
    int y = pos.y();
#ifndef Q_OS_ANDROID
    if (!_window->isMaximized()){
        x-=shadow_size; y-=shadow_size;

    }
#endif
    if (x<0 || y<0){return false;}
    if (y > titlebar_main_widget->height() || x > titlebar_main_widget->width()){
        return false;
    }
    return true;
}

QPair<bool,Qt::Edges> Frameless::is_allow_resize(const QPoint &pos){
    const int & _central_width = central_main_widget->width();
    const int & _central_height = central_main_widget->height();
    bool b = true;
    Qt::Edges n;
    if (_window->isMaximized() || m_isPressButton){
        b = false;
        SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::ArrowCursor);
    }else if (resize_rect_out < pos.x() && pos.x() < shadow_size + resize_rect_in &&
              resize_rect_out < pos.y() && pos.y() < shadow_size + resize_rect_in){
        n = Qt::TopEdge | Qt::LeftEdge;
        SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeFDiagCursor);
    }else if (_central_width+shadow_size-resize_rect_in < pos.x() && pos.x() < _central_width+shadow_size+resize_rect_out &&
              resize_rect_out < pos.y() && pos.y() < shadow_size + resize_rect_in){
        n = Qt::TopEdge | Qt::RightEdge;
        SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeBDiagCursor);
    }else if (resize_rect_out < pos.x() && pos.x() < shadow_size + resize_rect_in &&
              _central_height+shadow_size-resize_rect_in < pos.y() && pos.y() < _central_height+shadow_size+resize_rect_out ){
        n = Qt::BottomEdge | Qt::LeftEdge;
        SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeBDiagCursor);
    }else if (_central_width+shadow_size-resize_rect_in < pos.x() && pos.x() < _central_width+shadow_size+resize_rect_out &&
              _central_height+shadow_size-resize_rect_in < pos.y() && pos.y() < _central_height+shadow_size+resize_rect_out ){
        n = Qt::BottomEdge | Qt::RightEdge;
        SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeFDiagCursor);
    }else if (resize_rect_out < pos.x() && pos.x() < shadow_size + resize_rect_in &&
              shadow_size < pos.y() && pos.y() < shadow_size + _central_height ){
        if (pos.y()-shadow_size<resize_rect_corner){
            n = Qt::TopEdge | Qt::LeftEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeFDiagCursor);
        }else if (_central_height-(pos.y()-shadow_size)<resize_rect_corner){
            n = Qt::BottomEdge | Qt::LeftEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeBDiagCursor);
        }else{
            n =  Qt::LeftEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeHorCursor);
        }
    }else if (resize_rect_out < pos.y() && pos.y() < shadow_size + resize_rect_in &&
              shadow_size < pos.x() && pos.x() < shadow_size + _central_width ){
        if (pos.x()-shadow_size<resize_rect_corner){
            n = Qt::TopEdge | Qt::LeftEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeFDiagCursor);
        }else if (_central_width-(pos.x()-shadow_size)<resize_rect_corner){
            n = Qt::TopEdge | Qt::RightEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeBDiagCursor);
        }else{
            n =  Qt::TopEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeVerCursor);
        }
    }else if (_central_height+shadow_size-resize_rect_in < pos.y() && pos.y() < _central_height+shadow_size+resize_rect_out &&
              shadow_size < pos.x() && pos.x() < shadow_size + _central_width  ){
        if (pos.x()-shadow_size<resize_rect_corner){
            n = Qt::BottomEdge | Qt::LeftEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeBDiagCursor);
        }else if (_central_width-(pos.x()-shadow_size)<resize_rect_corner){
            n = Qt::BottomEdge | Qt::RightEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeFDiagCursor);
        }else{
            n =  Qt::BottomEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeVerCursor);
        }
    }else if (_central_width+shadow_size-resize_rect_in < pos.x() && pos.x() < _central_width+shadow_size+resize_rect_out &&
              shadow_size < pos.y() && pos.y() < shadow_size + _central_height){
        if (pos.y()-shadow_size<resize_rect_corner){
            n = Qt::TopEdge | Qt::RightEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeBDiagCursor);
        }else if (_central_height-(pos.y()-shadow_size)<resize_rect_corner){
            n = Qt::BottomEdge | Qt::RightEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeFDiagCursor);
        }else{
            n = Qt::RightEdge;
            SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::SizeHorCursor);
        }
    }else{
        b = false;
        SET_CURSOR_IF_NOT_SPECIFIED(_window, Qt::ArrowCursor);
    }
    QPair<bool,Qt::Edges> bn;
    bn.first = b;
    bn.second = n;
    return bn;
}

void Frameless::set_menubar(QWidget &menubar){
    //    menubar_widget = &menubar;
    menubar_main_layout->addWidget(&menubar,0,0,1,1);
    //#ifndef Q_OS_ANDROID
    //    foreach (QWidget*wi, menubar.findChildren<QToolButton*>()) {
    //        wi->installEventFilter(this);
    //    }
    //#endif
}

void Frameless::set_bottombar(QWidget &bottombar){
    bottombar_main_layout->addWidget(&bottombar,0,0,1,1);
}

void Frameless::showMaximized(bool only_update_round){
#ifdef Q_OS_ANDROID
    return;
#endif
    if (!allow_showMaximized){return;}

    if (!only_update_round){
        rectAfterMaximized = _window->geometry();
        if (shadow){
            shadow->setBlurRadius(0);
            delete shadow;shadow=nullptr;
            central_main_widget->setGraphicsEffect(nullptr);
        }
        background_main_layout->setContentsMargins(0,0,0,0);
        this->_window->showMaximized();
    }
    central_main_widget->setStyleSheet(QString(R"(
#central_main_widget{
background:%1;
border:solid; border-width:0px;
border-top-left-radius:0px; border-top-right-radius:0px;
border-bottom-left-radius:0px; border-bottom-right-radius:0px;
border:%6px solid %7;
})").arg(GLOBAL.qcolor2qss(colors.at(1)))
                                       .arg(QString::number(border_width),GLOBAL.qcolor2qss(colors.at(2))));
    titlebar_main_widget->setStyleSheet(QString(R"(
#titlebar_main_widget{
background:%1;
border:solid; border-width:0px;
border-top-left-radius:0px; border-top-right-radius:0px;
})").arg(GLOBAL.qcolor2qss(colors.at(0))));

    if (!only_update_round){
        emit this->windowStateChanged(this->_window->windowState());
    }
}

void Frameless::showNormal(bool only_update_round){
#ifndef Q_OS_ANDROID
    if (!only_update_round){
        this->_window->showNormal();
    }
#endif
    const bool &_isMaximized = this->_window->isMaximized();
    central_main_widget->setStyleSheet(QString(R"(
#central_main_widget{
background:%1;
border:solid; border-width:0px;
border-top-left-radius:%2px; border-top-right-radius:%3px;
border-bottom-left-radius:%4px; border-bottom-right-radius:%5px;
border:%6px solid %7;
})").arg(GLOBAL.qcolor2qss(colors.at(1)))
                                       .arg(QString::number(_isMaximized?0:round4.at(0)),QString::number(_isMaximized?0:round4.at(1)),QString::number(_isMaximized?0:round4.at(2)),QString::number(_isMaximized?0:round4.at(3)))
                                       .arg(QString::number(border_width),GLOBAL.qcolor2qss(colors.at(2))));
    titlebar_main_widget->setStyleSheet(QString(R"(
#titlebar_main_widget{
background:%1;
border:solid; border-width:0px;
border-top-left-radius:%2px; border-top-right-radius:%3px;
})").arg(GLOBAL.qcolor2qss(colors.at(0)))
                                        .arg(QString::number(_isMaximized?0:round4.at(0)),QString::number(_isMaximized?0:round4.at(1))));
#ifndef Q_OS_ANDROID
    if (!only_update_round){
        shadow = new QGraphicsDropShadowEffect(central_main_widget);
        shadow->setColor(shadow_color);
        shadow->setOffset(0, 0);
        shadow->setBlurRadius(shadow_size);
        central_main_widget->setGraphicsEffect(shadow);
        background_main_layout->setContentsMargins(shadow_size,shadow_size,shadow_size,shadow_size);
    }
#endif

    if (!only_update_round){
        emit this->windowStateChanged(this->_window->windowState());
    }
}


#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
void Frameless::_x11_move_window(const WId &wid,const QPoint &pos){
    XEvent event;
    memset(&event, 0, sizeof(XEvent));
    Display *display = QX11Info::display();
    event.xclient.type = ClientMessage;
    event.xclient.message_type = XInternAtom(display, "_NET_WM_MOVERESIZE", False);
    event.xclient.display = display;
    event.xclient.window = wid;
    event.xclient.format = 32;
    event.xclient.data.l[0] = pos.x();
    event.xclient.data.l[1] = pos.y();
    event.xclient.data.l[2] = 8;
    event.xclient.data.l[3] = Button1;
    event.xclient.data.l[4] = 1;
    XUngrabPointer(display, CurrentTime);
    XSendEvent(display, QX11Info::appRootWindow(QX11Info::appScreen()),False, SubstructureNotifyMask | SubstructureRedirectMask,&event);
    XFlush(display);
}
#endif

bool Frameless::eventFilter(QObject *watched, QEvent *event){
#ifdef Q_OS_ANDROID
    return QObject::eventFilter(watched,event);
#endif

    //    if (!QList<QEvent::Type>({
    //                             QEvent::MouseButtonPress, QEvent::MouseMove ,QEvent::MouseButtonRelease,
    //                             QEvent::MouseButtonDblClick,
    //                             QEvent::HoverMove,QEvent::Move,QEvent::CursorChange,
    //                             QEvent::UpdateRequest,QEvent::Paint,
    //                             QEvent::LayoutRequest,QEvent::PolishRequest
    //}).contains(event->type())){
    //        ____<<watched<<event->type();
    //    }
    QWidget *_watched_widget = qobject_cast<QWidget*>(watched);
    const bool &_is_titlebar_child = _watched_widget && titlebar_widget && titlebar_widget->isAncestorOf(_watched_widget);
    if (watched==this->_window || _is_titlebar_child){
        if (event->type()==QEvent::MouseButtonPress){
            auto e = static_cast<QMouseEvent*>(event);
            if (_is_titlebar_child){
                const QPoint &_titlebar_child_globalpos = _watched_widget->mapToGlobal(e->pos());
                const QPoint &_titlebar_child_topos = _window->mapFromGlobal(_titlebar_child_globalpos);
                if(e->button()==Qt::LeftButton){
                    QPair<bool,Qt::Edges> _bn = is_allow_resize(_titlebar_child_topos);
                    if(_bn.first){
                        e->ignore();
                        return true;
                    }else{
                        m_isPressButton = true;
                        return QObject::eventFilter(watched,event);
                    }
                }else{
                    return QObject::eventFilter(watched,event);
                }
            }else{
                if(e->button()==Qt::LeftButton){
                    QPair<bool,Qt::Edges> _bn = is_allow_resize(e->pos());
                    if(is_titlebar(e->pos()) && !_bn.first){
                        //#ifdef Q_OS_LINUX
                        //                if (w->isMaximized()){
                        //                    shadow->setBlurRadius(shadow_size);
                        //                    background_main_layout->setContentsMargins(shadow_size,shadow_size,shadow_size,shadow_size);
                        //                }
                        //                w->windowHandle()->startSystemMove();
                        //                e->accept();
                        //                return true;
                        //#else
                        m_isPress = true;
                        m_pressPos = e->pos();
                        m_pressGlobalPos = e->globalPos();
                        m_pressWindowGlobalPos = _window->pos();
                        this->_window->setCursor(Qt::ArrowCursor);
                    }else if(_bn.first){
                        _window->windowHandle()->startSystemResize(_bn.second);
                        e->accept();
                        return true;
                    }
                }
            }

            //            ____<< e << "鼠标按下";
        }else if (event->type()==QEvent::MouseMove){
            if (_is_titlebar_child){
                m_isPressButton = true;
                return QObject::eventFilter(watched,event);}
            auto e = static_cast<QMouseEvent*>(event);
            if (m_isPress){
                if (_window->isMaximized()){
                    QSize s = _window->size();
                    showNormal();
                    //                    shadow->setBlurRadius(shadow_size);
                    //                    w->showNormal();
                    //                    background_main_layout->setContentsMargins(shadow_size,shadow_size,shadow_size,shadow_size);

                    //#ifdef Q_OS_LINUX
                    //   qApp->processEvents();
                    //   QThread::msleep(200);
                    //#endif
                    //                    ____<<rectAfterMaximized<<w->geometry();
                    //                    w->setGeometry(-shadow_size+m_pressGlobalPos.x()-((double)m_pressGlobalPos.x() / s.width()*(rectAfterMaximized.width()-(shadow_size*2))),
                    //                                   m_pressGlobalPos.y()-((double)m_pressGlobalPos.y() / titlebar_main_widget->height()*titlebar_main_widget->height())-shadow_size,
                    //                                   rectAfterMaximized.width(),rectAfterMaximized.height());
                    int x = 0;
                    if (m_pressGlobalPos.x()<rectAfterMaximized.width()/2){
                        x = -shadow_size;
                    }else if (s.width()-m_pressGlobalPos.x()<rectAfterMaximized.width()/2){
                        x = (s.width()-rectAfterMaximized.width())+shadow_size;
                    }else{
                        x = m_pressGlobalPos.x()-(rectAfterMaximized.width()/2);
                    }
                    _window->setGeometry(x,
                                         m_pressGlobalPos.y()-((double)m_pressGlobalPos.y() / titlebar_main_widget->height()*titlebar_main_widget->height())-shadow_size,
                                         rectAfterMaximized.width(),rectAfterMaximized.height());
                    m_pressPos = e->pos();
                    m_pressGlobalPos = e->globalPos();
                    m_pressWindowGlobalPos = _window->pos();

                }else{
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
                    _x11_move_window(_window->winId(), m_pressGlobalPos);
                    m_isPress = false;
#else
                    QPoint pos = m_pressWindowGlobalPos;
                    pos += e->globalPos()-m_pressGlobalPos;
                    _window->move(pos);
#endif
                }
            }
            //            ____ << e<< "鼠标移动";
        }else if (event->type()==QEvent::MouseButtonRelease){
            auto e = static_cast<QMouseEvent*>(event);
            if (_is_titlebar_child || m_isPressButton){
                m_isPressButton = false;
                const QPoint &_titlebar_child_globalpos = _watched_widget->mapToGlobal(e->pos());
                const QPoint &_titlebar_child_topos = _window->mapFromGlobal(_titlebar_child_globalpos);
                if(e->button()==Qt::LeftButton){
                    QPair<bool,Qt::Edges> _bn = is_allow_resize(_titlebar_child_topos);
                    if(_bn.first){
                        e->ignore();
                        return true;
                    }else{
                        return QObject::eventFilter(watched,event);
                    }
                }else{
                    return QObject::eventFilter(watched,event);
                }
            }
            if (m_isPress){
                m_isPress = false;
                this->_window->setCursor(Qt::ArrowCursor);
            }
            if(e->button()==Qt::RightButton){

            }
            //            ____<< e << "鼠标松开";
        }else if (event->type()==QEvent::MouseButtonDblClick){
            if (_is_titlebar_child){
                return QObject::eventFilter(watched,event);}
            auto e = static_cast<QMouseEvent*>(event);
            if(e->button()==Qt::LeftButton){
                QPair<bool,Qt::Edges> _bn = is_allow_resize(e->pos());
                if(_bn.first && _bn.second!=Qt::TopEdge && _bn.second!=Qt::BottomEdge){

                }else if(_bn.first &&(_bn.second==Qt::TopEdge || _bn.second==Qt::BottomEdge)){ // 单方向最大化

                }else{
                    if(this->is_titlebar(e->pos())){
                        if (_window->isMaximized()){
                            showNormal();
                            //                        w->showNormal();
                            //                        shadow->setBlurRadius(shadow_size);
                            //                        background_main_layout->setContentsMargins(shadow_size,shadow_size,shadow_size,shadow_size);
                        }else{
                            //                        rectAfterMaximized = w->geometry();
                            //                        shadow->setBlurRadius(0);
                            //                        background_main_layout->setContentsMargins(0,0,0,0);
                            //                        w->showMaximized();
                            showMaximized();
                            is_allow_resize(e->pos());
                        }
                    }
                }
            }
            //            ____<< e << "鼠标双击";
        }else if (event->type()==QEvent::HoverMove){
            auto e = static_cast<QHoverEvent*>(event);
            //            ____ << e<< "鼠标悬停";
            if (is_allow_resize(e->pos()).first){
                //                ____<<"允许缩放11111111111111";
            }else{
                //                ____<<"不允许缩放2222222222222222";
            }
        }else if (event->type()==QEvent::Leave){
            auto e = static_cast<QEvent*>(event);
            //            ____ << e<< "鼠标离开";
        }else if (event->type()==QEvent::ActivationChange){
            auto e = static_cast<QEvent*>(event);
            //            ____ << e <<"ActivationChange";
        }else if (event->type()==QEvent::WindowDeactivate){
            auto e = static_cast<QEvent*>(event);
            //            ____ << e<< "WindowDeactivate";
        }else if (event->type()==QEvent::WindowActivate){
            auto e = static_cast<QEvent*>(event);
            //            ____ << e<< "WindowActivate";
        }else if (event->type()==QEvent::WindowStateChange){
            QWindowStateChangeEvent *stateChangeEvent = static_cast<QWindowStateChangeEvent *>(event);
            //            ____<<"WindowStateChange"<<stateChangeEvent<<_window->isMaximized();
            if (_window->isMaximized()){
                const auto &geometry = _window->geometry();
                if (geometry.x()!=0 && geometry.y()!=0){
                    rectAfterMaximized = _window->geometry();
                }
                if(shadow){
                    shadow->setBlurRadius(0);
                }
                background_main_layout->setContentsMargins(0,0,0,0);
                showMaximized(true);
            }
        }
    }

    return QObject::eventFilter(watched,event);
}

bool Frameless::nativeEventFilter(const QByteArray &eventType, void *message, long *result){
    //    qDebug() << eventType<<message<<result;
    //    if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG"){
    //        MSG * pMsg = reinterpret_cast<MSG *>(message);

    //        if (pMsg->message == WM_NCMOUSEMOVE)
    //        {
    //            qDebug() <<QString("获取到系统鼠标移动，可以做像qq一样的忙碌检测");
    //        }
    //    }

    return false;
}

//struct MSG {
//    void* hwnd;
//    UINT message;
//    WPARAM wParam;
//    LPARAM lParam;
//    DWORD time;
//    POINT pt;
//    DWORD lPrivate;
//};
bool Frameless::nativeEvent(const QByteArray &eventType, void *message, long *result){
#ifdef Q_OS_WIN
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg->message == 134 && shadow) {
        if (qobject_cast<QDialog*>(this->_window)) {
            if (msg->wParam){
                if (shadow->blurRadius()!=shadow_size){
                    // shadow->setBlurRadius(0);
                    shadow->setBlurRadius(shadow_size);
                }
            }else{
                int _2 = shadow_size/2;
                if (shadow->blurRadius()!=_2){
                    // shadow->setBlurRadius(0);
                    shadow->setBlurRadius(_2);
                }
            }
        }
    }
#endif
    return false;
}




FRAMELESS_END_NAMESPACE




