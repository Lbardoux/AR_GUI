/**
 * @file CursorListener.cpp
 */


#include "CursorListener.hpp"
#include "clamp.hpp"


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

Cursor::Cursor(const Interval& hor, const Interval& ver, uint32_t x, uint32_t y) noexcept : vertical(ver),
                                                                                            horizontal(hor),
                                                                                            _x(x),
                                                                                            _y(y)
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
    this->vertical.min   = 0u;
    this->vertical.max   = 0u;
    this->horizontal.min = 0u;
    this->horizontal.max = 0u;
}
