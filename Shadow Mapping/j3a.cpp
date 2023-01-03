//201821054 미디어학과 하태선 컴퓨터 그래픽스 1차과제

#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <stdio.h>
#include<vector>
#include<math.h>
#include "toys.h"

void render(GLFWwindow* window);
void init();
Program program;
GLuint vertBuf = 0;
GLuint vertArray = 0;
GLuint triBuf = 0;
int n = 70;

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
        render(win);
        glfwPollEvents();
    }
    glfwTerminate();
}

void init() {
    program.loadShaders("shader.vert", "shader.frag");
    std::vector<glm::vec3> vert;
    float r = 0.8;
    float theta = 2 * M_PI / n;
    for (int i = 0; i * theta <= 2 * M_PI; i++) {
        vert.push_back(r * glm::vec3(cos(i * theta), sin(i * theta), 0));
    }


    std::vector<glm::u32vec3> triangles;
    for (int k = 0; k < n; k++) {
        if (k == n)
            triangles.push_back(glm::u32vec3(0, k, 1));
        else
            triangles.push_back(glm::u32vec3(0, k, k + 1));
    }

    glGenBuffers(1, &vertBuf);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
    glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(glm::vec3), vert.data(), GL_STATIC_DRAW);

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
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program.programID);
    glBindVertexArray(vertArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
    glDrawElements(GL_TRIANGLES, 3 * n, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);

}

