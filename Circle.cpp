#include "Circle.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
unsigned int Circle::vertexArray = 0;
unsigned int Circle::vertexBuffer = 0;
unsigned int Circle::indexBuffer = 0;
float xp2, yp2, r2 = 1, n2 = 8, a2 = 0.5f, x2, y2;
unsigned int Circle::u = 0;

Circle::Circle()
{
    float vertices[36] = {};

    a2 = (2 * 3.14) / n2; //a = nilai 6.28 dibagi banyak segi
    std::cout << a2;
    std::cout << "\n\n";
    for (int i = 0; i < n2; i++) {
        if (i % 2 == 1) {
        x2 = xp2 + (r2-0.55f) * cos(i * a2);
        y2 = yp2 + (r2-0.55f) * sin(i * a2);
        }
        else {
        x2 = xp2 + r2 * cos(i * a2);
        y2 = yp2 + r2 * sin(i * a2);
        }
        vertices[u] = x2;
        u = u + 1;
        vertices[u] = y2;
        u = u + 1;
        vertices[u] = 0.0f;
        u = u + 1;
        vertices[u] = 0.0f;
        u = u + 1;
    }
    vertices[32] = xp2;
    vertices[33] = yp2;
    vertices[34] = 0.0f;
    vertices[35] = 0.0f;

    for (int i = 0; i < 37; i++) {
        std::cout << vertices[i];
        std::cout << "\n";
    }

    unsigned int indexArr[24] = {
    0,1,8,
    1,2,8,
    2,3,8,
    3,4,8,
    4,5,8,
    5,6,8,
    6,7,8,
    7,0,8
    };

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 24, indexArr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)));
}

void Circle::draw()
{
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);
}


