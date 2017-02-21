/**
 * @file
 */
#include "MaidDrawer.hpp"

MaidDrawer::MaidDrawer(Player & player, Clothe & maid, ShaderProgram & program) : 
	m_program(program), m_player(player), m_maid(maid)
{
	///Creation de la texture couleur
    glGenTextures(1, &m_color_buffer);
    glBindTexture(GL_TEXTURE_2D, m_color_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0,
        GL_RGBA, 640, 480, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
    glGenSamplers(1, &m_color_sampler);
    glSamplerParameteri(m_color_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(m_color_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(m_color_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glSamplerParameteri(m_color_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    //Creation de la texture depth.
    glGenTextures(1, &m_depth_buffer);
    glBindTexture(GL_TEXTURE_2D, m_depth_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0,
        GL_DEPTH_COMPONENT, 640, 480, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    
    //Creation et configuration du FBO
    glGenFramebuffers(1, &m_frame_buffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frame_buffer);
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_buffer, 0);
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth_buffer, 0);
    
    //Le fragment shader ne declare qu'une seule sortie, indice 0
    GLenum buffers[]= { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, buffers);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    //Nettoyage
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLuint MaidDrawer::draw() const
{
	m_program.use();

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frame_buffer);
    glViewport(0, 0, 640, 480);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Matrices
    //Transform model = translationMatrix(0, 0, 9000) * scaleMatrix(15 * 640.0f, 15 * 480.0f, 1);
    static Transform model(1.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, -1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f);
    Transform view = model*lookAt(Point(0, 0, 0), Point(0, 0, 1), Vector(0, 1, 0));
    Transform projection = perspective(45, 640.0f / 480.0f, 0.1f, 10000.0f);

    //Détection
    m_player.update();
    Point position_1 = m_player.getPointOf(RIGHT_SHOULDER);
    Point position_2 = m_player.getPointOf(LEFT_SHOULDER);

    //Vetement
    if (  position_1.x() != 0 || position_1.y() != 0 || position_1.z() != 0 ||
          position_2.x() != 0 || position_2.y() != 0 || position_2.z() != 0)
    {
        m_maid.draw(position_1, position_2, view, projection);
    }

    return m_frame_buffer;
}
