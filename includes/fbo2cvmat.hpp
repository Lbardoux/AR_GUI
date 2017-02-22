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
#include "GlContext.hpp"
#include <GL/gl.h>

/**
 * @brief Stores the all content of @b fbo into @b out.
 * @param[in]  fbo    The ID of the FrameBufferObject you wanna extract data.
 * @param[out] out    The matrice to store the extraction.
 * @param[in]  width  The width of @b fbo.
 * @param[in]  height The height of @b fbo.
 */
void fbo2cvmat(GLuint fbo, cv::Mat& out, GLint width, GLint height)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    
    int byteSizeRequired = width*height*4;
    int byteSizeCurrent  = out.cols*out.rows*out.channels();
    
    if (byteSizeCurrent != byteSizeRequired)
    {
        out = cv::Mat(height, width, CV_8UC4);
    }
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, out.data);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

#endif
