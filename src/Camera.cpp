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

void __exit_Openni_message_()
{
	mtl::log::info("Shutting down OpenNI");
}

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
	atexit(__exit_Openni_message_);
}

void printStatusOpenni(openni::Status status)
{
	switch(status)
	{
		case openni::STATUS_OK :
			mtl::log::info("Status returned : STATUS_OK");
			break;
		case openni::STATUS_ERROR :
			mtl::log::info("Status returned : STATUS_ERROR");
			break;
		case openni::STATUS_NOT_IMPLEMENTED :
			mtl::log::info("Status returned : STATUS_NOT_IMPLEMENTED");
			break;
		case openni::STATUS_NOT_SUPPORTED :
			mtl::log::info("Status returned : STATUS_NOT_SUPPORTED");
			break;
		case openni::STATUS_BAD_PARAMETER :
			mtl::log::info("Status returned : STATUS_BAD_PARAMETER");
			break;
		case openni::STATUS_OUT_OF_FLOW :
			mtl::log::info("Status returned : STATUS_OUT_OF_FLOW");
			break;
		case openni::STATUS_NO_DEVICE :
			mtl::log::info("Status returned : STATUS_NO_DEVICE");
			break;
		case openni::STATUS_TIME_OUT :
			mtl::log::info("Status returned : STATUS_TIME_OUT");
			break;
		default:
			mtl::log::info("Unknown status ", status);
			break;
	}
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
    // this->initDepthStream();
    if (/* !this->depth.isValid() || */ !this->color.isValid())
    {
        closeOpenNIWithException("No valid streams");
    }
}

// #define __DEPTH_FORMAT__ openni::PIXEL_FORMAT_DEPTH_1_MM
bool Camera::findVideoModes(int width, int height, openni::SensorType sensorType, openni::VideoMode& videoMode)
{
	const openni::SensorInfo* sinfo = this->device.getSensorInfo(sensorType);

    if (sinfo == NULL)
    {
        mtl::log::error("Couldn't get device info\n", openni::OpenNI::getExtendedError());
        return false;
    }

    const openni::Array<openni::VideoMode>& modesDepth = sinfo->getSupportedVideoModes();

    std::vector<int> item;
    for (int i = 0; i < modesDepth.getSize(); i++) {
        // printf("%i: %ix%i, %i fps, %i format\n", i, modesDepth[i].getResolutionX(), modesDepth[i].getResolutionY(),
        //     modesDepth[i].getFps(), modesDepth[i].getPixelFormat()); //PIXEL_FORMAT_DEPTH_1_MM = 100, PIXEL_FORMAT_DEPTH_100_UM
        if (modesDepth[i].getResolutionX() == width && modesDepth[i].getResolutionY() == height)/* &&
            modesDepth[i].getPixelFormat() == __DEPTH_FORMAT__)*/
            item.push_back(i);
    }

    if(item.empty())
    {
        mtl::log::error("Couldn't find resolution [", width, ',', height, "] in modes available for the device");
        return false;
    }

    videoMode = modesDepth[item[0]];

    return true;
}
// #undef __DEPTH_FORMAT__

void Camera::start(int width, int height)
{
	openni::VideoMode videoMode;
	openni::Status status;

	// if(findVideoModes(width / 2, height / 2, openni::SENSOR_DEPTH, videoMode))
	// {
	// 	status = this->depth.setVideoMode(videoMode);
	// 	if(status != openni::STATUS_OK)
	// 	{
	// 		mtl::log::error("Unable to set VideoMode for depth stream");
	// 		printStatusOpenni(status);
	// 	}
	// 	else
	// 		mtl::log::info("Resolution sets to [", width, ',', height, "] for depth stream");
 // 	}
	if(findVideoModes(width, height, openni::SENSOR_COLOR, videoMode))
	{
		status = this->color.setVideoMode(videoMode);
		if(status != openni::STATUS_OK)
		{
			mtl::log::error("Unable to set VideoMode for color stream");
			printStatusOpenni(status);
		}
		else
			mtl::log::info("Resolution sets to [", width, ',', height, "] for color stream");
	}

	// if (this->depth.start() != openni::STATUS_OK)
 //    {
 //    	mtl::log::error("Couldn't start depth stream:\n", openni::OpenNI::getExtendedError());
 //        // printf("Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
 //        this->depth.destroy();
 //    }
    if (this->color.start() != openni::STATUS_OK)
    {
    	mtl::log::error("Couldn't start color stream:\n", openni::OpenNI::getExtendedError());
        // printf("Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
        this->color.destroy();
    }
}

Camera::~Camera(void)
{
    this->color.stop();
    this->color.destroy();
    // this->depth.stop();
    // this->depth.destroy();
    this->device.close();
}

void Camera::readFrame(void)
{
    // this->depth.readFrame(&this->depthframe);
    // // cv::Mat temp;
    // const openni::DepthPixel* depthImageBuffer = (const openni::DepthPixel*)this->depthframe.getData();
    // depthMat.create(this->depthframe.getHeight(), this->depthframe.getWidth(), CV_16UC1);
    // memcpy(depthMat.data, depthImageBuffer, this->depthframe.getHeight()*this->depthframe.getWidth()*sizeof(int16_t));
    // // cv::flip(temp, this->depthMat, 1);

    this->color.readFrame(&this->colorframe);
    const openni::RGB888Pixel* rgbImageBuffer = (const openni::RGB888Pixel*)this->colorframe.getData();
    colorMat.create(this->colorframe.getHeight(), this->colorframe.getWidth(), CV_8UC3);
    memcpy(colorMat.data, rgbImageBuffer, this->colorframe.getHeight()*this->colorframe.getWidth()*sizeof(uint8_t)*3);
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

// void Camera::initDepthStream(void)
// {
//     if (this->depth.create(this->device, openni::SENSOR_DEPTH) != openni::STATUS_OK)
//     {
//     	mtl::log::error("Couldn't find depth stream:\n", openni::OpenNI::getExtendedError());
//         // printf("Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
//     }
// }

void Camera::initColorStream(void)
{
    if (this->color.create(this->device, openni::SENSOR_COLOR) != openni::STATUS_OK)
    {
    	mtl::log::error("Couldn't find color stream:\n", openni::OpenNI::getExtendedError());
        // printf("Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
    }
}

// const cv::Mat& Camera::depthFrame(void) const
// {
// 	return this->depthMat;
// }

// cv::Mat& Camera::depthFrame(void)
// {
// 	return this->depthMat;
// }

const cv::Mat& Camera::colorFrame(void) const
{
	return this->colorMat;
}

cv::Mat& Camera::colorFrame(void)
{
	return this->colorMat;
}

openni::Device& Camera::getDevice()
{
	return this->device;
}