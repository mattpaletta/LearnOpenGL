//
//  resource.cpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//

#include "engine/resource.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

#include "stb_image/stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader& ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& name) {
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader& ResourceManager::GetShader(const std::string& name) {
    return Shaders[name];
}

Shader& ResourceManager::GetShader(const std::string& name, const std::string& file, const std::size_t& line) {
    if (Shaders.find(name) == Shaders.end()) {
#if DEBUG
        std::cout << "Failed to get shader: " << name << " at: [" << file << ":" << line << "]" << std::endl;
#endif
    }
    return Shaders[name];
}

Texture2D& ResourceManager::LoadTexture(const std::string& file, const bool alpha, const std::string& name) {
    Textures[name] = std::move(loadTextureFromFile(file.c_str(), alpha));
    return Textures[name];
}

Texture2D& ResourceManager::GetTexture(const std::string& name) {
    return Textures[name];
}

void ResourceManager::Clear() {
    // (properly) delete all shaders
    for (const auto& iter : Shaders) {
        glDeleteProgram(iter.second.id());
    }

    // (properly) delete all textures
    for (const auto& iter : Textures) {
        glDeleteTextures(1, &iter.second.ID);
    }
}


std::string readFile(const std::string& filePath) {
    std::ifstream vFile;
    vFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    std::string fileContents;
    vFile.open(filePath);
    std::stringstream vFileStream;
    vFileStream << vFile.rdbuf();
    vFile.close();

    fileContents = vFileStream.str();

    return fileContents;
}

Shader ResourceManager::loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try {
        vertexCode = readFile(vShaderFile);
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::VERTEX_SHADER::FILE_NOT_SUCCESFULLY_READ: " << vShaderFile << std::endl;
    }

    try {
        fragmentCode = readFile(fShaderFile);
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::FRAGMENT_SHADER::FILE_NOT_SUCCESFULLY_READ: " << fShaderFile << std::endl;
    }

//    try {
//        geometryCode = readFile(gShaderFile);
//    } catch(std::ifstream::failure e) {
//        std::cout << "ERROR::GEOMETRY_SHADER::FILE_NOT_SUCCESFULLY_READ: " << gShaderFile << std::endl;
//    }

    // 2. now create shader object from source code
    return {vertexCode, fragmentCode, geometryCode};
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, const bool alpha) {
    // create texture object
    Texture2D texture;
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
#if DEBUG
    std::ifstream f(file);
    if (!f.good()) {
        std::cout << "Failed to open file: " << file << std::endl;
    }
#endif
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
#if DEBUG
    if (strlen(reinterpret_cast<char*>(data)) == 0) {
        std::cout << "Tried to read file: " << file << " got empty data" << std::endl;
    }
#endif
    // now generate texture
    texture.Generate(width, height, data);

    // and finally free image data
    stbi_image_free(data);
    return texture;
}
