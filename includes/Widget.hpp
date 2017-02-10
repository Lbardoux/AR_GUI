/**
 * @file
 */
#ifndef _WIDGET_HPP__
#define _WIDGET_HPP__ 

#include "Cv_core.hpp"
#include "Cursor.hpp"
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

	/**
	 * @date       10-Feb-2017
	 * @brief      Indique si le Widget est sous le curseur
	 * @param[in]  cursor  Le Cursor
	 * @return     Vrai si le Widget est sous le Cursor, Faux sinon
	 */
	virtual bool isUnderCursor(UNUSED(const Cursor& cursor)) const;


	/**
	 * @date       10-Feb-2017
	 * @brief      Set pour le temps d'activation
	 * @param[in]  time  Temps d'activation du Widget
	 */
	virtual void setActivationTime(time_t time);

	/**
	 * @date       10-Feb-2017
	 * @brief      Indique si le Widget est activé. Il est activé s'il est sous
	 *             un curseur depuis un temps de activationTime
	 * @return     Vrai si le Widget est activé, Faux sinon.
	 */
	virtual bool isActivated() const;

	/**
	 * @date       10-Feb-2017
	 * @brief      Action liée au Widget
	 */
	virtual void action();

	/**
	 * @date       09-Feb-2017
	 * @brief      Affiche le Widget sur la frame
	 * @param      frame  La frame
	 */
	virtual void draw(UNUSED(cv::Mat& frame));

private:
	time_t activationTime;
};

#endif