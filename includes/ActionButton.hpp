/**
 * @file ActionButton.hpp
 * @brief Définit un bouton qui va choisir une action avec une main particulière.
 * @author Laurent BARDOUX p1108365
 */
#ifndef ACTIONBUTTON_HPP_INCLUDED
#define ACTIONBUTTON_HPP_INCLUDED

#include <string>
#include <functional>
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
        //! @brief Action par défaut.
        ActionButton(void);
        /**
         * @brief Charge un widget avec @b image comme représentation et @b action comme texte explicatif.
         * @param[in] image  L'adresse d'un @b sprite préalablement alloué/chargé (cela ne le desallouera pas).
         * @param[in] action Une courte description (un mot) pour l'action.
         */
        ActionButton(Sprite* image, const std::string& action);
        //! @brief Destruction (ne désalloue pas le Sprite).
        ~ActionButton(void);
        
        void init(const std::string& action, std::function<void(void)> function, Sprite* image, int x, int y, double seconde);
        virtual void action() override;
        virtual void draw(Sprite& frame) override;
        
        //! @brief Donnent accès au texte de l'action.
        std::string& getText(void) noexcept;
        const std::string& getText(void) const noexcept;
        
    protected:
        std::string text;                   //!< Le texte explicatif associé à cette action
        std::function<void(void)> function; //!< Ce que doit faire le widget lorsqu'il se déclenche.
    
};

#endif
