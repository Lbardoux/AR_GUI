#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cstdint>

#include "Camera.hpp"

static bool OPENNI_INITIALISED = false;


void OpenNIInitialiser()
{
	if(OPENNI_INITIALISED)
		return;

	if (openni::OpenNI::initialize() != openni::STATUS_OK)
    {
        std::stringstream ss;
        ss << "Failed to initialize OpenNI : " << openni::OpenNI::getExtendedError();
        throw std::runtime_error(ss.str());
    }

	mtl::log::info("OpenNI initisalised correctly");
	OPENNI_INITIALISED = true;
	atexit(openni::OpenNI::shutdown);
}


namespace
{
    void closeOpenNIWithException(const std::string& what)
    {
        openni::OpenNI::shutdown();
        throw std::runtime_error(what);
    }
}

void Camera::init(const char* uri)
{
	OpenNIInitialiser();

    this->initCamera(uri);
    this->initColorStream();
    this->initDepthStream();
    if (!this->depth.isValid() || !this->color.isValid())
    {
        closeOpenNIWithException("No valid streams");
    }
}

Camera::~Camera(void)
{
    this->color.destroy();
    this->depth.destroy();
    this->device.close();
}

void Camera::readFrame(void)
{
    this->depth.readFrame(&this->depthframe);
    cv::Mat temp;
    const openni::DepthPixel* depthImageBuffer = (const openni::DepthPixel*)this->depthframe.getData();
    temp.create(this->depthframe.getHeight(), this->depthframe.getWidth(), CV_16UC1);
    memcpy(temp.data, depthImageBuffer, this->depthframe.getHeight()*this->depthframe.getWidth()*sizeof(int16_t));
    // cv::flip(temp, this->depthMat, 1);

    this->color.readFrame(&this->colorframe);
    const openni::RGB888Pixel* rgbImageBuffer = (const openni::RGB888Pixel*)this->colorframe.getData();
    temp.create(this->colorframe.getHeight(), this->colorframe.getWidth(), CV_8UC3);
    memcpy(temp.data, rgbImageBuffer, this->colorframe.getHeight()*this->colorframe.getWidth()*sizeof(uint8_t)*3);
    // cv::flip(temp, this->colorMat, 1);
    cv::cvtColor(this->colorMat, this->colorMat, CV_BGR2RGB);
}


void Camera::initCamera(const char* uri)
{
    if (this->device.open(uri) != openni::STATUS_OK)
    {
        std::stringstream error;
        error << "Failed to open device : " << openni::OpenNI::getExtendedError();
        closeOpenNIWithException(error.str());
    }
}

void Camera::initDepthStream(void)
{
    if (this->depth.create(this->device, openni::SENSOR_DEPTH) == openni::STATUS_OK)
    {
        if (this->depth.start() != openni::STATUS_OK)
        {
        	mtl::log::error("Couldn't start depth stream:\n", openni::OpenNI::getExtendedError());
            // printf("Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
            this->depth.destroy();
        }
    }
    else
    {
    	mtl::log::error("Couldn't find depth stream:\n", openni::OpenNI::getExtendedError());
        // printf("Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
    }
}

void Camera::initColorStream(void)
{
    if (this->color.create(this->device, openni::SENSOR_COLOR) == openni::STATUS_OK)
    {
        if (this->color.start() != openni::STATUS_OK)
        {
        	mtl::log::error("Couldn't start color stream:\n", openni::OpenNI::getExtendedError());
            // printf("Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
            this->color.destroy();
        }
    }
    else
    {
    	mtl::log::error("Couldn't find color stream:\n", openni::OpenNI::getExtendedError());
        // printf("Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
    }
}

const cv::Mat& Camera::depthFrame(void) const
{
	return this->depthMat;
}

cv::Mat& Camera::depthFrame(void)
{
	return this->depthMat;
}

const cv::Mat& Camera::colorFrame(void) const
{
	return this->colorMat;
}

cv::Mat& Camera::colorFrame(void)
{
	return this->colorMat;
}
