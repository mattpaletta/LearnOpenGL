//
//  resource.hpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//

#pragma once
#include <string>
#include <map>
#include <set>

#include "shader.hpp"
#include "texture.hpp"


#define ResourceManagerGetShader(name) \
    ResourceManager::GetShader(name, __FILE__, __LINE__)

class ResourceManager {
public:
    // resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, std::string> Sounds;

#if DEBUG
	static std::set<std::string> UnusedShaders;
	static std::set<std::string> UnusedTextures;
	static std::set<std::string> UnusedSounds;
#endif

	// loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader& LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& name);

    // retrieves a stored sader
    static Shader& GetShader(const std::string& name);
    static Shader& GetShader(const std::string& name, const std::string& file, const std::size_t& line);

    // loads (and generates) a texture from file
    static Texture2D& LoadTexture(const std::string& file, const bool alpha, const std::string& name);

    // retrieves a stored texture
    static Texture2D& GetTexture(const std::string& name);

	static std::string RegisterSound(const std::string& file, const std::string& name);
	static std::string& GetSound(const std::string& name);

    // properly de-allocates all loaded resources
    static void Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() = default;

    // loads and generates a shader from file
    static Shader loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile = "");

    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char* file, const bool alpha);
};
