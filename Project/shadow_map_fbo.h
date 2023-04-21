#ifndef SHADOWMAPFBO_H
#define	SHADOWMAPFBO_H

#include <GL/glew.h>

/*Класс ShadowMapFBO предоставляет простой интерфейс для FBO,
который будет использован для наложения теней.
FBO - объект буфера кадра для промежуточного рендера карты теней
*/
class ShadowMapFBO
{
public:
    ShadowMapFBO();

    ~ShadowMapFBO();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void BindForWriting();

    void BindForReading(GLenum TextureUnit);

private:
    GLuint m_fbo; // Текущий FBO
    // Указатель на текстуру, которая будет использована для прикрепления к буферу кадра
    GLuint m_shadowMap;
};

#endif	/* SHADOWMAPFBO_H */

