#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform.hpp>
#include <iostream>
#include<vector>
#include "toys.h"
#include "j3a.hpp"

using namespace glm;
const float PI = 3.141592653;

vec3 lightPos = vec3(3, 5, 5);
vec3 lightInt = vec3(1, 1, 1);
vec3 color = vec3(1,.3,0);
vec3 ambInt = vec3(1, 1, 1);

void render(GLFWwindow* window);
void init();
Program program;
GLuint vertBuf = 0;
GLuint normBuf = 0;
GLuint tcoordBuf = 0;
GLuint vertArray = 0;
GLuint triBuf = 0;

float theta = 0; 
float phi = 0; 
float fovy = 60;

vec3 cameraPosition = vec3(0, 0, 5);

double oldX;
double oldY;

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
        theta -= (xpos - oldX) / width * PI;
        phi -= (ypos - oldY) / height * PI;
    }
    if (phi> PI/2.0f-0.01f) phi = PI/2.0f-0.01f;
    if (phi < -PI/2.0f+0.01f) phi = -PI/2.0f+0.01f;
    oldX = xpos;
    oldY = ypos;
   
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fovy >= 10.f && fovy <= 170.f) {
        fovy = fovy * pow(1.01, yoffset);
    }
    if (fovy <= 10.0f)
        fovy = 10.0f;
    if (fovy >= 170.0f)
        fovy = 170.0f;
}

int main(void) {

    if (!glfwInit())  exit(EXIT_FAILURE);
    
    GLFWwindow* win = glfwCreateWindow(800, 800, "Assignment", nullptr, nullptr);
    
    glfwSetCursorPosCallback(win, cursorCallback);
    glfwSetScrollCallback(win, scrollCallback);
    glfwMakeContextCurrent(win);
    glewInit();
    init();
    while (!glfwWindowShouldClose(win)) {
        render(win);
        glfwPollEvents();
    }
    glfwDestroyWindow(win);
    glfwTerminate();
}

void init() {
    program.loadShaders("shader.vert", "shader.frag");
    loadJ3A("apple.j3a");

    glGenBuffers(1, &vertBuf);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normBuf);
    glBindBuffer(GL_ARRAY_BUFFER, normBuf);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &tcoordBuf);
    glBindBuffer(GL_ARRAY_BUFFER, tcoordBuf);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec2), texCoords[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertArray);
    glBindVertexArray(vertArray);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normBuf);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, tcoordBuf);
    glVertexAttribPointer(2, 2, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &triBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0]*sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);

}

void render(GLFWwindow* window) {
    GLuint loc;
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    
    vec3 cameraPos = vec3(rotate(theta, vec3(0,1,0)) * rotate(phi, vec3(1, 0, 0))*vec4(cameraPosition,1));

    mat4 viewMat = lookAt(cameraPos, vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 projMat = perspective(fovy * PI/ 180, w / (float)h, 0.1f, 100.f);
    mat4 modelMat = mat4(1);

    
    glViewport(0, 0, w, h);
    glClearColor(0, 0, 0.2f, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    glUseProgram(program.programID);

    loc = glGetUniformLocation(program.programID, "modelMat");
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMat));
    loc = glGetUniformLocation(program.programID, "viewMat");
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(viewMat));
    loc = glGetUniformLocation(program.programID, "projMat");
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(projMat));
    
    loc = glGetUniformLocation(program.programID, "lightPos");
    glUniform3fv(loc, 1, glm::value_ptr(lightPos));
    loc = glGetUniformLocation(program.programID, "lightInt");
    glUniform3fv(loc, 1, glm::value_ptr(lightInt));
    loc = glGetUniformLocation(program.programID, "ambInt");
    glUniform3fv(loc, 1, glm::value_ptr(ambInt));
    loc = glGetUniformLocation(program.programID, "color");
    glUniform3fv(loc, 1, glm::value_ptr(color));

    loc = glGetUniformLocation(program.programID, "cameraPos");
    glUniform3fv(loc, 1, glm::value_ptr(cameraPos));


    glBindVertexArray(vertArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
    glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);

}

