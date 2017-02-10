/**
 * @file Mesh.hpp
 * @brief Interface permettant d'afficher un mesh
 * @author Charles Sultan p1207507
 * @version 1.0
 */
#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <iostream>
#include <array>
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct vec2
{
	float x, y;
};

struct vec3
{
	float x, y, z;
};

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
	Mesh(char * path);

	/**
     * @brief Déstructeur par défaut.
     */
	~Mesh() = default;

	/**
     * @brief Affiche le mesh.
     */
	void Draw() const;

private:
	void initVAO();
/*
	std::vector<vec3> 	m_vertices;
	std::vector<vec2> 	m_uvs;
	std::vector<vec3> 	m_normals;
	GLuint 				m_vao;*/
};

#endif