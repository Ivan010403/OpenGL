#include <stdio.h>
#include <glew.h>
#include <glut.h>
#include "math_3d.h"

GLuint VBO; //указатель на буфер

void RenderSceneCB() {
    glClear(GL_COLOR_BUFFER_BIT); //очистка буфера кадра

    glEnableVertexAttribArray(0); //включаем атрибут вершины

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязываем указатель 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3); //функция для отрисовки

    glDisableVertexAttribArray(0);  

    glutSwapBuffers(); //меняет буфер кадра и фоновый буфер местами
}


void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //указываем что будут хранится вершины в буфере
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //связывание с данными
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  //инициализация glut

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //GLUT_DOUBLE включает двойную буферизацию (отрисовка будет происходить в фоновый буфер, в то время как другой буфер отображается)

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");

    glutDisplayFunc(RenderSceneCB); //функция обратного вызова


    GLenum res = glewInit(); //инициализируем glew
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //цвет, который будет использован во время очистки буфера кадра

    CreateVertexBuffer();

    glutMainLoop(); //передаёт управление основному циклу glut
}