#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "buffer.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "target.hpp"
#include "texture.hpp"


namespace kite {
    
    GLFWwindow* win;


    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }  


    static void init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);
        #ifdef __APPLE__ // apple requires forward compatability
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif  
    }

    static GLFWwindow* window(int width, int height, const char* title) {
        win = glfwCreateWindow(width, height, title, NULL, NULL);
        if (win == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(1);
        }
        glfwMakeContextCurrent(win);
        glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

        if (glewInit() != GLEW_OK) {
            // Handle initialization error
            fprintf(stderr, "Error initializing GLEW\n");
            exit(1);
        }
        glEnable(GL_DEPTH_TEST); // enable depth testing
        glfwSwapInterval(1); // enable vsync
        return win;
    }

    static void poll() {
        glfwPollEvents();
    }

    static void targetwindow(bool clear = true) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // update the viewport dimensions, since the draw.target call changed it.
        int width, height;
        glfwGetFramebufferSize(win, &width, &height);
        glViewport(0,0,width,height);
        if(clear) {
            // clear the screen
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // some random color
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }

    static bool running() {
        return !glfwWindowShouldClose(win);
    }

    static void end_draw() {
        glfwSwapBuffers(win);
        glFinish(); // wait for all draw calls to be finished
    }

    static void close() {
        glfwTerminate(); // TODO: ressource cleanup on all allocated objects
    }

}
