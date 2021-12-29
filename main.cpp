#include <iostream>
#include "headers/shader.h"
#include "headers/object.h"
#include "headers/camera.h"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
// GLFW
#include <GLFW/glfw3.h>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
const GLuint WIDTH = 1000, HEIGHT = 1000;

std::vector<bool> keys(1024,false);

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  
    glViewport(0, 0, width, height);


    Shader sh;
    sh.LoadShader("shaders/vshader.glsl","shaders/fshader.glsl");


    glm::vec4 light = glm::vec4(0.0f,0.0f,-10.0f,1.0f);
    float lightpow = 1000.0f;
    Object obj;
    obj.LoadObject("Skull_my.obj");

    glm::mat4 trans(1.0f);
    Camera cam(WIDTH,HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        light = glm::rotate(glm::mat4(1.0f),glm::radians(deltaTime*30),glm::vec3(0.0f,1.0f,0.0f))*light;
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.Control(keys,deltaTime);
        cam.DrawObj(obj,sh,light,lightpow);


        glfwSwapBuffers(window);
        if(keys[GLFW_KEY_P]){
            sh.LoadShader("shaders/vshader.glsl","shaders/fshader.glsl");
            keys[GLFW_KEY_P] = false;
        }
    }
    

    glfwTerminate();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key > 0 && key < 1024){
        if(action == GLFW_PRESS)
            keys[key] = true;
        else if(action == GLFW_RELEASE)
            keys[key] = false;	
    }
}

