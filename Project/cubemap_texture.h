#pragma once
#include <string>
#include <GL/glew.h>
#include <ImageMagick-6\Magick++.h>

using namespace std;

// ����� �������� � ���� ���������� ���������� �������� � ������������� ������� ���������
// ��� �� �������� � �������������
class CubemapTexture
{
public:
    // ����������� ��������� ���������� � 6 ���� ������, ������� �������� ������� ����
    CubemapTexture(const string& Directory,
        const string& PosXFilename,
        const string& NegXFilename,
        const string& PosYFilename,
        const string& NegYFilename,
        const string& PosZFilename,
        const string& NegZFilename);

    ~CubemapTexture();

    // Load() ��� ����, ��� �� ��������� ��� ����������� � ������� ������ �������� OpenGL
    bool Load();

    // ��� ����, ��� �� ������� �������� ��������� ��� �������
    void Bind(GLenum TextureUnit);

private:

    string m_fileNames[6];
    GLuint m_textureObj;
};