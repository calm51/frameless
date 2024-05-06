#include "widget_background.h"

FRAMELESS_BEGIN_NAMESPACE

Widget_background::Widget_background(QWidget *parent)
    : QWidget{parent}
{

}

Widget_background::~Widget_background(){
    ____<<"~Widget_background";
}

FRAMELESS_END_NAMESPACE
