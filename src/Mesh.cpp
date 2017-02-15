/**
 * @file
 */
#include "Mesh.hpp"

Mesh::Mesh(const char * path_to_obj, const char * path_to_texture, ShaderProgram & program) : m_program(program)
{
    std::cout<<"Chargement du fichier OBJ : \'"<<path_to_obj<<"\' ... ";
    readWaveFront(path_to_obj);
    initVAO();
    initTexture(path_to_texture);
    std::cout<<"Fait"<<std::endl;
}

Mesh::Mesh(const char * path_to_obj, Camera & camera, ShaderProgram & program) : m_program(program)
{
    std::cout<<"Chargement du fichier OBJ : \'"<<path_to_obj<<"\' ... ";
    readWaveFront(path_to_obj);
    initVAO();
    readTextureFromCamera(camera);
    std::cout<<"Fait"<<std::endl;
}

void Mesh::readWaveFront(const char * path_to_obj)
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
            int vertexIndex[3], uvIndex[3], normalIndex[3];
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

void Mesh::readTextureFromCamera(Camera & camera)
{
    camera.readFrame();
    cv::Mat mat = camera.colorFrame();

    GLenum minFilter = GL_NEAREST;
    GLenum magFilter = GL_NEAREST;
    GLenum wrapFilter = GL_CLAMP;

    // Generate a number for our textureID's unique handle
    GLuint textureID;
    glGenTextures(1, &textureID);
 
    // Bind to our texture handle
    glBindTexture(GL_TEXTURE_2D, textureID);
 
    // Catch silly-mistake texture interpolation method for magnification
    if (magFilter == GL_LINEAR_MIPMAP_LINEAR  ||
        magFilter == GL_LINEAR_MIPMAP_NEAREST ||
        magFilter == GL_NEAREST_MIPMAP_LINEAR ||
        magFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        std::cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << std::endl;
        magFilter = GL_LINEAR;
    }
 
    // Set texture interpolation methods for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
 
    // Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);
 
    // Set incoming texture format to:
    // GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
    // GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
    // Work out other mappings as required ( there's a list in comments in main() )
    GLenum inputColourFormat = GL_BGRA;
    if (mat.channels() == 1)
    {
        inputColourFormat = GL_LUMINANCE;
    }
 
    // Create the texture
    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,            // Internal colour format to convert to
                 mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
                 mat.rows,          // Image height i.e. 480 for Kinect in standard mode
                 0,                 // Border width in pixels (can either be 1 or 0)
                 inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE,  // Image data type
                 mat.ptr());        // The actual image data itself
 
    // If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
    if (minFilter == GL_LINEAR_MIPMAP_LINEAR  ||
        minFilter == GL_LINEAR_MIPMAP_NEAREST ||
        minFilter == GL_NEAREST_MIPMAP_LINEAR ||
        minFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
 
    m_texture = textureID;
}

void Mesh::initTexture(const char * path)
{
    printf("Reading image %s\n", path);

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    // Actual RGB data
    unsigned char * data;

    // Open the file
    FILE * file = fopen(path,"rb");
    if (!file) {
        printf("Not exist\n");
        assert(false);
    }

    // If less than 54 bytes are read, problem
    if ( fread(header, 1, 54, file)!=54 ){
        printf("Not a correct BMP file (1)\n");
        assert(false);
    }
    // A BMP files always begins with "BM"
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file (2)\n");
        assert(false);
    }
    // Make sure this is a 24bpp file
    if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file (3)\n");    assert(false);}
    if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file (4)\n");    assert(false);}

    // Read the information about the image
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    // Everything is in memory now, the file wan be closed
    fclose (file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // OpenGL has now copied the data. Free our own version
    delete [] data;

    // ... nice trilinear filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Return the ID of the texture we just created
    m_texture = textureID;
}

void Mesh::draw(const Transform & model, const Transform & view, const Transform & projection) const
{
    glEnable(GL_TEXTURE_2D);

    //Matrices
    Transform mv = view * model;
    Transform mvp = projection * mv;
    GLint mvp_location =  glGetUniformLocation(m_program, "MVP");
    GLint mv_location  =  glGetUniformLocation(m_program, "MV");
    GLint n_location   =  glGetUniformLocation(m_program, "N");
    glUniformMatrix4fv(mvp_location, 1, GL_TRUE, mvp.getBuffer());
    glUniformMatrix4fv(mv_location, 1, GL_TRUE, mv.getBuffer());
    glUniformMatrix4fv(n_location, 1, GL_TRUE, mv.getBuffer());
    /*for(int i = 0; i < 16; i++)
    {
        std::cout<<model.getBuffer()[i]<<std::endl;
    }
    std::cout<<std::endl<<std::endl;*/

    //Texture
    GLint texture_location = glGetUniformLocation(m_program, "u_texture");
    glUniform1i(texture_location, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    //Triangles
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());  
    glBindVertexArray(0);
}

