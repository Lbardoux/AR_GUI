/**
 * @file OpenGL.hpp
 * @brief Interface permettant de dessiner dans un frame_buffer
 * @author Charles Sultan p1207507
 * @version 1.0
 */
#ifndef _OPENGL_H_
#define _OPENGL_H_

#include "Player.hpp"
#include "Clothe.hpp"

/**
 * @class Mesh
 * @brief Cette classe permet de dessiner dans un frame_buffer la soubrette sur le joueur.
 */
class MaidDrawer
{
public:
	/**
      * @brief      Construit MaidDrawer
      * @param[in]  player le joueur
      * @param[in]  maid le vêtement à afficher
      * @param[in]  program le shader
      * @pre        Le contexte OpenGl doit être initialisé
      */
	MaidDrawer(Player & player, Clothe & maid, ShaderProgram & program);

	/**
     * @brief Déstructeur par défaut.
     */
    ~MaidDrawer() = default;

    /**
     * @brief Dessine dans le frame buffer
     * @return Renvoie l'identifiant du frame buffer
     */
    GLuint draw() const;

private:
    ShaderProgram &    m_program;       //!< Le shader
	GLuint             m_color_sampler;	//!< Le color sampler
	GLuint             m_color_buffer;	//!< Le color buffer
	GLuint             m_depth_buffer;	//!< Le depth buffer
	GLuint             m_frame_buffer;	//!< Le frame buffer
    Player &           m_player;        //!< Le joueur
    Clothe &           m_maid;          //!< La soubrette
};


#endif