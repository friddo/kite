#pragma once

#include <GL/glew.h>

#include <iostream> 

class Texture {
// TODO: maybe not hardcode GL_TEXTURE_2D

public:

    GLuint texture;
    GLenum format = GL_RGB; // default for now, should maybe be an option.
    int width, height;

    Texture() { glGenTextures(1, &texture); }
    Texture(int w, int h):Texture() {
        width = w, height = h;
    }
    Texture(int w, int h, bool alpha, void* data):Texture(w,h) { 
        if(alpha) format = GL_RGBA;
        init(data);
    }
    ~Texture() {
        glDeleteTextures(1, &texture);
    }
    
    void init(void* data = NULL);

};

// we have a seperate function for actually making the texture. 
// We want to be able to instantiate the texture object without specifying texture data.
void Texture::init(void* data) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); // unbind texture again
}