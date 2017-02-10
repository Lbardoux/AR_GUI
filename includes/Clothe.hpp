/**
 * @file Clothe.hpp
 * @brief Interface permettant d'afficher un vêtement à un joueur
 * @author Charles Sultan p1207507
 * @version 1.0
 */
#ifndef _CLOTHE_H_
#define _CLOTHE_H_

#include "Player.hpp"
#include "Mesh.hpp"
#include "Mat.hpp"

/**
 * @class Clothe
 * @brief Cette structure permet de d'afficher un vêtement à un joueur.
 */
class Clothe
{
public:
	/**
     * @brief 		Construit un nouveau vêtement 
     * @param[in] 	player le joueur 
     * @param[in] 	member1 la première articulation à laquelle est attaché le vêtement
	 * @param[in] 	member2 la deuxième articulation à laquelle est attaché le vêtement
	 * @param[in] 	mesh le mesh du vêtement
     */
	Clothe(Player & player, PlayerMember member1, PlayerMember member2, const Mesh & mesh);

	/**
     * @brief Déstructeur par défaut.
     */
	~Clothe() = default;

	/**
     * @brief Affiche le vêtement.
     */
	void draw() const;

private:
	Player & 		m_player; 				//!< Le joueur.
	PlayerMember 	m_member1, m_member2; 	//!< Les deux membres auquel est attaché le vêtement.
	const Mesh &	m_mesh;					//!< Le mesh.
};

#endif