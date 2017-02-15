/**
 * @file Sprite.cpp
 */
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "Sprite.hpp"
#include "logs.hpp"

Sprite Sprites::test;

void Sprites::init(void)
{
    loadSprite("assets/images/spr_shield.png", Sprites::test);
	
}

void Sprites::empty(void)
{
    
	
}

void loadSprite(const std::string& fname, Sprite& dst)
{
	if (fname.substr(fname.rfind(".")) != ".png")
	{
		throw std::invalid_argument("Les sprites doivent etre des .png");
	}
	dst = cv::imread(fname, cv::IMREAD_UNCHANGED);
	mtl::log::info("\t|-- Chargement de", fname);
}

void blit(Sprite& dst, const Sprite& sprite, int x, int y)
{
	int beginX = std::max(0, x)-x;
	int beginY = std::max(0, y)-y;
	int endX   = std::min(x + sprite.cols, dst.cols)-x;
	int endY   = std::min(y + sprite.rows, dst.rows)-y;
	for(int col=beginX;col<endX;++col)
	{
		for(int row=beginY;row<endY;++row)
		{
			if (sprite.at<mat_data_t>(row, col)[3] != 0)
				matAt(dst, col + x, row + y) = matAt(sprite, col, row);
		}
	}
}
