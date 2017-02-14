#include "CameraWindow.hpp"

CameraWindow::CameraWindow()
{}

CameraWindow::~CameraWindow()
{}

void CameraWindow::init(const std::string& name , int width, int height)
{
	this->camera.init();
	this->camera.start(width, height);
	this->setName(name);
	this->open(width, height);
}

void CameraWindow::close(void) 
{
	this->OpenCVWindow::close();
}

void CameraWindow::update(void)
{
	this->camera.readFrame();
	cv::imshow(this->name, this->camera.colorFrame());
}
