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
#include <filesystem>

#include "stb_image/stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

#if DEBUG
std::set<std::string>    ResourceManager::UnusedTextures;
std::set<std::string>    ResourceManager::UnusedShaders;
#endif

Shader& ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& name) {
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
#if DEBUG
	UnusedShaders.insert(name);
#endif
    return ResourceManager::GetShader(name);
}

Shader& ResourceManager::GetShader(const std::string& name) {
#if DEBUG
	if (Shaders.find(name) == Shaders.end()) {
		std::cout << "Failed to get shader: " << name << std::endl;
	}
	UnusedShaders.erase(name);
#endif
    return Shaders[name];
}

Shader& ResourceManager::GetShader(const std::string& name, const std::string& file, const std::size_t& line) {
#if DEBUG
	if (Shaders.find(name) == Shaders.end()) {
        std::cout << "Failed to get shader: " << name << " at: [" << file << ":" << line << "]" << std::endl;
    }

	UnusedShaders.erase(name);
#endif

	return Shaders[name];
}

Texture2D& ResourceManager::LoadTexture(const std::string& file, const bool alpha, const std::string& name) {
    Textures.emplace(name, loadTextureFromFile(file.c_str(), alpha));
#if DEBUG
	UnusedTextures.insert(name);
#endif
    return ResourceManager::GetTexture(name);
}

Texture2D& ResourceManager::GetTexture(const std::string& name) {
	if (Textures.find(name) == Textures.end()) {
		std::cout << "Failed to get texture: " << name << std::endl;
	}
#if DEBUG
	UnusedTextures.erase(name);
#endif
    return Textures[name];
}

void ResourceManager::Clear() {
    // (properly) delete all shaders
    for (const auto& iter : Shaders) {
#if DEBUG
		if (UnusedShaders.find(iter.first) != UnusedShaders.end()) {
			std::cout << "Warning: shader loaded but never used: " << iter.first << std::endl;
		}
#endif
		glDeleteProgram(iter.second.id());
    }

    // (properly) delete all textures
    for (const auto& iter : Textures) {
#if DEBUG
		if (UnusedTextures.find(iter.first) != UnusedTextures.end()) {
			std::cout << "Warning: texture loaded but never used: " << iter.first << std::endl;
		}
#endif
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
		std::terminate();
    }

    try {
        fragmentCode = readFile(fShaderFile);
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::FRAGMENT_SHADER::FILE_NOT_SUCCESFULLY_READ: " << fShaderFile << std::endl;
		std::terminate();
    }

//    try {
//        geometryCode = readFile(gShaderFile);
//    } catch(std::ifstream::failure e) {
//        std::cout << "ERROR::GEOMETRY_SHADER::FILE_NOT_SUCCESFULLY_READ: " << gShaderFile << std::endl;
//    }

    // 2. now create shader object from source code
#if DEBUG
	assert(vertexCode != "");
	assert(fragmentCode != "");
#endif

	Shader shader;
	shader.Compile(
		vertexCode.c_str(), 
		fragmentCode.c_str(), 
		geometryCode == "" ? nullptr : geometryCode.c_str());
    return shader;
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
    f.close();
#endif

//    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, STBI_default);

    // now generate texture
    texture.Generate(width, height, data);

    // and finally free image data
    stbi_image_free(data);
    return texture;
}
