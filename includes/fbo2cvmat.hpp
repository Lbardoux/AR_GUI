/**
 * @file fbo2cvmat.hpp
 * @brief Offers a simple way to convert data from a FrameBufferObject (OpenGL)
 * to an OpenCV Matrix (cv::Mat).@n
 * 
 * You'll need an OpenGL context to call this module., in order to do so, defines -DINCLUDE_GL_CONTEXT="#include "...""
 * while compiling.
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef FBO2CVMAT_HPP_INCLUDED
#define FBO2CVMAT_HPP_INCLUDED

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#ifndef INCLUDE_GL_CONTEXT
    #define INCLUDE_GL_CONTEXT
#endif
INCLUDE_GL_CONTEXT
#include <GL/gl.h>
#include <type_traits>
#include <array>


//! @cond IGNORING_FROM_DOXYGEN
template<GLenum F> struct _GL_FORMAT_trait;
template<GLenum D> struct _GL_DATATYPE_trait;
template<GLenum F> struct _GL_FORMAT_size;
template<GLenum D> struct _GL_DATATYPE_size;
struct _OpenGL2OpenCV final;
//! @endcond


/**
 * @brief Stores the all content of @b fbo into @b out.
 * @param[in]  fbo    The ID of the FrameBufferObject you wanna extract data.
 * @param[out] out    The matrice to store the extraction.
 * @param[in]  width  The width of @b fbo.
 * @param[in]  height The height of @b fbo.
 * @tparam Format   A GLenum value to define the organization of a pixel.
 * @tparam Datatype The "type" of each value (how many bits for one value).
 */
template<GLenum Format = GL_RGBA, GLenum Datatype = GL_UNSIGNED_BYTE>
void fbo2cvmat(GLuint fbo, cv::Mat& out, GLint width, GLint height)
{
    static_assert(_GL_FORMAT_trait<Format>::value,     "Invalid GLenum for the pixel format !");
    static_assert(_GL_DATATYPE_trait<Datatype>::value, "Invalid GLenum for the pixel data type !");
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    
    int byteSizeRequired = width*height*_GL_FORMAT_size<Format>::value*_GL_DATATYPE_size<Datatype>::value;
    int byteSizeCurrent  = out.cols*out.rows*out.channels()*out.type();
    
    if (byteSizeCurrent != byteSizeRequired)
    {
        _OpenGL2OpenCV constGenerator;
        out = cv::Mat(height, width, constGenerator.get(_GL_FORMAT_size<Format>::value, Datatype));
    }
    glReadPixels(0, 0, width, height, Format, Datatype, out.data);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

//! @cond IGNORING_FROM_DOXYGEN
// Checks GL_ENUM validity ########################################################################
// For GL_ENUM ---> pixel color format
// Legal values are within TRUE_GL_FORMAT_TRAIT macro.
template<GLenum F> struct _GL_FORMAT_trait : public false_type {};
#define TRUE_GL_FORMAT_TRAIT(glenum) template<> struct GL_FORMAT_trait<glenum> : public true_type {}
TRUE_GL_FORMAT_TRAIT(GL_RED);
TRUE_GL_FORMAT_TRAIT(GL_GREEN);
TRUE_GL_FORMAT_TRAIT(GL_BLUE);
TRUE_GL_FORMAT_TRAIT(GL_RGB);
TRUE_GL_FORMAT_TRAIT(GL_BGR);
TRUE_GL_FORMAT_TRAIT(GL_RGBA);
TRUE_GL_FORMAT_TRAIT(GL_BGRA);
//TRUE_GL_FORMAT_TRAIT(GL_STENCIL_INDEX);
//TRUE_GL_FORMAT_TRAIT(GL_DEPTH_COMPONENT);
//TRUE_GL_FORMAT_TRAIT(GL_DEPTH_STENCIL);

// For GL_ENUM ---> pixel data type
// Same story, legal values are within TRUE_GL_DATATYPE_TRAIT
template<GLenum D> struct _GL_DATATYPE_trait : public false_type {};
#define TRUE_GL_DATATYPE_TRAIT(glenum) template<> struct GL_DATATYPE_trait<glenum> : public true_type {}
TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_BYTE);
TRUE_GL_DATATYPE_TRAIT(GL_BYTE);
TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_SHORT);
TRUE_GL_DATATYPE_TRAIT(GL_SHORT);
TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT);
TRUE_GL_DATATYPE_TRAIT(GL_INT);
TRUE_GL_DATATYPE_TRAIT(GL_FLOAT);
//TRUE_GL_DATATYPE_TRAIT(GL_HALF_FLOAT);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_BYTE_3_3_2);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_BYTE_2_3_3_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_SHORT_5_6_5);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_SHORT_5_6_5_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_SHORT_4_4_4_4);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_SHORT_4_4_4_4_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_SHORT_5_5_5_1);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_SHORT_1_5_5_5_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT_8_8_8_8);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT_8_8_8_8_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT_10_10_10_2);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT_2_10_10_10_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT_24_8);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT_10F_11F_11F_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_UNSIGNED_INT_5_9_9_9_REV);
//TRUE_GL_DATATYPE_TRAIT(GL_FLOAT_32_UNSIGNED_INT_24_8_REV);

