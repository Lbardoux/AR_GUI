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
#include "Cv_core.hpp"
#include "Camera.hpp"

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
      * @brief      Construit le mesh
      * @param[in]  path_to_obj      le chemin vers le fichier .obj
      * @param[in]  path_to_texture  le chemin vers le fichier de texture (doit
      *                              être un fichier BMP)
      * @param[in]  program          le shader
      * @param[in]  offset           le décallage
      */
    Mesh(const char * path_to_obj, const char * path_to_texture, ShaderProgram & program, 
            const Vector & offset = Vector());

    /**
     * @brief      Construit le mesh
     * @param[in]  path_to_obj  le chemin vers le fichier .obj
     * @param      camera       la camera
     * @param[in]  program      le shader
     * @param[in]  offset       le décallage
     */
    Mesh(const char * path_to_obj, Camera & camera, ShaderProgram & program,
            const Vector & offset = Vector());

    /**
     * @brief Déstructeur par défaut.
     */
    ~Mesh();

    /**
     * @brief      Initialise ou rafraichie la texture
     * @param      camera  la camera
     */
    void readTextureFromCamera(Camera & camera);

    /**
     * @brief Affiche le mesh.r
     * @param[in] model la matrice modele
        * @param[in] view la matrice vue
     * @param[in] projection la matrice projection
     */
    void draw(const Transform & model, const Transform & view, const Transform & projection) const;

private:
    /**
     * @brief      Initialise les 3 tableaux à partir d'un fichier .obj
     * @param[in]  path_to_obj  Le chemin vers le fichier .obj
     * @param[in]  offset       Le décallage
     */
    void readWaveFront(const char * path_to_obj, const Vector & offset);

    /**
     * @brief      Initialise la VAO à n'appeler que dans le constructeur
     */
    void initVAO();

    /**
     * @brief      Initialise la texture
     * @param[in]  path  Le chemin vers le fichier contenant la texture (doit être un fichier BMP)
     */
    void initTexture(const char * path);

    GLuint              m_program;  //!< Le shader   
    GLuint              m_vao;      //!< Le VAO.
    GLuint              m_vbo;      //!< Le VBO.
    std::vector<vec3>   m_vertices; //!< Les coordonnées des points.
    std::vector<vec3>   m_normals;  //!< Les normales.
    std::vector<vec2>   m_uvs;      //!< Les coordonnées de textures.
    GLuint              m_texture;  //!< La texture
};

#endif
