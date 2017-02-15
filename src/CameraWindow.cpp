#include "CameraWindow.hpp"
#include "Sprite.hpp"

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
	//mtl::log::info("nombre de canaux :", this->camera.colorFrame().channels());
	blit(this->camera.colorFrame(), Sprites::test, -24, -24);
	cv::imshow(this->name, this->camera.colorFrame());
}

Camera& CameraWindow::getCamera()
{
	return this->camera;
}
