#ifndef TITLEBARLIKEANDROID_H
#define TITLEBARLIKEANDROID_H

#include <QWidget>

#include "../__frameless_include__.h"

namespace Ui {
class TitlebarLikeAndroid;
}


FRAMELESS_BEGIN_NAMESPACE

class Frameless;

class LIB_EXPORT TitlebarLikeAndroid : public QWidget
{
    Q_OBJECT

public:
    explicit TitlebarLikeAndroid(Frameless *fl,  QWidget *parent = nullptr);
    ~TitlebarLikeAndroid();

    Frameless *fl = nullptr;

    void load();
    void loadthemesetting();

    int border_top_width = 1;
    int border_bottom_width = 1;
    QList<QColor> colors = {

        QColor(241,241,241), // all buttom background color

        QColor(167,240,178), // border top color
        QColor(238,238,238) // border bottom color

    };

    Ui::TitlebarLikeAndroid *ui;

private:
    QWidget *_window=nullptr;
    void load_round4(bool en=true);


};


FRAMELESS_END_NAMESPACE
#endif // TITLEBARLIKEANDROID_H
