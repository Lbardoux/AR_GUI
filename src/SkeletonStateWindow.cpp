/**
 * @file SkeletonStateWindow.cpp
 */
#include <iostream>
#include "Cv_core.hpp"
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
void SkeletonStateWindow::open(UNUSED(uint32_t width), UNUSED(uint32_t height))
{
    this->valid = cv::imread(IMAGES_DIR "valid.png", cv::IMREAD_COLOR);
    this->error = cv::imread(IMAGES_DIR "error.png", cv::IMREAD_COLOR);
}

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
