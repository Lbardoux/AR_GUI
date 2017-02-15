/**
 * @file Sprite.cpp
 */
#include <stdexcept>

#include "Sprite.hpp"

void Sprites::init(void)
{
    
}

void Sprites::empty(void)
{
    
	
}

void loadSprite(const std::string& fname, cv::Mat& dst)
{
	dst = cv::imread(fname, cv::IMREAD_UNCHANGED);
}

void blit(cv::Mat& dst, const cv::Mat& sprite, int x, int y)
{
	
	
	
	
	
	
	//sprite.copyTo(dst.rowRange(1, 6).colRange(3, 10));
}
