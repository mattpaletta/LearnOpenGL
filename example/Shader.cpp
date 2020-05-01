//
//  Shader.cpp
//  create_window
//
//  Created by Matthew Paletta on 2020-04-27.
//

#include "Shader.hpp"

#include "glad/glad.h" // include glad to get all the required OpenGL headers


#include <fstream>
#include <sstream>
#include <iostream>

namespace {
    unsigned int CompileShader(const std::string& shaderSource, const GLuint& shaderType) {
        unsigned int shader;
        const auto raw_str = shaderSource.c_str();
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &raw_str, NULL);
        glCompileShader(shader);
        return shader;
    }

    bool VerifyShader(unsigned int shader, const std::string& step) {
        int  success;
        constexpr std::size_t info_msg_length = 512;
        char infoLog[info_msg_length];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, info_msg_length, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << step << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return success;
    }

    unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
        unsigned int vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
        if (!VerifyShader(vertexShader, "VERTEX")) {
            std::cout << "Failed to compile vertex shader" << std::endl;
        }
        unsigned int fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
        if (!VerifyShader(fragmentShader, "FRAGMENT")) {
            // Free Memory
            std::cout << "Failed to compiile fragment shader" << std::endl;
            glDeleteShader(vertexShader);
        }

        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return shaderProgram;
    }

    bool VerifyShaderProgram(unsigned int shaderProgram) {
        //    glUseProgram(shaderProgram);

        int  success;
        constexpr std::size_t info_msg_length = 512;

        char infoLog[info_msg_length];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, info_msg_length, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        }

        return success;
    }
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    this->ID = CreateShaderProgram(vertexCode, fragmentCode);
}

unsigned int Shader::get_id() const {
    return this->ID;
}

bool Shader::valid() {
    return VerifyShaderProgram(this->ID);
}

void Shader::use() {
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set(const std::string &name, bool value) const {
    this->setBool(name, value);
}

void Shader::set(const std::string &name, int value) const {
    this->setInt(name, value);
}

void Shader::set(const std::string &name, float value) const {
    this->setFloat(name, value);
}

void Shader::set(const std::string &name, const glm::vec2& value) const {
    this->setVec2(name, value);
}

void Shader::set(const std::string &name, float x, float y) const {
    this->setVec2(name, x, y);
}

void Shader::set(const std::string &name, const glm::vec3& value) const {
    this->setVec3(name, value);
}

void Shader::set(const std::string &name, float x, float y, float z) const {
    this->setVec3(name, x, y, z);
}

void Shader::set(const std::string &name, const glm::vec4& value) const {
    this->setVec4(name, value);
}

void Shader::set(const std::string &name, float x, float y, float z, float w) const {
    this->setVec4(name, x, y, z, w);
}

void Shader::set(const std::string &name, const glm::mat2& mat) const {
    this->setMat2(name, mat);
}

void Shader::set(const std::string &name, const glm::mat3& mat) const {
    this->setMat3(name, mat);
}

void Shader::set(const std::string &name, const glm::mat4& mat) const {
    this->setMat4(name, mat);
}
