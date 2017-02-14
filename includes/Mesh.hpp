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

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

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
     * @param[in] program le shader
     */
	Mesh(const char * path, ShaderProgram & program);

	/**
     * @brief Déstructeur par défaut.
     */
	~Mesh() = default;

	/**
     * @brief Affiche le mesh.r
     * @param[in] model la matrice modele
   	 * @param[in] view la matrice vue
     * @param[in] projection la matrice projection
     */
	void draw(Transform & model, Transform & view, Transform & projection) const;

private:
	void initVAO();

	GLuint              m_program;  //!< Le shader   
    GLuint              m_vao;      //!< Le VAO.
    GLuint              m_vbo;      //!< Le VBO.
    std::vector<vec3>   m_vertices; //!< Les coordonnées des points.
    std::vector<vec3>   m_normals;  //!< Les normales.
    std::vector<vec2>   m_uvs;      //!< Les coordonnées de textures.
};

#endif
