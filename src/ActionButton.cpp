/**
 * @file ActionButton.cpp
 */


#include "ActionButton.hpp"
#include "TextPutter.hpp"


ActionButton::ActionButton(Sprite* image, const std::string& action) : TouchButton(image), text(action)
{
    
}

void ActionButton::action()
{
    
}

void ActionButton::draw(UNUSED(Sprite& frame))
{
	const int PIXELS_DOWN = 12;
    this->TouchButton::draw(frame);
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

