/**
 * @file Player.hpp
 * @brief Interface permettant de trouver facilement la position d'une articulation de la personne vue par la caméra.
 * @author Charles Sultan p1207507
 * @version 1.0
 */
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <NiTE.h>
#include "vec.hpp"
#include "Camera.hpp"

/**
 * @enum PlayerMember
 * @brief Enumère toutes les articulations d'un joueur
 */
enum PlayerMember { HEAD = 0, NECK, TORSO, 
                    LEFT_SHOULDER, LEFT_ELBOW, LEFT_HAND, 
                    RIGHT_SHOULDER, RIGHT_ELBOW, RIGHT_HAND, 
                    LEFT_HIP, LEFT_KNEE,
                    RIGHT_HIP, RIGHT_KNEE,
                    NB_PLAYER_MEMBER };  // L'enum NB_PLAYER_MEMBER doit etre en dernier, comme ça on peut les compter 

/**
 * @class Player
 * @brief Cette structure permet de trouver la position de n'importe quelle articulation du joueur en mettant à jour la frame.
 */
class Player
{
public:

	Player();
	/**
     * @brief 		Construit un nouveau player 
     * @param[in] 	user_tracker le tracker préallablement initialisé avec la bibliothèque NiTE.
	 * @pre 		Veuillez faire attention  que user_tracker->create(&device) soit bien égal à nite::STATUS_OK.
     */
    Player(Camera & camera);
    /**
     * @brief Destructeur par défaut.
     */
    ~Player() = default;

	/**
	 * @date       16-Feb-2017
	 * @brief      Initialise un player
	 * @param      camera  Camera qui servira pour NiTE
	 */
	void init(Camera & camera);

	/**
     * @brief 	Met à jour les articulations du joueur en lisant une nouvelle frame.
	 * @return	Vrai si un seul joueur a été detecté.
	 *			Faux si aucun joueur a été detecté ou plusieurs ou si il y a eu un problème.  
     */
    bool update();

    /**
     * @brief     Renvoi vrai si le joueur est visible.
     * @return    Vrai si un seul joueur a été detecté et qu'il est visible, faux sinon.
     */
    bool isVisible() const;

    /**
     * @brief         Renvoi la position de l'articulation
     * @param[in]     member l'articulation dont on souhaite connaitre la position.
     * @return        La position correspondant à l'articulation. Le position (0 0 0) si l'articulation n'était pas visible. 
     */
    nite::Point3f getPositionOf(PlayerMember member) const;

    /**
     * @brief         Renvoi le point correspondant à l'articulation
     * @param[in]     member l'articulation dont on souhaite connaitre la position.
     * @return        Le point correspondant à l'articulation. Le point (0 0 0) si l'articulation n'était pas visible. 
     */
	Point getPointOf(PlayerMember member) const;
	
	nite::Point3f getCameraPositionOf(PlayerMember member) const;
private:
    /**
     * @brief         Renvoi la position de l'articulation
     * @param[in]     member l'articulation dont on souhaite connaitre la position.
     * @return        Vrai si un seul joueur a été detecté et qu'il est visible, faux sinon.
     */
    nite::Point3f getPositionOf(nite::JointType member) const;

    nite::UserTracker      m_user_tracker;        //!< Le tracker.
    const nite::UserData *     m_user;                //!< Le joueur detecté. 
    bool                     one_player_visible;    //!< Permet de savoir si lors du dernier update, la caméra a bien decté un et un seul joueur.
};

#endif
