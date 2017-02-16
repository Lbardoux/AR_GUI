/**
 * @file TextPutter.hpp
 * @brief Offers a more simplier way to display text on a cv::Mat
 * @author MTLCRBN
 * @author Zelnes
 * @version 1.0
 */
#ifndef OPENCV_TEXTPUTTER_HPP_INCLUDED
#define OPENCV_TEXTPUTTER_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#if CV_MAJOR_VERSION < 3
    #define _HERSHEY_FONT_NS_ cv
    #define _HERSHEY_TYPE_NS_ int
#else
    #define _HERSHEY_FONT_NS_ cv::HersheyFonts
    #define _HERSHEY_TYPE_NS_ cv::HersheyFonts
#endif


/**
 * @class TextPutter
 * @brief Embeds calls to cv::putText by simplyfying arguments settings.
 */
class TextPutter final
{
    public:
        //! @brief Create a simple TextPutter to work with.
        TextPutter(void) noexcept;
        /**
         * @brief Sets the color of the text.
         * @param[in] r The red   value.
         * @param[in] g The green value.
         * @param[in] b The blue  value.
         * @return *this
         */
        TextPutter& rgb(uint8_t r, uint8_t g, uint8_t b) noexcept;
        /**
         * @brief Multiply the default font size by @b s.
         * @param[in] s The desired size factor.
         * @return *this
         * 
         * As an example, 1.2f will increase the default size by 20%.
         */
        TextPutter& fontSize(float s) noexcept;
        /**
         * @brief Sets the origin of the text (centered at bottom-left).
         * @param[in] x The column number.
         * @param[in] y The row    number.
         * @return *this
         */
        TextPutter& pos(int32_t x, int32_t y) noexcept;
        /**
         * @brief Sets the font type to use.
         * @param[in] enumValue One of the following values (prefixed by _HERSHEY_FONT_NS_::).
         *    - FONT_HERSHEY_SIMPLEX
         *    - FONT_HERSHEY_PLAIN
         *    - FONT_HERSHEY_DUPLEX
         *    - FONT_HERSHEY_COMPLEX
         *    - FONT_HERSHEY_TRIPLEX
         *    - FONT_HERSHEY_COMPLEX_SMALL
         *    - FONT_HERSHEY_SCRIPT_SIMPLEX
         *    - FONT_HERSHEY_SCRIPT_COMPLEX
         *    - FONT_ITALIC
         * 
         * @return *this
         */
        TextPutter& font(_HERSHEY_TYPE_NS_ enumValue) noexcept;
        /**
         * @brief Put @b text on @b dst, using the currently setted values.
         * @param[in,out] dst  The cv::Mat to display on.
         * @param[in]     text The text you wanna display..
         * @return *this
         */
        TextPutter& write(cv::Mat& dst, const std::string& text);
    
    private:
        uint8_t           red;   //!< The red   value [0, 255] for the text color.
        uint8_t           green; //!< The green value [0, 255] for the text color.
        uint8_t           blue;  //!< The blue  value [0, 255] for the text color.
        int32_t           x;     //!< The <b>x</b>th column for the text origin.
        int32_t           y;     //!< The <b>y</b>th row    for the text origin.
        _HERSHEY_TYPE_NS_ face;  //!< The font setting.
        float             size;  //!< The font size factor.
    
};

#endif
