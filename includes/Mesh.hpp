/**
 * @file Mesh.hpp
 * @brief Interface permettant d'afficher un mesh
 * @author Charles Sultan p1207507
 * @version 1.0
 */
#ifndef _MESH_H_
#define _MESH_H_

#define USING_OPENGL

#include <vector>
#include <iostream>
#include <array>
#include <assert.h>
#include <cstdio>
#include <string.h>
#include "vec.hpp"
#include "GlCore.hpp"
#include "Matrix.hpp"
#include "ShaderProgram.hpp"

/**
 * @class Mesh
 * @brief Cette structure permet de d'afficher un mesh.
 */
class Mesh
{
public:
	/**
     * @brief Construit le mesh
     * @param[in] path le chemin vers le fichier .obj 
     */
	Mesh(const char * path);

	/**
     * @brief Déstructeur par défaut.
     */
	~Mesh() = default;

	/**
     * @brief Affiche le mesh.
     * @param[in] programm le shader
     * @param[in] model la matrice modele
   	 * @param[in] view la matrice vue
     * @param[in] projection la matrice projection
     */
	void draw(ShaderProgram & programm, Transform & model, Transform & view, Transform & projection) const;

private:
	void initVAO();

	GLuint 				m_vertex_buffer;	//!< Le buffer de points.
    GLuint 				m_normal_buffer;	//!< Le buffer des normales.
    GLuint 				m_texture_buffer;	//!< Le buffer des textures.
	std::vector<vec3> 	m_vertices;			//!< Les coordonnées des points.
	std::vector<vec3> 	m_normals;			//!< Les normales.
	std::vector<vec2> 	m_uvs;				//!< Les coordonnées de textures.
	GLuint 				m_vao;				//!< Le VAO.
};

#endif
