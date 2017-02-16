/**
 * @file
 */
#ifndef _WIDGET_HPP__
#define _WIDGET_HPP__ 

#include "Cv_core.hpp"
#include "SetCursor.hpp"
#include "logs.hpp"
#include <ctime>

/**
 * @date       09-Feb-2017
 * @brief      Element qui reagi a un curseur
 * Classe mere
 * Methodes de reaction en virtuelle brute
 * De bases elles ne font rien
 * S'affiche sur cv mat
 * 
 */
class Widget 
{
public:
    Widget();
    ~Widget();

    /**Cursor dessus
    Temps que le curseur reste dessus -> vdirtuelle
    Faire quelque chose, une action -> virtuelle
*/

	// virtual void update(Player);

	/**
	 * @date       10-Feb-2017
	 * @brief      Indique si le Widget est sous le curseur
	 * Pour faciliter le code, il faut lui faire retourner l'appel à changeFirstActivation
	 * @param[in]  cursor  Le Cursor
	 * @return     Vrai si le Widget est sous le Cursor, Faux sinon
	 */
	virtual bool isUnderCursor(UNUSED(const Cursor& cursor));


    /**
     * @date       10-Feb-2017
     * @brief      Set pour le temps d'activation
     * @param[in]  seconde  Temps d'activation du Widget en seconde
     */
    virtual void setActivationTime(double seconde);

    /**
     * @date       15-Feb-2017
     * @brief      Change le temps auquel le Widget a été activé
     * @param[in]  underCursor  Retour de underCursor
     * @return     Retour de underCursor
     */
    bool changeFirstActivation(bool underCursor);

    /**
     * @date       10-Feb-2017
     * @brief      Indique si le Widget est activé. Il est activé s'il est sous
     *             un curseur depuis un temps de activationTime
     * @return     Vrai si le Widget est activé, Faux sinon.
     */
    bool isActivated() const;

    /**
     * @date       10-Feb-2017
     * @brief      Action liée au Widget. C'est elle qui est appelée lorsque le Widget est activé
     */
    virtual void action();

    /**
     * @date       09-Feb-2017
     * @brief      Affiche le Widget sur la frame
     * @param      frame  La frame
     */
    virtual void draw(UNUSED(cv::Mat& frame));

    uint32_t  x() const ;
    uint32_t& x();
    uint32_t  y() const ;
    uint32_t& y();

private:
    double activationTime;    //!< Temps minimum pour activer le Widget en seconde
    time_t firstActiveTime; //!< Temps auquel le Widget a été activé
    uint32_t _x; //!< Coordonnées en x du Widget
    uint32_t _y; //!< Coordonnées en y du Widget
};


class WidgetManager final
{
    public:
        //! @brief Crée juste le gestionnaire.
        WidgetManager(void) noexcept;
        //! @brief Appelle la méthode close() de chaque widget.
        ~WidgetManager(void);
        //! @brief Appelle la méthode update pour toutes les widgets.
        void updateWidgets(void);
        /**
         * @brief Ajoute @b Widget au gestionnaire.
         * @param[in,out] Widget L'adresse du widget à ajouter.
         * Le gestionnaire ne désallouera rien !
         * @return *this
         */
        WidgetManager& addWidget(Widget* Widget);
        //! @brief Ferme tous les widgets.
        void closeWidgets(void);
        
    private:
        std::vector<Widget*> Widgets; //!< L'ensemble des widgets utilisées.
        
        WidgetManager(const WidgetManager& other)            = delete;
        WidgetManager(WidgetManager&& other)                 = delete;
        WidgetManager& operator=(const WidgetManager& other) = delete;
        WidgetManager& operator=(WidgetManager&& other)      = delete;
        
};


// Code wifi Oasis-TD8 : @Deay2dh&
#endif