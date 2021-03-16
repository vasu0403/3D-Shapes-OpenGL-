#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<bits/stdc++.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace std;

class Shader {
    unsigned int ID;

    void shaderCompileLog(unsigned int shader, string type) const;

    void programCompileLog(unsigned int program) const;

    public:
    Shader(const char* vertexPath, const char * fragmentPath);
    
    void use();

    void setBool(const string &name, bool value) const;

    void setInt(const string &name, int value) const;

    void setFloat(const string &name, float value) const;

    void setMat4(const string &name, glm::mat4 value) const;

};

void Shader::shaderCompileLog(unsigned int shader, string type) const{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "ERROR::" << type << "::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << endl;
    }
}

void Shader::programCompileLog(unsigned int program) const{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" <<
        infoLog << endl;
    }
}
Shader::Shader(const char* vertexPath, const char * fragmentPath) {
    fstream vShaderFile;
    fstream fShaderFile;
    string vertexCode, fragmentCode;
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open("../source/shader.vs", ios::in);
        fShaderFile.open("../source/shader.fs", ios::in);
        
        stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch(ifstream::failure e) {
        cout << "Some ERROR occured\n";
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    shaderCompileLog(vertexShader, "SHADER");

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    shaderCompileLog(fragmentShader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    programCompileLog(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const string &name, glm::mat4 value) const {
    unsigned int transformLoc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}
#endif