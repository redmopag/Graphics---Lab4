#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <math.h>

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int cCube;
const char* skybox[6] = { "../Content/right.jpg",
"../Content/left.jpg" ,
"../Content/top.jpg" ,
"../Content/bottom.jpg",
"../Content/front.jpg",
"../Content/back.jpg"
};


void LoadTextureCube(const char* filename[6], unsigned int* target) {
    glGenTextures(1, target);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *target); //делаем текстуру активной, 1 -тип текстуры, 2 - номер текстуры

    //задаем как текстура д.б. наложена:
    //GL_TEXTURE_CUBE_MAP - cube 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, cnt;
    unsigned char* data;
    for (int i = 0; i < 6; i++) {
        data = stbi_load(filename[i], &width, &height, &cnt, 0);
        //GL_TEXTURE_CUBE_MAP_POSITIVE_X - код первой грани кубической текстуры,
        //остальные грани идут подряд
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
            width, height, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
}

float cube[] = { -1,-1,1, 1,-1,1, 1,1,1, -1,1,1,
                -1,-1,-1, 1,-1,-1, 1,1,-1, -1,1,-1 };
unsigned int cubeInd[] = { 0,1,2,2,3,0, 4,5,6,6,7,4,
                         1,5,6,6,2,1, 0,4,7,7,3,0,
                         3,2,6,6,7,3, 0,1,5,5,4,0 };
int cubeIndCnt = sizeof(cubeInd) / sizeof(cubeInd[0]);



void ShowCube() {

    glUseProgram(0); //используем стандартные шейдеры
    glEnable(GL_TEXTURE_CUBE_MAP); //разрешаем использовать кубические текстуры

    glActiveTexture(GL_TEXTURE0); //актвируем текстуру
    glBindTexture(GL_TEXTURE_CUBE_MAP, cCube);

    glVertexPointer(3, GL_FLOAT, 0, cube); //путь массива вершин и массив текстурных координат
    glTexCoordPointer(3, GL_FLOAT, 0, cube);

    glPushMatrix();
    glDisable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDrawElements(GL_TRIANGLES, cubeIndCnt, GL_UNSIGNED_INT, cubeInd);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glDisable(GL_TEXTURE_CUBE_MAP);
}



float X_alfa = 20;
float Z_alfa = 0;
void MoveCamera() {
    if (GetKeyState(VK_UP) < 0) X_alfa = ++X_alfa;
    if (GetKeyState(VK_DOWN) < 0) X_alfa = --X_alfa;
    if (GetKeyState(VK_LEFT) < 0) Z_alfa++;
    if (GetKeyState(VK_RIGHT) < 0) Z_alfa--;

    glRotatef(-X_alfa, 1, 0, 0);
    glRotatef(-Z_alfa, 0, 1, 0);

}


void Init() {
    gladLoadGL();
    Z_alfa = 0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float k = 1200 / (float)720;
    glFrustum(-0.1 * k, 0.1 * k, -0.1, 0.1, 0.2, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    LoadTextureCube(skybox, &cCube);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) //1- указатель на окно, 2 - кнопка, 3 - действие над клавишей, 4 - модификаторы
{
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
    // и приложение после этого закроется
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}



int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 720, "World", primary, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    Init();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))  //цикл, работающий пока окно не закрыто
    {
        glClearColor(0.3f, 0.2f, 0.1f, 0.1f);  //цвет зачистки
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        MoveCamera();
        ShowCube();
        glPopMatrix();

        glfwSetKeyCallback(window, key_callback); //ф-я выхода на Еск

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        Sleep(1);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
