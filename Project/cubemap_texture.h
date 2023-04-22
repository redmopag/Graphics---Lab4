#pragma once
#include <string>
#include <GL/glew.h>
#include <ImageMagick-6\Magick++.h>

using namespace std;

// класс включает в себ€ реализацию кубической текстуры и предоставл€ет простой интерфейс
// дл€ ее загрузки и использовани€
class CubemapTexture
{
public:
    //  онструктор принимает директорию и 6 имен файлов, которые содержат стороны куба
    CubemapTexture(const string& Directory,
        const string& PosXFilename,
        const string& NegXFilename,
        const string& PosYFilename,
        const string& NegYFilename,
        const string& PosZFilename,
        const string& NegZFilename);

    ~CubemapTexture();

    // Load() дл€ того, что бы загрузить все изображени€ и создать объект текстуры OpenGL
    bool Load();

    // дл€ того, что бы сделать текстуру доступной дл€ шейдера
    void Bind(GLenum TextureUnit);

private:

    string m_fileNames[6];
    GLuint m_textureObj;
};