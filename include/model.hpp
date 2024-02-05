#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <string>

#include "buffer.hpp"


struct Model {

    GLuint vao;
    size_t size = 0;    // number of vertices needed to draw the object
    GLenum mode = GL_TRIANGLE_STRIP;

    std::unordered_map<std::string, int> bindings;  // locations of bindings

    glm::mat4 model = glm::mat4(1.0f);  // model matrix to use for vertex shader


    Model(){
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    ~Model(){
        glDisableVertexAttribArray(vao);
        glDeleteVertexArrays(1, &vao);
    }

    Model(std::vector<std::string> nbinding):Model(){ // generate a model which has predefined bindings
        for(auto& b: nbinding) {
            bindings[b] = bindings.size();          // next available index
            glEnableVertexAttribArray(bindings[b]); // add it
        }
    }

    template<typename T>
    void bind(std::string binding, Buffer* buffer) { // bind a buffer to the model
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, buffer->index);
        glVertexAttribPointer(bindings[binding], sizeof(T)/sizeof(GL_FLOAT), GL_FLOAT, GL_FALSE, 0, 0);
    }

    void render(){
        glBindVertexArray(vao);
        glDrawArrays(mode, 0, size);
    }

};

struct Plane : Model {
    Buffer vert, tex;
    Plane():Model({"in_Quad", "in_Tex"}),
    vert({-1.0f,  -1.0f,  0.0f, -1.0f, 1.0f,  0.0f,  1.0f,  -1.0f,  0.0f,  1.0f, 1.0f,  0.0f}),
    tex({ 0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  1.0f,  1.0f}){
        bind<glm::vec3>("in_Quad", &vert);
        bind<glm::vec2>("in_Tex", &tex);
        size = 4;
    }
};

struct Cube : Model {
  Buffer vert, tex;
  Cube():Model({"in_Quad", "in_Tex"}),
  vert({ /* Front */ -1.0f, -1.0f, -1.0f,  
                      1.0f, -1.0f, -1.0f, 
                      1.0f,  1.0f, -1.0f, 
                      1.0f,  1.0f, -1.0f, 
                     -1.0f,  1.0f, -1.0f, 
                     -1.0f, -1.0f, -1.0f,
                     
         /* Back  */ -1.0f, -1.0f, 1.0f,  
                      1.0f, -1.0f, 1.0f, 
                      1.0f,  1.0f, 1.0f, 
                      1.0f,  1.0f, 1.0f,
                     -1.0f,  1.0f, 1.0f,
                     -1.0f, -1.0f, 1.0f,

         /* Left  */ -1.0f,  1.0f,  1.0f, 
                     -1.0f,  1.0f, -1.0f,
                     -1.0f, -1.0f, -1.0f, 
                     -1.0f, -1.0f, -1.0f, 
                     -1.0f, -1.0f,  1.0f, 
                     -1.0f,  1.0f,  1.0f,

         /* Right */  1.0f,  1.0f,  1.0f, 
                      1.0f,  1.0f, -1.0f, 
                      1.0f, -1.0f, -1.0f, 
                      1.0f, -1.0f, -1.0f, 
                      1.0f, -1.0f,  1.0f, 
                      1.0f,  1.0f,  1.0f,

         /* Top   */ -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f,  1.0f,
                     -1.0f, -1.0f,  1.0f,
                     -1.0f, -1.0f, -1.0f,

         /* Bottom*/ -1.0f,  1.0f, -1.0f,  
                      1.0f,  1.0f, -1.0f, 
                      1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                     -1.0f,  1.0f,  1.0f,
                     -1.0f,  1.0f, -1.0f 
        }),
  tex({ 0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f}){
    bind<glm::vec3>("in_Quad", &vert);
    bind<glm::vec2>("in_Tex", &tex);
    size = 36;
    mode = GL_TRIANGLES; // this model uses individually defined triangles
  }
};
