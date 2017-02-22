/**
 * @file Sprite.cpp
 */
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstdint>

#include "Sprite.hpp"
#include "logs.hpp"

Sprite Sprites::test;
Sprite Sprites::spr_peinture_on;
Sprite Sprites::spr_peinture_off;
Sprite Sprites::spr_peinture_reset;
Sprite Sprites::spr_peinture_save;
Sprite Sprites::spr_clothe_on;
Sprite Sprites::spr_clothe_off;

cv::Size Sprites::tailleIcone = {56, 56};


void Sprites::init(void)
{
    loadSprite("assets/images/exit.png", Sprites::test, true);
    loadSprite("assets/images/peinture_on.png", Sprites::spr_peinture_on, true);
    loadSprite("assets/images/peinture_off.png", Sprites::spr_peinture_off, true);
    loadSprite("assets/images/button_reset.png", Sprites::spr_peinture_reset, true);
    loadSprite("assets/images/peinture_sauvegarde.png", Sprites::spr_peinture_save, true);
    loadSprite("assets/images/clothe_button_on.png", Sprites::spr_clothe_on, true);
    loadSprite("assets/images/clothe_button_off.png", Sprites::spr_clothe_off, true);
}

void Sprites::empty(void)
{
	mtl::log::info("Aboutissement des Sprites...", mtl::log::hold_on());
    Sprites::test.release();
    Sprites::spr_peinture_on.release();
    Sprites::spr_peinture_off.release();
    Sprites::spr_peinture_reset.release();
    Sprites::spr_peinture_save.release();
    Sprites::spr_clothe_on.release();
    Sprites::spr_clothe_off.release();
	mtl::log::info("Fait!");
}

void loadSprite(const std::string& fname, Sprite& dst, bool resize)
{
    if (fname.substr(fname.rfind(".")) != ".png")
    {
        throw std::invalid_argument("Les sprites doivent etre des .png");
    }
    dst = cv::imread(fname, cv::IMREAD_UNCHANGED);
    if (resize)
    {
        cv::resize(dst, dst, Sprites::tailleIcone);
    }
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
            int iAlpha = sprite.at<mat_data_t>(row, col)[3];
            switch(iAlpha)
            {
                case 0:
                    break;
                case 255:
                    matAt(dst, col + x, row + y) = matAt(sprite, col, row);
                    break;
                default:
                    float alpha = static_cast<float>(iAlpha);
                    mat_data_t fromSprite = (alpha/255.0f)*matAt(sprite, col, row);
                    mat_data_t fromDst    = ((255.0f-alpha)/255.0f)*matAt(dst, col + x, row + y);
                    matAt(dst, col + x, row + y) = fromSprite + fromDst;
                    break;
            }
        }
    }
}

void fillBordure(Sprite& sprite, const mat_data_t& color, int epaisseurBordure, int taillePointille)
{
    for (int i = 0; i < epaisseurBordure; ++i)
    {
        for (int x = 0; x < sprite.cols; ++x)
        {
            matAt(sprite, x, i) = color;
            matAt(sprite, x, sprite.rows - i - 1) = color;
            for(int xx = 0; x < (sprite.cols - 1) && xx < (taillePointille - 1); ++xx)
            {
                matAt(sprite, ++x, i) = color;
                matAt(sprite, x, sprite.rows - i - 1) = color;
            }
            x += taillePointille;
        }
        for (int y = 0; y < sprite.rows; ++y)
        {
            matAt(sprite, i, y) = color;
            matAt(sprite, sprite.cols - i - 1, y) = color;
            for(int yy = 0; y < (sprite.rows - 1) && yy < (taillePointille - 1); ++yy)
            {
                matAt(sprite, i, ++y) = color;
                matAt(sprite, sprite.cols - i - 1, y) = color;
            }
            y += taillePointille;
        }
    }
}