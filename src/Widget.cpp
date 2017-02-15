#include "Widget.hpp"

Widget::Widget()
{}
Widget::~Widget()
{}

bool Widget::isUnderCursor(UNUSED(const Cursor& cursor)) const
{
	return false;
}

void Widget::setActivationTime(time_t time)
{
	this->activationTime = time;
}

bool Widget::isActivated() const
{
	return false;
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