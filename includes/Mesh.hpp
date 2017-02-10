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
#include <stdio.h>
#include <string.h>

/**
 * @class Mesh
 * @brief Cette structure permet de d'afficher un mesh.
 */
class Mesh
{
public:
	/**
     * TODO
     */
	Mesh(const char * path);

	/**
     * @brief Déstructeur par défaut.
     */
	~Mesh() = default;

	/**
     * @brief Affiche le mesh.
     */
	void draw() const;

private:
	void initVAO();
/*
	std::vector<vec3> 	m_vertices;
	std::vector<vec2> 	m_uvs;
	std::vector<vec3> 	m_normals;
	GLuint 				m_vao;*/
};

#endif