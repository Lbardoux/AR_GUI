/**
 * @file Cursor.cpp
 */


#include "Cursor.hpp"
#include "clamp.hpp"
#include "Cv_core.hpp"

Interval Cursor::horizontal;
Interval Cursor::vertical;

namespace
{
    /**
     * @brief Applique clamp sur un intervalle.
     * @param[in,out] v     La valeur a éditer (@b x ou @b y ).
     * @param[in]     inter L'intervalle avec lequel tester.
     */
    void clampInterval(uint32_t& v, const Interval& inter) noexcept
    {
        clamp(v, inter.min, inter.max);
    }
}


//////////////////////////////////////////////////////////////////////////////////////
///////// Partie sur Cursor
//////////////////////////////////////////////////////////////////////////////////////


Cursor::Cursor(uint32_t x, uint32_t y) noexcept :
    _x(x),
    _y(y)
{
    clampInterval(this->_x, Cursor::horizontal);
    clampInterval(this->_y, Cursor::vertical);
}

Cursor::Cursor(const Cursor& other) noexcept : Cursor(other._x, other._y)
{
    
}

Cursor::Cursor(Cursor&& other) noexcept : Cursor(other)
{
    other.reset();
}

Cursor::~Cursor(void) noexcept
{
    this->reset();
}

void Cursor::reset(void) noexcept
{
    this->_x             = 0u;
    this->_y             = 0u;
}

uint32_t Cursor::x(void) const noexcept
{
    return this->_x;
}

uint32_t Cursor::y(void) const noexcept
{
    return this->_y;
}

Cursor& Cursor::x(uint32_t value) noexcept
{
    this->_x = value;
    clampInterval(this->_x, Cursor::horizontal);
    return *this;
}

Cursor& Cursor::y(uint32_t value) noexcept
{
    this->_y = value;
    clampInterval(this->_y, Cursor::vertical);
    return *this;
}

Cursor& Cursor::operator=(const Cursor& cursor)
{
    this->_x         = cursor._x;
    this->_y         = cursor._y;

    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
///////// Partie sur ColoredCursor
//////////////////////////////////////////////////////////////////////////////////////

ColoredCursor::ColoredCursor(uint32_t x, uint32_t y, uint32_t radius) :
    Cursor(x, y),
    _radius(radius),
    _spr((radius * 2) + 1, (radius * 2) + 1, CV_8UC4),
    _color(0, 0, 0, 1)
{
    setColor(this->_color);
}

ColoredCursor::~ColoredCursor()
{
    
}

void ColoredCursor::setColor(const mat_data_t& color)
{
    this->_color = color;

    for(int i = 0; i < _spr.cols; ++i)
        for(int j = 0; j < _spr.rows; ++j)
            matAt(_spr, i, j) = color;
}

uint32_t ColoredCursor::radius(void) const noexcept
{
    return this->_radius;
}

ColoredCursor& ColoredCursor::radius(uint32_t value) noexcept
{
    this->_radius = value;

    cv::resize(_spr, _spr, cv::Size((this->_radius * 2) + 1, (this->_radius * 2) + 1));
    setColor(this->_color);

    return *this;
}


ColoredCursor& ColoredCursor::operator=(const ColoredCursor& c)
{
    (Cursor)*this = (Cursor)c;
    this->_radius = c.radius();
    this->_spr    = c._spr;
    this->_color  = c._color;

    return *this;
}

ColoredCursor& ColoredCursor::operator=(const mat_data_t& c)
{
    this->_color = c;

    return *this;
}



void ColoredCursor::reset(void) noexcept
{
    Cursor::reset();
    this->_radius = 0u;
}

void ColoredCursor::draw(cv::Mat& frame) const noexcept
{
    blit(frame, this->_spr, this->x(), this->y());
}

