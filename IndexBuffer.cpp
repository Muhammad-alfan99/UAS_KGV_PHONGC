#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "util.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Square.h"
#include "Triangle.h"
#include "Shape.h"
#include "Octagon.h"
#include "Circle.h"

#include <vector>

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

float speedUp = 4.0f;
unsigned int program;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        std::cout << "Hello World!\n";
    }
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, keyCallback);
    GLenum err = glewInit();

    Square s1;
    s1.setTranslation(0.5f, 0.7f, 0.0f);
    s1.setScale(0.2f, 0.2f, 1.0f);
    s1.setColor(glm::vec4(0.5f, 0.8f, 1.0f, 1.0f));

    Triangle t1;
    t1.setTranslation(0.06f, 0.0f, 0.0f);
    t1.setScale(0.1f, 0.1f, 1.0f);
    t1.setColor(glm::vec4(0.8f, 0.3f, 0.3f, 1.0f));

    Triangle t2;
    t2.setScale(0.2f, 0.2f, 1.0f);
    t2.setTranslation(0.3f, 0.0f, 0.0f);
    t2.setColor(glm::vec4(0.8f, 0.8f, 0.3f, 1.0f));

    Octagon o1;
    o1.setScale(0.2f, 0.2f, 1.0f);
    o1.setTranslation(-3.5f, 0.0f, 0.0f);
    o1.setColor(glm::vec4(0.9f, 0.7f, 0.5f, 1.0f));

    Circle c1;
    c1.setScale(0.2f, 0.2f, 1.0f);
    c1.setTranslation(2.5f, 0.0f, 0.0f);
    c1.setColor(glm::vec4(0.5f, 0.1f, 0.5f, 1.0f));

    vector<Shape*> shapes;

    shapes.push_back(&s1);
    shapes.push_back(&t2);
    shapes.push_back(&t1);
    shapes.push_back(&o1);
    shapes.push_back(&c1);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);


    GLint uColor = glGetUniformLocation(program, "uColor");
    GLint uMat4x4 = glGetUniformLocation(program, "transformationMat4x4");

    Shape* shape;


    //Square s2;
    //s2.setTranslation(0.0f, 0.1f, 0.0f);
    //s2.setScale(0.1f, 0.4f, 1.0f);
    //s2.setColor(glm::vec4(1.0f, 0.5f, 0.0f, 0.0f));
    //Square s3;
    //s3.setRotation(glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //s3.setScale(0.05f, 0.3f, 0.0f);
    //s3.setTranslation(5.5f, -0.5f, 0.0f);
    //s3.setColor(glm::vec4(0.6f, 0.25f, 0.72f, 1.0f));

    //Square s4;
    //s4.setRotation(glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //s4.setScale(0.05f, 0.3f, 0.0f);
    //s4.setTranslation(5.35f, 0.375f, 0.0f);
    //s4.setColor(glm::vec4(0.6f, 0.25f, 0.72f, 1.0f));

    //Square s5;
    //s5.setTranslation(0.255f, -0.525f, 0.0f);
    //s5.setRotation(glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //s5.setScale(0.05f, 0.35f, 0.0f);
    //s5.setColor(glm::vec4(0.65f, 0.3f, 0.3f, 1.0f));

    //Square s6;
    //s6.setTranslation(-0.255f, -0.525f, 0.0f);
    //s6.setRotation(glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //s6.setScale(0.05f, 0.35f, 0.0f);
    //s6.setColor(glm::vec4(0.65f, 0.3f, 0.3f, 1.0f));


    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime) * speedUp;
        lastTime = currentTime;

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

       
        for (int i = 0; i < shapes.size(); i++)
        {
            shape = shapes.at(i);
            glUniform4fv(uColor, 1, &(shape->getColor()[0]));
            glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &(shape->getTransformationMat4x4()[0][0]));
            shapes.at(i)->draw();
        }
        /*glUniform4fv(uColor, 1, &s1.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s1.getTransformationMat4x4()[0][0]);
        s1.draw();*/

        //glUniform4fv(uColor, 1, &s3.getColor()[0]);
        //glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s3.getTransformationMat4x4()[0][0]);
        //s3.draw();

        //glUniform4fv(uColor, 1, &s4.getColor()[0]);
        //glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s4.getTransformationMat4x4()[0][0]);
        //s4.draw();

        //glUniform4fv(uColor, 1, &s5.getColor()[0]);
        //glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s5.getTransformationMat4x4()[0][0]);
        //s5.draw();

        //glUniform4fv(uColor, 1, &s6.getColor()[0]);
        //glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s6.getTransformationMat4x4()[0][0]);
        //s6.draw();

        //glUniform4fv(uColor, 1, &s2.getColor()[0]);
        //glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &s2.getTransformationMat4x4()[0][0]);
        //s2.draw();

        /*glUniform4fv(uColor, 1, &t1.getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &t1.getTransformationMat4x4()[0][0]);
        t1.draw();*/

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}