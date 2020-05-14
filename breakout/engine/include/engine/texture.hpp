//
//  texture.hpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//
#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D {
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int ID;

    // texture image dimensions
    unsigned int Width, Height; // width and height of loaded image in pixels

    // texture Format
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image

    // texture configuration
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels

    // constructor (sets default texture modes)
    Texture2D();

//    Texture2D(const Texture2D&) = delete;
//    Texture2D& operator=(const Texture2D&) = delete;

    // generates texture from image data
    void Generate(const std::size_t& width, const std::size_t& height, const unsigned char* data);

    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};
