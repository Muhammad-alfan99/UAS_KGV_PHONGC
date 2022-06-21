#include "Octagon.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
unsigned int Octagon::vertexArray = 0;
unsigned int Octagon::vertexBuffer = 0;
unsigned int Octagon::indexBuffer = 0;
float xp, yp, r = 1, n = 8, a = 0.5f, x, y;
float increment = 0.05f, z = 0.0f;
unsigned int Octagon::u = 0;

Octagon::Octagon()
{
    float vertices[36] = {};

    a = (2 * 3.14) / n; //a = nilai 6.28 dibagi banyak segi
    std::cout<< a;
    std::cout << "\n\n";
    for (int i = 0; i < n; i++) {
        x = xp + r * cos(i * a);
        y = yp + r * sin(i * a);
        vertices[u] = x;
        u = u + 1;
        vertices[u] = y;
        u = u + 1;
        vertices[u] = 0.0f;
        u = u + 1;
        vertices[u] = 0.0f;
        u = u + 1;
    }
    vertices[32] = xp;
    vertices[33] = yp;
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

void Octagon::draw()
{
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);
    if (z > 1.0f)
        increment = -0.005f;
    else if (z < 0.0f)
        increment = 0.005f;

    z += increment;
}


