/**
 * @file TextPutter.cpp
 */


#include "TextPutter.hpp"
// cv::HersheyFonts

TextPutter::TextPutter(void) noexcept : red(0), green(0), blue(0),
                                        x(0), y(0),
                                        face(_HERSHEY_FONT_NS_::FONT_HERSHEY_SIMPLEX),
                                        size(1.0f)
{
    
}

TextPutter& TextPutter::rgb(uint8_t r, uint8_t g, uint8_t b) noexcept
{
    this->red   = r;
    this->blue  = b;
    this->green = g;
    return *this;
}

TextPutter& TextPutter::fontSize(float s) noexcept
{
    this->size = s;
    return *this;
}

TextPutter& TextPutter::pos(int x, int y) noexcept
{
    this->x = x;
    this->y = y;
    return *this;
}

TextPutter& TextPutter::font(_HERSHEY_TYPE_NS_ enumValue) noexcept
{
    this->face = enumValue;
    return *this;
}

TextPutter& TextPutter::write(cv::Mat& dst, const std::string& text)
{
    cv::putText(dst, text, cvPoint(this->x, this->y), this->face, this->size,
                cvScalar(this->red ,this->green, this->blue), 1, CV_AA);
    return *this;
}


