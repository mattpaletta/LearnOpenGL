//
//  shader.cpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//

#include "engine/shader.hpp"

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

        unsigned int shaderProgram = glCreateProgram();
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

void Shader::use_if(const bool should_use) const {
    if (should_use) {
        this->use();
    }
}

unsigned int Shader::id() const {
    return this->ID;
}

bool Shader::valid() const {
    return VerifyShaderProgram(this->ID);
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	unsigned int sVertex, sFragment, gShader;
	// vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	// if geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}
	// shader program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	if (geometrySource != nullptr) {
		glAttachShader(this->ID, gShader);
	}
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr) {
		glDeleteShader(gShader);
	}
}

Shader& Shader::use() {
#if DEBUG
    if (this->ID == 0) {
        std::cout << "Warning: Shader ID 0" << std::endl;
    }
#endif

    glUseProgram(this->ID);
    return *this;
}

Shader Shader::use() const {
#if DEBUG
	if (this->ID == 0) {
		std::cout << "Warning: Shader ID 0" << std::endl;
	}
#endif

	glUseProgram(this->ID);
	return Shader(*this);
}

void Shader::setBool(const std::string& name, const bool value, const bool useShader) const {
    this->use_if(useShader);
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, const int value, const bool useShader) const {
    this->use_if(useShader);
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float value, const bool useShader) const {
    this->use_if(useShader);
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value, const bool useShader) const {
    this->use_if(useShader);
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, const float x, const float y, const bool useShader) const {
    this->use_if(useShader);
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value, const bool useShader) const {
    this->use_if(useShader);
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, const float x, const float y, const float z, const bool useShader) const {
    this->use_if(useShader);
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value, const bool useShader) const {
    this->use_if(useShader);
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, const float x, const float y, const float z, const float w, const bool useShader) const {
    this->use_if(useShader);
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat, const bool useShader) const {
    this->use_if(useShader);
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat, const bool useShader) const {
    this->use_if(useShader);
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat, const bool useShader) const {
    this->use_if(useShader);
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
/*
void Shader::set(const std::string &name, const bool value, const bool useShader) const {
    this->setBool(name, value, useShader);
}

void Shader::set(const std::string &name, int value, bool useShader) {
    this->setInt(name, value, useShader);
}

void Shader::set(const std::string &name, float value, bool useShader) {
    this->setFloat(name, value, useShader);
}

void Shader::set(const std::string &name, const glm::vec2& value, bool useShader) {
    this->setVec2(name, value, useShader);
}

void Shader::set(const std::string &name, float x, float y, bool useShader) {
    this->setVec2(name, x, y, useShader);
}

void Shader::set(const std::string &name, const glm::vec3& value, bool useShader) {
    this->setVec3(name, value, useShader);
}

void Shader::set(const std::string &name, float x, float y, float z, bool useShader) {
    this->setVec3(name, x, y, z, useShader);
}

void Shader::set(const std::string &name, const glm::vec4& value, bool useShader) {
    this->setVec4(name, value, useShader);
}

void Shader::set(const std::string &name, float x, float y, float z, float w, bool useShader) {
    this->setVec4(name, x, y, z, w, useShader);
}

void Shader::set(const std::string &name, const glm::mat2& mat, bool useShader) {
    this->setMat2(name, mat, useShader);
}

void Shader::set(const std::string &name, const glm::mat3& mat, bool useShader) {
    this->setMat3(name, mat, useShader);
}

void Shader::set(const std::string &name, const glm::mat4& mat, bool useShader) {
    this->setMat4(name, mat, useShader);
}
*/

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}