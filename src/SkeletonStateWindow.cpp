/**
 * @file SkeletonStateWindow.cpp
 */
#include <iostream>
#include "Cv_core.hpp"
#include "SkeletonStateWindow.hpp"
#include "logs.hpp"

SkeletonStateWindow::SkeletonStateWindow(void) : OpenCVWindow(), state(false)
{
    mtl::log::info("Creation de la fenetre d'etat");
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
	mtl::log::info("Chargement de " IMAGES_DIR "valid.png et " IMAGES_DIR "error.png");
}

void SkeletonStateWindow::close(void)
{
    this->valid.release();
    this->error.release();
    this->OpenCVWindow::close();
	mtl::log::info("Destruction de la fenetre d'etat");
}

void SkeletonStateWindow::update(void)
{
    cv::imshow(this->name, (this->state) ? this->valid : this->error);
}
