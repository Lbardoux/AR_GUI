/**
 * @file
 */
#include "Mesh.hpp"

Mesh::Mesh(const char * path)
{
    /*std::cout<<"Chargement du fichier OBJ : "<<path<<std::endl;

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<vec3> temp_vertices;
    std::vector<vec2> temp_uvs;
    std::vector<vec3> temp_normals;

    FILE * file = fopen(path, "r");
    if(file == NULL)
    {
        std::cout<<"Impossible d'ouvrir le fichier"<<std::endl;
        assert(false);
    }

    while(1)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            vec3 vertex;
            assert(fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z ));
            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 )
        {
            vec2 uv;
            assert(fscanf(file, "%f %f\n", &uv.x, &uv.y ));
            temp_uvs.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            vec3 normal;
            assert(fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z ));
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9)
            {
                std::cout<<"Le fichier ne peut être lu par ce parseur"<<std::endl;
                assert(false);
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);

        }
        else
        {
            char stupidBuffer[1000];
            assert(fgets(stupidBuffer, 1000, file));
        }

    }

    for(unsigned int i=0; i<vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        vec3 vertex = temp_vertices[ vertexIndex-1 ];
        vec2 uv = temp_uvs[ uvIndex-1 ];
        vec3 normal = temp_normals[ normalIndex-1 ];

        m_vertices.push_back(vertex);
        m_uvs     .push_back(uv);
        m_normals .push_back(normal);
    }

    initVAO();*/
}

void Mesh::initVAO()
{
	/*GLuint vertex_buffer;
    GLuint normal_buffer;
    GLuint texture_buffer;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vec3), &m_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(vec3), &m_normals[0], GL_STATIC_DRAW);

    if (uvs.size() > 0)
    {
        glGenBuffers(1, &texture_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
        glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(vec2), &m_uvs[0], GL_STATIC_DRAW);
    }

    GLint attribute = 0;
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribute);

    attribute = 1;
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribute);

    if (uvs.size() > 0)
    {
        attribute = 2;
        glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
        glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(attribute);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/
}

void Mesh::draw() const
{
	/*glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);*/
}
