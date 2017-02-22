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

ActionButton::~ActionButton(void)
{
    
}

void ActionButton::action()
{
    this->function();
}

void ActionButton::init(const std::string& action, std::function<void(void)> function, Sprite* image,
                        int x, int y, double seconde)
{
    TouchButton::init(image, x, y, seconde);
    this->text = action;
    this->function = function;
}

void ActionButton::draw(Sprite& frame)
{
    this->TouchButton::draw(frame);
    // On n'affiche pas le texte, on verra plus tard.
}

std::string& ActionButton::getText(void) noexcept
{
    return this->text;
}

const std::string& ActionButton::getText(void) const noexcept
{
    return this->text;
}
