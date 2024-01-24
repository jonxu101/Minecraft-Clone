#pragma once

#include <glm/glm.hpp>

#include <string>

class Texture {
private:
    unsigned int rendererId_;
    std::string filePath_;
    unsigned char* localBuffer_;
    int width_, height_, BPP_;

    int id_;

public:
    Texture();
    Texture(const std::string& path, int id);

    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return width_; }
    inline int GetHeight() const { return height_; }
    inline int GetID() const { return id_; }
    inline std::string GetPath() {return filePath_;}
};

class ColorMap {
private:
    std::string filePath_;
    unsigned char* localBuffer_;
    int width_, height_, BPP_;

public:
    ColorMap(const std::string& path);
    ~ColorMap();

    glm::mat4 getPixelMat(float x, float y) const ;
};