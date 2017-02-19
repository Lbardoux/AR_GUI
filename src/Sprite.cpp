/**
 * @file Sprite.cpp
 */
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "Sprite.hpp"
#include "logs.hpp"

Sprite Sprites::test;

Sprite Sprites::spr_touchButton;
Sprite Sprites::spr_peinture_on;
Sprite Sprites::spr_peinture_off;
Sprite Sprites::spr_peinture_reset;
Sprite Sprites::spr_peinture_save;

cv::Size Sprites::tailleIcone = {56, 56};

void Sprites::init(void)
{
    loadSprite("assets/images/spr_shield.png", Sprites::test);
    loadSprite("assets/images/valid.png", Sprites::spr_touchButton);
    loadSprite("assets/images/peinture_on.png", Sprites::spr_peinture_on);
    cv::resize(Sprites::spr_peinture_on, Sprites::spr_peinture_on, Sprites::tailleIcone);
    loadSprite("assets/images/peinture_off.png", Sprites::spr_peinture_off);
    cv::resize(Sprites::spr_peinture_off, Sprites::spr_peinture_off, Sprites::tailleIcone);
    loadSprite("assets/images/button_reset.png", Sprites::spr_peinture_reset);
    cv::resize(Sprites::spr_peinture_reset, Sprites::spr_peinture_reset, Sprites::tailleIcone);
    loadSprite("assets/images/peinture_sauvegarde.png", Sprites::spr_peinture_save);
    cv::resize(Sprites::spr_peinture_save, Sprites::spr_peinture_save, Sprites::tailleIcone);
}

void Sprites::empty(void)
{
	mtl::log::info("Aboutissement des Sprites...", mtl::log::hold_on());
    spr_touchButton.release();

	mtl::log::info("Fait!");
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
			double alpha = static_cast<double>(sprite.at<mat_data_t>(row, col)[3])/255.0;
			if (alpha > 0.0)
			{
				mat_data_t fromSprite = (1.0 - alpha)*matAt(sprite, col, row);
				mat_data_t fromDst    = alpha*matAt(dst, col + x, row + y);
				matAt(dst, col + x, row + y) = fromSprite + fromDst;
			}
		}
    }
}
