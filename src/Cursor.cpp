/**
 * @file Cursor.cpp
 */


#include "Cursor.hpp"
#include "clamp.hpp"
#include "Cv_core.hpp"


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

Cursor::Cursor() noexcept :
    vertical({0,0}),
    horizontal({0,0}),
    _x(0),
    _y(0),
    _radius(0)
{
    
}

Cursor::Cursor(const Interval& hor, const Interval& ver, uint32_t x, uint32_t y, uint32_t radius) noexcept :
    vertical(ver),
    horizontal(hor),
    _x(x),
    _y(y),
    _radius(radius)
{
    clampInterval(this->_x, this->horizontal);
    clampInterval(this->_y, this->vertical);
}

Cursor::Cursor(const Cursor& other) noexcept : Cursor(other.horizontal, other.vertical, other._x, other._y)
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
    this->_radius        = 0u;
    this->vertical.min   = 0u;
    this->vertical.max   = 0u;
    this->horizontal.min = 0u;
    this->horizontal.max = 0u;
}

uint32_t Cursor::x(void) const noexcept
{
    return this->_x;
}

uint32_t Cursor::y(void) const noexcept
{
    return this->_y;
}

uint32_t Cursor::radius(void) const noexcept
{
    return this->_radius;
}

Cursor& Cursor::x(uint32_t value) noexcept
{
    this->_x = value;
    clampInterval(this->_x, this->horizontal);
    return *this;
}

Cursor& Cursor::y(uint32_t value) noexcept
{
    this->_y = value;
    clampInterval(this->_y, this->vertical);
    return *this;
}

Cursor& Cursor::radius(uint32_t value) noexcept
{
    this->_radius = value;
    return *this;
}

Cursor& Cursor::operator=(const Cursor& cursor)
{
    this->vertical   = cursor.vertical;
    this->horizontal = cursor.horizontal;
    this->_x         = cursor._x;
    this->_y         = cursor._y;
    this->_radius    = cursor._radius;

    return *this;
}

void Cursor::draw(cv::Mat& frame, const mat_data_t& color) const noexcept
{
    Interval bornesX, bornesY;

    // frame.cols; // x
    if(this->_x < this->_radius)
        bornesX.min = 0;
    else
        bornesX.min = this->_x - this->_radius;
    if(this->_x + this->_radius >= static_cast<uint32_t>(frame.cols))
        bornesX.max = frame.cols - 1;
    else
        bornesX.max = 0;
    
    // frame.rows; // y
    if(this->_y < this->_radius)
        bornesY.min = 0;
    else
        bornesY.min = this->_x - this->_radius;
    if(this->_y + this->_radius >= static_cast<uint32_t>(frame.rows))
        bornesY.max = frame.rows - 1;
    else
        bornesY.max = 0;

    for(uint32_t x = bornesX.min; x < bornesX.max; ++x)
        for(uint32_t y = bornesY.min; y < bornesY.max; ++y)
            matAt(frame, x, y) = color;
}



