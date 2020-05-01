//
//  shader.hpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//

#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
private:
    // the program ID
    unsigned int ID;

    void use_if(bool should_use);

public:
    // constructor reads and builds the shader
    Shader() = default;
    Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);

    // Delete Copy Operators
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&&) = default;
    Shader& operator=(Shader&&) = default;

    // use/activate the shader
    Shader& use();

    bool valid() const;
    unsigned int id() const;

    // utility uniform functions
    void setBool(const std::string &name, bool value, bool useShader);
    void setInt(const std::string &name, int value, bool useShader);
    void setFloat(const std::string &name, float value, bool useShader);
    void setVec2(const std::string &name, const glm::vec2& value, bool useShader);
    void setVec2(const std::string &name, float x, float y, bool useShader);
    void setVec3(const std::string &name, const glm::vec3& value, bool useShader);
    void setVec3(const std::string &name, float x, float y, float z, bool useShader);
    void setVec4(const std::string &name, const glm::vec4& value, bool useShader);
    void setVec4(const std::string &name, float x, float y, float z, float w, bool useShader);
    void setMat2(const std::string &name, const glm::mat2& mat, bool useShader);
    void setMat3(const std::string &name, const glm::mat3& mat, bool useShader);
    void setMat4(const std::string &name, const glm::mat4& mat, bool useShader);

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
};

