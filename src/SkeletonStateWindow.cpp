/**
 * @file SkeletonStateWindow.cpp
 */
#include <iostream>

#include "SkeletonStateWindow.hpp"

SkeletonStateWindow::SkeletonStateWindow(void) : OpenCVWindow(), state(false)
{
    
}

SkeletonStateWindow::~SkeletonStateWindow(void)
{
    
}

SkeletonStateWindow& SkeletonStateWindow::setState(bool value) noexcept
{
    this->state = value;
    return *this;
}

#define IMAGES_DIR "assets/images/"
void SkeletonStateWindow::open(uint32_t width, uint32_t height)
{
    (void)width, (void)height;
    this->valid = cv::imread(IMAGES_DIR "valid.png", cv::IMREAD_COLOR);
    this->error = cv::imread(IMAGES_DIR "error.png", cv::IMREAD_COLOR);
}
#undef IMAGES_DIR

void SkeletonStateWindow::close(void)
{
    this->valid.release();
    this->error.release();
    this->OpenCVWindow::close();
}

void SkeletonStateWindow::update(void)
{
    cv::imshow(this->name, (this->state) ? this->valid : this->error);
}
