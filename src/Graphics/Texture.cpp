#define GLEW_STATIC
#include <GL/glew.h>

#include "Graphics/Texture.h"

#include <vendor/stb_image.h>
#include <iostream>

Texture::Texture() : id_(-1) {}

Texture::Texture(const std::string& path, int id) 
    : filePath_(path), localBuffer_(nullptr),
    width_(0), height_(0), BPP_(0),
    rendererId_(0),
    id_(id) {
    
    stbi_set_flip_vertically_on_load(1);
    localBuffer_ = stbi_load(path.c_str(), &width_, &height_, &BPP_, 4);
    std::cout << "Gotten image " << path << ": " << width_ << ", " << height_ << std::endl; 

    glGenTextures(1, &rendererId_);
    glBindTexture(GL_TEXTURE_2D, rendererId_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer_);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (localBuffer_) {
        stbi_image_free(localBuffer_);
    }
}

void updatePixel(unsigned char* under, unsigned char* over, int width, int coord_x, int coord_y) {
    unsigned char a = over[4 * (coord_y * width + coord_x) + 3];
    if (a != 0) {
        under[4 * (coord_y * width + coord_x) + 0] = over[4 * (coord_y * width + coord_x) + 0];
        under[4 * (coord_y * width + coord_x) + 1] = over[4 * (coord_y * width + coord_x) + 1];
        under[4 * (coord_y * width + coord_x) + 2] = over[4 * (coord_y * width + coord_x) + 2];
        under[4 * (coord_y * width + coord_x) + 3] = over[4 * (coord_y * width + coord_x) + 3];
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &rendererId_);
}

void Texture::Bind(unsigned int slot /*= 0*/) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, rendererId_);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

ColorMap::ColorMap(const std::string& path) 
    : filePath_(path), localBuffer_(nullptr),
    width_(0), height_(0), BPP_(0) {
    
    stbi_set_flip_vertically_on_load(1);
    localBuffer_ = stbi_load(path.c_str(), &width_, &height_, &BPP_, 4);
    std::cout << "Gotten colormap " << path << ": " << width_ << ", " << height_ << std::endl; 
}

ColorMap::~ColorMap() {}

glm::mat4 ColorMap::getPixelMat(float x, float y) const {
    int coord_x = (int) ((float)width_ * x);
    int coord_y = (int) ((float)height_ * y) + 1;
    unsigned char r = localBuffer_[4 * (coord_y * width_ + coord_x) + 0];
    unsigned char g = localBuffer_[4 * (coord_y * width_ + coord_x) + 1];
    unsigned char b = localBuffer_[4 * (coord_y * width_ + coord_x) + 2];
    unsigned char a = localBuffer_[4 * (coord_y * width_ + coord_x) + 3];
    // std::cout << "Got color pixael: " << (int)r << "," << (int) g << "," << (int) b << "," << (int) a <<std::endl;
    return glm::mat4 {  r / 256.0, 0.0, 0.0, 0.0,
                        0.0, g / 256.0, 0.0, 0.0,
                        0.0, 0.0, b / 256.0, 0.0,
                        0.0, 0.0, 0.0, a / 256.0};
}