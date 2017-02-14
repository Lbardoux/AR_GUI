/**
 * @file
 */
#include "Mesh.hpp"

Mesh::Mesh(const char * path, ShaderProgram & program) : m_program(program)
{
    std::cout<<"Chargement du fichier OBJ : \'"<<path<<"\' ... ";

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
            float x, y, z;
            assert(fscanf(file, "%f %f %f\n", &x, &y, &z));
            vec3 vertex(x, y, z);
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

    initVAO();

    std::cout<<"Fait"<<std::endl;
}

void Mesh::initVAO()
{
    std::size_t vbo_vertex_size = m_vertices.size() * sizeof(vec3);
    std::size_t vbo_normal_size = m_normals.size() * sizeof(vec3);    
    std::size_t vbo_texture_size = m_uvs.size() * sizeof(vec2);

    const float * vbo_vertex_content = &m_vertices.front()[0];
    const float * vbo_normal_content = &m_normals.front()[0];
    const float * vbo_texture_content = &m_uvs.front()[0];

    //On vérifie que notre buffer n'est pas déjà alloué, si c'est le cas, on libere l'espace
    if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
    //On alloue un espace mémoire pour le vbo
    glGenBuffers(1, &m_vbo);
    //On bind le vbo afin de l'utiliser
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        //On alloue un espace mémoire pour toutes les données du buffer: nos vertex et nos normals
        glBufferData(GL_ARRAY_BUFFER, vbo_vertex_size + vbo_normal_size + vbo_texture_size, 0, GL_STATIC_DRAW);
        //On remplie le buffer avec nos vertex, on remplie de: 0 à vertex_buffer_size()
        glBufferSubData(GL_ARRAY_BUFFER, 0, vbo_vertex_size, vbo_vertex_content);        
        //On remplie le buffer avec nos normals, on remplie de: vertex_buffer_size() à normal_buffer_size()  
        glBufferSubData(GL_ARRAY_BUFFER, vbo_vertex_size, vbo_normal_size, vbo_normal_content);
        //On remplie avec les coordonnées de texture
        glBufferSubData(GL_ARRAY_BUFFER, vbo_vertex_size + vbo_normal_size, vbo_texture_size, vbo_texture_content);
        //On cherche les zones ou se trouves les "in variables"
        GLint position_location = glGetAttribLocation(m_program, "position");
        GLint normal_location   = glGetAttribLocation(m_program, "normal");
        GLint texture_location  = glGetAttribLocation(m_program, "vertexUV");
    //On débind le vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //On vérifie que notre array n'est pas déjà alloué, si c'est le cas, on libère l'espace
    if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
    //On crée notre vao
    glGenVertexArrays(1, &m_vao);
    //On bind le vao, afin de l'utiliser
    glBindVertexArray(m_vao);
        //On bind le vbo afin de l'utiliser
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            //On link nos données "vertex" (qui commence à partir de "0") du buffer à la "in variable" "position" 
            glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
            //On link nos données "normal" (qui commence à partir de "vertex_buffer_size()") du buffer à la "in variable" "normal"
            glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vbo_vertex_size));
            glEnableVertexAttribArray(1);
            //On link nos données "texture"
            glVertexAttribPointer(texture_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vbo_vertex_size + vbo_normal_size));
            glEnableVertexAttribArray(2);
        //On débind le vbo
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //On débind le vao
    glBindVertexArray(0);
}

void Mesh::draw(const Transform & model, const Transform & view, const Transform & projection) const
{
    Transform mv = model * view;
    Transform mvp = model * view * projection;

    /*for(int i = 0; i < 16; i++)
    {
        std::cout<<model.getBuffer()[i]<<std::endl;
    }
    std::cout<<std::endl<<std::endl;*/

    GLint mvp_location =  glGetUniformLocation(m_program, "MVP");
    GLint mv_location  =  glGetUniformLocation(m_program, "MV");
    //GLint n_location   =  glGetUniformLocation(m_program, "N");

    glUniformMatrix4fv(mvp_location, 1, GL_TRUE, mvp.getBuffer());
    glUniformMatrix4fv(mv_location, 1, GL_TRUE, mv.getBuffer());
    //glUniformMatrix4fv(n_location, 1, GL_TRUE, mv.normal().getBuffer());

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());  
    glBindVertexArray(0);
}
