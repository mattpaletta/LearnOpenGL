//
//  shader.hpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//

#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	// the program ID
	unsigned int ID;
	
	void use_if(bool should_use) const;

    // constructor reads and builds the shader
    Shader() = default;

    // Delete Copy Operators
    Shader(const Shader&) = default;
    Shader& operator=(const Shader&) = default;

    Shader(Shader&&) = default;
    Shader& operator=(Shader&&) = default;

    // use/activate the shader
    Shader& use();
	Shader use() const;

	bool valid() const;
    unsigned int id() const;
	
	void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 

    // utility uniform functions
    void setBool(const std::string &name, const bool value, const bool useShader = false) const;
    void setInt(const std::string &name, const int value, const bool useShader = false) const;
    void setFloat(const std::string &name, const float value, const bool useShader = false) const;
    void setVec2(const std::string &name, const glm::vec2& value, const bool useShader = false) const;
    void setVec2(const std::string &name, const float x, const float y, const bool useShader = false) const;
    void setVec3(const std::string &name, const glm::vec3& value, const bool useShader = false) const;
    void setVec3(const std::string &name, const float x, const float y, const float z, const bool useShader = false) const;
    void setVec4(const std::string &name, const glm::vec4& value, const bool useShader = false) const;
    void setVec4(const std::string &name, const float x, const float y, const float z, const float w, const bool useShader = false) const;
    void setMat2(const std::string &name, const glm::mat2& mat, const bool useShader = false) const;
    void setMat3(const std::string &name, const glm::mat3& mat, const bool useShader = false) const;
    void setMat4(const std::string &name, const glm::mat4& mat, const bool useShader = false) const;
/*
    void set(const std::string &name, bool value, bool useShader);
    void set(const std::string &name, int value, bool useShader);
    void set(const std::string &name, float value, bool useShader);
    void set(const std::string &name, const glm::vec2& value, bool useShader);
    void set(const std::string &name, float x, float y, bool useShader);
    void set(const std::string &name, const glm::vec3& value, bool useShader);
    void set(const std::string &name, float x, float y, float z, bool useShader);
    void set(const std::string &name, const glm::vec4& value, bool useShader);
    void set(const std::string &name, float x, float y, float z, float w, bool useShader);
    void set(const std::string &name, const glm::mat2& mat, bool useShader);
    void set(const std::string &name, const glm::mat3& mat, bool useShader);
    void set(const std::string &name, const glm::mat4& mat, bool useShader);
*/
private:
	// checks if compilation or linking failed and if so, print the error logs
	void    checkCompileErrors(unsigned int object, std::string type);
};

