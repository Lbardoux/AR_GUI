/**
 * @file OpenCVWindow.cpp
 */


#include "OpenCVWindow.hpp"


OpenCVWindow::OpenCVWindow(void) : Window()
{
    
}

OpenCVWindow::~OpenCVWindow(void)
{
    
}

void OpenCVWindow::open(uint32_t width, uint32_t height)
{
    cv::resizeWindow(this->name, width, height);
}

bool OpenCVWindow::isGood(void) const
{
    return true;
}

void OpenCVWindow::close(void)
{
    cv::destroyWindow(this->name);
}

void OpenCVWindow::update(void)
{
    
}

void OpenCVWindow::setName(const std::string& name)
{
    this->name = name;
    cv::namedWindow(name);
}
