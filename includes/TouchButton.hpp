/**
 * @file TouchButton.hpp
 * @brief Un widget simple, si un cursor le touche, il "réagit" directement.
 * @author Laurent BARDOUX p1108365
 */
#ifndef TOUCHBUTTON_HPP_INCLUDED
#define TOUCHBUTTON_HPP_INCLUDED

#include "Cv_core.hpp"
#include "Widget.hpp"


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
        TouchButton(cv::Mat* image);
        
        virtual bool isUnderCursor(UNUSED(const Cursor& cursor)) const override;
        //virtual void setActivationTime(time_t time) override;
        virtual bool isActivated() const override;
        virtual void action() override;
        virtual void draw(UNUSED(cv::Mat& frame)) override;
    
    protected:
        cv::Mat* sprite; //!< La représentation de ce widget.
        
        TouchButton& operator=(const TouchButton& other) = delete;
        TouchButton& operator=(TouchButton&& other) = delete;
};

#endif

