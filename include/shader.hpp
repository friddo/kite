#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

class Shader {

private:
    GLuint vertexShader, fragmentShader;

    std::string readfile(std::string filename);
    void checkCompileErrors(int program);

public:
    GLuint program;    
    int boundTextures;  // for texture indexing

    Shader() {
        program = glCreateProgram();
    }
    Shader(std::string vertex, std::string fragment, std::vector<std::string> in) : Shader() {
        vertexShader = add(vertex, GL_VERTEX_SHADER);
        fragmentShader = add(fragment, GL_FRAGMENT_SHADER);
        for(int i = 0; i < in.size(); i++) {
            glBindAttribLocation(program, i, in[i].c_str());
        }
        link();
    }
    ~Shader() {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
    }

    int add(std::string filename, GLuint type);
    void compile(GLuint shader);
    void link();
    void use();
    //static void bind(); 


    // for setting shader uniforms and samplers
    template<typename T> void uniform(std::string name, const T u);
    template<typename T> void texture(std::string name, const T& t);

};


int Shader::add(std::string filename, GLuint type) {
    std::string file = readfile(filename); // get the shader source code
    const char* str = file.c_str();
    int shaderID = glCreateShader(type);    // create the shader
    glShaderSource(shaderID, 1, &str, NULL);
    compile(shaderID);

    return shaderID;
}

void Shader::compile(GLuint shader) {
    glCompileShader(shader); // TODO: error handling
    checkCompileErrors(shader);
    glAttachShader(program, shader);
}

void Shader::link() {
    glLinkProgram(program); // TODO: error handling
}

void Shader::use() {
    boundTextures = 0;
    glUseProgram(program); // TODO: error handlings
}


std::string Shader::readfile(std::string filename) {
    std::string fileContent;
    try
    {
        // open file
        std::ifstream file(filename);
        std::stringstream fileStream;
        // read file's buffer contents into streams
        fileStream << file.rdbuf();
        // close file handlers
        file.close();
        // convert stream into string
        fileContent = fileStream.str();
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
        exit(1);
    }
    return fileContent;
}

// uniforms

template<> void Shader::uniform(std::string name, const bool u) {
    glUniform1i(glGetUniformLocation(program, name.c_str()), u);
}

template<> void Shader::uniform(std::string name, const int u) {
    glUniform1i(glGetUniformLocation(program, name.c_str()), u);
}

template<> void Shader::uniform(std::string name, const float u) {
    glUniform1f(glGetUniformLocation(program, name.c_str()), u);
}

template<> void Shader::uniform(std::string name, const double u) {
    glUniform1f(glGetUniformLocation(program, name.c_str()), (float)u);
}

template<> void Shader::uniform(std::string name, const glm::vec2 u) {
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &u[0]);
}

template<> void Shader::uniform(std::string name, const glm::ivec2 u) {
    glUniform2iv(glGetUniformLocation(program, name.c_str()), 1, &u[0]);
}

template<> void Shader::uniform(std::string name, const glm::vec3 u) {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &u[0]);
}

template<> void Shader::uniform(std::string name, const float (&u)[3]) {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &u[0]);
}

template<> void Shader::uniform(std::string name, const float (&u)[4]) {
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &u[0]);
}

template<> void Shader::uniform(std::string name, const glm::vec4 u) {
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &u[0]); 
}

template<> void Shader::uniform(std::string name, const glm::mat3 u) {
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &u[0][0]);
}

template<> void Shader::uniform(std::string name, const glm::mat4 u) {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &u[0][0]);
}


// textures
template<typename T>
void Shader::texture(std::string name, const T& tex){
    glActiveTexture(GL_TEXTURE0 + boundTextures);
    glBindTexture(GL_TEXTURE_2D, tex.texture);
    uniform(name, boundTextures++);
}


void Shader::checkCompileErrors(int shader)
{
    int status;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "Shader compile error:" << "\n" << infoLog << std::endl;
    }
}