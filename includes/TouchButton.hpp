/**
 * @file TouchButton.hpp
 * @brief Un widget simple, si un cursor le touche, il "réagit" directement.
 * @author Laurent BARDOUX p1108365
 */
#ifndef TOUCHBUTTON_HPP_INCLUDED
#define TOUCHBUTTON_HPP_INCLUDED

#include "Cv_core.hpp"
#include "WidgetManager.hpp"
#include "Sprite.hpp"
#include "logs.hpp"
#include <vector>

/**
 * @class TouchButton
 * @brief Ce widget a comme particularité de réagir instantanément quand on le "touche"
 * C'est également un widget en forme de cercle, rendant les collisions réduites à de simples calculs.
 */
class TouchButton : public Widget
{
    public:
        TouchButton(void);
        TouchButton(const TouchButton& other);
        TouchButton(TouchButton&& other);
        /**
         * @brief Instancie un TouchButton avec @b image comme sprite
         * @param[in] image L'aresse d'une cv::Mat préalablement chargée.
         */
        TouchButton(Sprite* image);
        ~TouchButton();

        /**
         * @date       15-Feb-2017
         * @brief      Initialise le Sprite du Widget
         * @param      image    Le Sprite
         * @param[in]  x        Position en x du Widget
         * @param[in]  y        Position en y du Widget
         * @param[in]  seconde  Temps d'activation du Widget
         */
        void init(Sprite* image, int x, int y, double seconde);
        
        virtual bool isUnderCursor(UNUSED(const Cursor& cursor)) override;
        //virtual void setActivationTime(time_t time) override;
        virtual void action() override;
        virtual void draw(Sprite& frame) override;
        virtual void update(void);
        virtual void updateTime(const CursorSet& cursors);
        /**
         * @date       17-Feb-2017
         * @brief      Ajoute un membre aux membres pouvant intéragir avec le Widget
         * @param[in]  membre Membre à ajouter
         * @return     *this
         */
        TouchButton& addMembre(int membre);
        /**
         * @date       18-Feb-2017
         * @brief      Change le Sprite
         * @param      sprite  Nouveau Sprite du Widget
         */
        void setSprite(Sprite* sprite);
    
    protected:
        Sprite* sprite; //!< La représentation de ce widget.
        std::vector<int> membres; //!< Contient les valeurs des membres pouvant intéragir avec le Widget
        
        TouchButton& operator=(const TouchButton& other) = delete;
        TouchButton& operator=(TouchButton&& other) = delete;
};

#endif

