#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cstdint>

#include "Camera.hpp"
#include "Cursor.hpp"

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
}

void QuitOpenNI(void)
{
    mtl::log::info("On ferme OpenNI");
    openni::OpenNI::shutdown();
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
    if (!this->color.isValid())
    {
        closeOpenNIWithException("No valid streams");
    }
}

bool Camera::findVideoModes(int width, int height, openni::SensorType sensorType, openni::VideoMode& videoMode, bool printMods)
{
    const openni::SensorInfo* sinfo = this->device.getSensorInfo(sensorType);

    if (sinfo == NULL)
    {
        mtl::log::error("Couldn't get device info\n", openni::OpenNI::getExtendedError());
        return false;
    }

    const openni::Array<openni::VideoMode>& modesDepth = sinfo->getSupportedVideoModes();

    bool old_value = mtl::log::Options::ENABLE_SPACING;
    mtl::log::Options::ENABLE_SPACING = false;

    std::vector<int> item;
    for (int i = 0; i < modesDepth.getSize(); i++) {
        if(printMods)
            mtl::log::info(i, ": ", modesDepth[i].getResolutionX(), 'x', modesDepth[i].getResolutionY(), ", ", modesDepth[i].getFps(), " fps, ", modesDepth[i].getPixelFormat(), " format", mtl::log::hold_on());
        if (modesDepth[i].getResolutionX() == width && modesDepth[i].getResolutionY() == height)
        {
            item.push_back(i);
            if(printMods)
                mtl::log::info(" : Ajouté");
        }
        else if(printMods)
                mtl::log::info();

    }

    if(item.empty())
    {
        mtl::log::error("Couldn't find resolution [", width, ',', height, "] in modes available for the device");
        return false;
    }

    videoMode = modesDepth[item[0]];

    mtl::log::Options::ENABLE_SPACING = old_value;

    return true;
}

void Camera::start(int width, int height)
{
    openni::VideoMode videoMode;
    openni::Status status;

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

    if (this->color.start() != openni::STATUS_OK)
    {
        mtl::log::error("Couldn't start color stream:\n", openni::OpenNI::getExtendedError());
        this->color.destroy();
    }
    
    Interval iH = {0u, static_cast<uint32_t>(width)};
    Interval iV = {0u, static_cast<uint32_t>(height)};
    Cursor::horizontal = iH;
    Cursor::vertical   = iV;
}

Camera::~Camera(void)
{
    this->color.stop();
    this->color.destroy();
    this->device.close();
}

void Camera::readFrame(void)
{
    this->color.readFrame(&this->colorframe);
    const openni::RGB888Pixel* rgbImageBuffer = (const openni::RGB888Pixel*)this->colorframe.getData();
    colorMat.create(this->colorframe.getHeight(), this->colorframe.getWidth(), CV_8UC3);
    memcpy(colorMat.data, rgbImageBuffer, this->colorframe.getHeight()*this->colorframe.getWidth()*sizeof(uint8_t)*3);
    cv::cvtColor(this->colorMat, this->colorMat, CV_BGR2RGBA);
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

void Camera::initColorStream(void)
{
    if (this->color.create(this->device, openni::SENSOR_COLOR) != openni::STATUS_OK)
    {
        mtl::log::error("Couldn't find color stream:\n", openni::OpenNI::getExtendedError());
    }
}

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
