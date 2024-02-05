#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

#include "texture.hpp"

class Target {
public:

    unsigned int width, height;
    GLuint fbo;         

    std::vector<GLenum> attachments;
    bool hasdepth = false;         

    Target(int W, int H){
        width = W; height = H;
        glGenFramebuffers(1, &fbo);
    }

    ~Target(){ glDeleteFramebuffers(1, &fbo); }           //Default destructor


    template<typename T>
    void bind(T& tex, GLenum type = GL_COLOR_ATTACHMENT0) { // bind a texture to a specific attachment
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture(GL_FRAMEBUFFER, type, tex.texture, 0);
        if(type != GL_DEPTH_ATTACHMENT){
            attachments.push_back(type);
            glDrawBuffers(attachments.size(), &attachments[0]);
        } else {
            hasdepth = true;
            if(attachments.empty()) glDrawBuffer(GL_NONE); 
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void target(bool clear = true) { // use this framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, width, height);
        if(clear) glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

};

class Billboard: public Target {
public:
    Texture texture, depth;

    Billboard(int _W, int _H):
    Target(_W, _H),texture(_W, _H),depth(_W, _H){
        texture.init();
        bind(texture, GL_COLOR_ATTACHMENT0);
        depth.format = GL_DEPTH_COMPONENT; // TODO: dont hardcode this
        depth.init();
        bind(depth, GL_DEPTH_ATTACHMENT);
    }
};