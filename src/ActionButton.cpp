/**
 * @file ActionButton.cpp
 */


#include "ActionButton.hpp"
#include "TextPutter.hpp"

ActionButton::ActionButton(void)
{

}

ActionButton::ActionButton(Sprite* image, const std::string& action) : TouchButton(image), text(action)
{
    
}

ActionButton::~ActionButton()
{

}

void ActionButton::action()
{
    this->function();
}

void ActionButton::init(const std::string& action, std::function<void(void)> function, Sprite* image, int x, int y, double seconde)
{
	TouchButton::init(image, x, y, seconde);
	this->text = action;
	this->function = function;
}

void ActionButton::draw(Sprite& frame)
{
	const int PIXELS_DOWN = 12;
    this->TouchButton::draw(frame);

    if(this->text.empty())
    	return;

	TextPutter().pos(this->x(), this->y() + this->sprite->rows + PIXELS_DOWN)
	            .fontSize(0.6f)
	            .rgb(25, 25, 25)
	            .write(frame, this->text);
}

std::string& ActionButton::getText(void) noexcept
{
    return this->text;
}

const std::string& ActionButton::getText(void) const noexcept
{
    return this->text;
}

