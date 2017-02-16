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

    // Widget
    this->touchButton.init(&Sprites::spr_touchButton, 5, 5, 4.0f);
}

void CameraWindow::close(void)
{
    this->OpenCVWindow::close();
}

void CameraWindow::update(void)
{
	// if (this->touchButton.isUnderCursor(Cursor(nite::Point3f(10, 10, 10))) && this->touchButton.isActivated())
	// 	this->touchButton.action();

	// this->touchButton.draw(this->camera.colorFrame());
	cv::imshow(this->name, this->camera.colorFrame());
}

void CameraWindow::readFrame(void)
{
	this->camera.readFrame();
}

Camera& CameraWindow::getCamera()
{
    return this->camera;
}
