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
