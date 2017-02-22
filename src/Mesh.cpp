/**
 * @file
 */
#include "Mesh.hpp"
#include "logs.hpp"

Mesh::Mesh(const char * path_to_obj, const char * path_to_texture, ShaderProgram & program, 
           const Vector & offset) : m_program(program), m_texture(0)
{
    mtl::log::info("Chargement du fichier OBJ :", path_to_obj, " --> ", mtl::log::hold_on());
    readWaveFront(path_to_obj, offset);
    initVAO();
    glGenTextures(1, &m_texture);
    initTexture(path_to_texture);
    mtl::log::info("OK");
}

Mesh::~Mesh()
{
    glDeleteTextures(1, &m_texture);
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteVertexArrays(1, &this->m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    this->m_vertices.clear();
    this->m_normals.clear();
    this->m_uvs.clear();
}

void Mesh::readWaveFront(const char * path_to_obj, const Vector & offset)
{
    std::vector<int> vertexIndices, uvIndices, normalIndices;
    std::vector<vec3> temp_vertices;
    std::vector<vec2> temp_uvs;
    std::vector<vec3> temp_normals;

    FILE * file = fopen(path_to_obj, "r");
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
            float x, y, z;
            assert(fscanf(file, "%f %f %f\n", &x, &y, &z));
            vec3 vertex(x + offset.x(), y + offset.y(), z + offset.z());
            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 )
        {
            float x, y;
            assert(fscanf(file, "%f %f\n", &x, &y));
            vec2 uv(x, y);
            temp_uvs.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            float x, y, z;
            assert(fscanf(file, "%f %f %f\n", &x, &y, &z));
            vec3 normal(x, y, z);
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
                &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
                &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
                &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
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
        
        unsigned int vertexIndex = std::abs(vertexIndices[i]);
        unsigned int uvIndex = std::abs(uvIndices[i]);
        unsigned int normalIndex = std::abs(normalIndices[i]);

        vec3 vertex = temp_vertices[ vertexIndex-1 ];
        vec2 uv = temp_uvs[ uvIndex-1 ];
        vec3 normal = temp_normals[ normalIndex-1 ];

        m_vertices.push_back(vertex);
        m_uvs     .push_back(uv);
        m_normals .push_back(normal);
    }
}

void Mesh::initVAO()
{
    std::size_t vbo_vertex_size = m_vertices.size() * sizeof(vec3);
    std::size_t vbo_normal_size = m_normals.size() * sizeof(vec3);
    std::size_t vbo_texture_size = m_uvs.size() * sizeof(vec2);

    const float * vbo_vertex_content = &m_vertices.front()[0];
    const float * vbo_normal_content = &m_normals.front()[0];
    const float * vbo_texture_content = &m_uvs.front()[0];

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vbo_vertex_size + vbo_normal_size + vbo_texture_size, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vbo_vertex_size, vbo_vertex_content);
        glBufferSubData(GL_ARRAY_BUFFER, vbo_vertex_size, vbo_normal_size, vbo_normal_content);
        glBufferSubData(GL_ARRAY_BUFFER, vbo_vertex_size + vbo_normal_size, vbo_texture_size, vbo_texture_content);
        GLint position_location = glGetAttribLocation(m_program, "position");
        GLint normal_location   = glGetAttribLocation(m_program, "normal");
        GLint texture_location  = glGetAttribLocation(m_program, "vertexUV");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vbo_vertex_size));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(texture_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vbo_vertex_size + vbo_normal_size));
            glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

namespace
{
    inline int access(unsigned char* header, int offset)
    {
        int* addrInt = reinterpret_cast<int*>(&header[offset]);
        return *addrInt;
    }
}

void Mesh::initTexture(const char * path)
{
    unsigned char  header[54];
    unsigned int   dataPos;
    unsigned int   imageSize;
    unsigned int   width, height;
    unsigned char* data;

    FILE * file = fopen(path,"rb");
    if (!file)
    {
        mtl::log::error(path, "does not exist");
        assert(false);
    }
    if (fread(header, 1, 54, file)!=54 )
    {
        mtl::log::error("Not a correct BMP file (1)");
        assert(false);
    }
    if (header[0] != 'B' || header[1] != 'M')
    {
        mtl::log::error("Not a correct BMP file (2)");
        assert(false);
    }
    if (access(header, 0x1E) != 0)  {mtl::log::error("Not a correct BMP file (3)");assert(false);}
    if (access(header, 0x1C) != 24) {mtl::log::error("Not a correct BMP file (4)");assert(false);}
    dataPos    = access(header, 0x0A);
    imageSize  = access(header, 0x22);
    width      = access(header, 0x12);
    height     = access(header, 0x16);

    if (imageSize == 0)
        imageSize = width*height*3;
    if (dataPos == 0)
        dataPos = 54;

    data = new unsigned char [imageSize];
    assert(fread(data,1,imageSize,file) == imageSize);
    fclose (file);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    delete [] data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Mesh::draw(const Transform & model, const Transform & view, const Transform & projection) const
{
    glEnable(GL_TEXTURE_2D);

    Transform mv = view * model;
    Transform mvp = projection * mv;
    static GLint mvp_location =  glGetUniformLocation(m_program, "MVP");
    static GLint mv_location  =  glGetUniformLocation(m_program, "MV");
    static GLint n_location   =  glGetUniformLocation(m_program, "N");
    glUniformMatrix4fv(mvp_location, 1, GL_TRUE, mvp.getBuffer());
    glUniformMatrix4fv(mv_location, 1, GL_TRUE, mv.getBuffer());
    glUniformMatrix4fv(n_location, 1, GL_TRUE, mv.getBuffer());

    GLint texture_location = glGetUniformLocation(m_program, "u_texture");
    glUniform1i(texture_location, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
}

