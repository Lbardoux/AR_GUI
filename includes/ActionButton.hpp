/**
 * @file ActionButton.hpp
 * @brief Définit un bouton qui va choisir une action avec une main particulière.
 * @author Laurent BARDOUX p1108365
 */
#ifndef ACTIONBUTTON_HPP_INCLUDED
#define ACTIONBUTTON_HPP_INCLUDED

#include <string>
#include "Sprite.hpp"
#include "TouchButton.hpp"
#include "Cv_core.hpp"


/**
 * @class ActionButton
 * @brief Un bouton d'action va définir un état qui restera tant que celui-ci est validé.
 * Par défaut, il faudra les activer avec la main gauche.
 */
class ActionButton : public TouchButton
{
    public:
        ActionButton(void) = delete;
        ActionButton(Sprite* image, const std::string& action);
        
        virtual void action() override;
        virtual void draw(UNUSED(Sprite& frame)) override;
        
        std::string& getText(void) noexcept;
        const std::string& getText(void) const noexcept;
        
    protected:
        std::string text; //!< Le texte explicatif associé à cette action
    
};

#endif
