#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include<vector>
#include<math.h>
#include "toys.h"

using namespace glm;
void render(GLFWwindow* window);
void init();
Program program;
GLuint vertBuf = 0;
GLuint vertArray = 0;
GLuint triBuf = 0;

float theta = 0.0;

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* win = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
    glfwMakeContextCurrent(win);
    glewInit();
    glfwSwapInterval(1);
    init();
    while (!glfwWindowShouldClose(win)) {
        theta += 5/180.0*M_PI ;
        if (theta > 2*M_PI) theta = 0.1;
        render(win);
        glfwPollEvents();
    }
    glfwTerminate();
}

void init() {
    program.loadShaders("shader.vert", "shader.frag");
    std::vector<vec3> vert;
    vert.push_back(vec3(0, 0.7, 0));
    vert.push_back(vec3(-0.7, -0.7, 0));
    vert.push_back(vec3(0.7, -0.7, 0));

    std::vector<u32vec3> triangles;
    triangles.push_back(u32vec3(0, 1, 2));

    glGenBuffers(1, &vertBuf);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
    glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(vec3), vert.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertArray);
    glBindVertexArray(vertArray);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &triBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(glm::u32vec3), triangles.data(), GL_STATIC_DRAW);

}

void render(GLFWwindow* window) {
    GLuint loc;
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0, 0, 0.2, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program.programID);

    loc = glGetUniformLocation(program.programID, "transf");
    mat3 transf = mat3(cos(theta),sin(theta),0, -sin(theta),cos(theta),0,  0,0,1);
    glUniformMatrix3fv(loc, 1, false, value_ptr(transf));
    glBindVertexArray(vertArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);

}