// ################################################################################################

#define GL_FORMAT_SIZE(glenum, value) template<> struct GL_FORMAT_size<glenum> : public std::integral_constant<int, value> {}
GL_FORMAT_SIZE(GL_BGRA,  4);
GL_FORMAT_SIZE(GL_RGBA,  4);
GL_FORMAT_SIZE(GL_BGR,   3);
GL_FORMAT_SIZE(GL_RGB,   3);
GL_FORMAT_SIZE(GL_BLUE,  1);
GL_FORMAT_SIZE(GL_RED,   1);
GL_FORMAT_SIZE(GL_GREEN, 1);

#define GL_DATATYPE_SIZE(glenum, value) template<> struct GL_DATATYPE_size<glenum> : public std::integral_constant<int, value> {}
GL_DATATYPE_SIZE(GL_UNSIGNED_BYTE,  sizeof(unsigned char));
GL_DATATYPE_SIZE(GL_BYTE,           sizeof(char));
GL_DATATYPE_SIZE(GL_UNSIGNED_SHORT, sizeof(unsigned short));
GL_DATATYPE_SIZE(GL_SHORT,          sizeof(short));
GL_DATATYPE_SIZE(GL_UNSIGNED_INT,   sizeof(unsigned int));
GL_DATATYPE_SIZE(GL_INT,            sizeof(int));
GL_DATATYPE_SIZE(GL_FLOAT,          sizeof(float));

//8UC1,,3,4
//16UC1,,3,4
//32UC1,,3,4
//32FC1,,3,4
struct _OpenGL2OpenCV final
{
    std::array<int, 12> cv_const;
    //! @brief Fill the map
    _OpenGL2OpenCV(void)
    {
        cv_const.at(0)  = CV_8UC1;
        cv_const.at(1)  = CV_8UC3;
        cv_const.at(2)  = CV_8UC4;
        cv_const.at(3)  = CV_16UC1;
        cv_const.at(4)  = CV_16UC3;
        cv_const.at(5)  = CV_16UC4;
        cv_const.at(6)  = CV_32UC1;
        cv_const.at(7)  = CV_32UC3;
        cv_const.at(8)  = CV_32UC4;
        cv_const.at(9)  = CV_32FC1;
        cv_const.at(10)  = CV_32FC3;
        cv_const.at(11)  = CV_32FC4;
    }
    int get(int format, GLenum type)
    {
        int begin = 0;
        if (type == GL_FLOAT)
            begin = 9;
        if (type == GL_GL_UNSIGNED_SHORT || type == GL_SHORT)
            begin = 3;
        if (type == GL_GL_UNSIGNED_INT || type == GL_INT)
            begin = 6;
        return this->cv_const.at(begin + format/2);
    }
};

//! @endcond

#endif
