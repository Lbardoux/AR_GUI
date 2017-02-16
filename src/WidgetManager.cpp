#include "WidgetManager.hpp"

Widget::Widget() : firstActiveTime(0)
{}
Widget::~Widget()
{}

bool Widget::isUnderCursor(UNUSED(const Cursor& cursor))
{
    return changeFirstActivation(false);
}

bool Widget::changeFirstActivation(bool underCursor)
{
    if (underCursor)
    {
        if (this->firstActiveTime == 0)
            time(&this->firstActiveTime);
    }
    else
        this->firstActiveTime = 0;

    return underCursor;
}

void Widget::setActivationTime(double seconde)
{
    this->activationTime = seconde;
}

bool Widget::isActivated() const
{
    time_t timer;
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    //mtl::log::info(difftime(timer, this->firstActiveTime));
    return (difftime(timer, this->firstActiveTime) >= (this->activationTime - 1.0f));
}

void Widget::action()
{}

void Widget::draw(UNUSED(cv::Mat& frame))
{}

uint32_t Widget::x() const
{
    return _x;
}
uint32_t& Widget::x()
{
    return _x;
}
uint32_t Widget::y() const
{
    return _y;
}
uint32_t& Widget::y()
{
    return _y;
}
