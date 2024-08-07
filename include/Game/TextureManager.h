#pragma once

#include "Utils.h"
#include "Graphics/Texture.h"

#include <string>
#include <unordered_map>
#include <vector>

struct GameTexture {
    int id; // used as index
    int colormap;

    int overlay_id; // used as index
    int overlay_colormap;
};

class TextureManager {
private:
    Texture* blockTextureArray_;
    std::vector<std::vector<int>> blockToTextureIndex_;
    
public:
    TextureManager(int& numBlockTextures);
    ~TextureManager();

    // int GetTextureID(tex

    int BindBlockTexture(Utils::BlockType type, uint16_t face);
    void Bind();
    void Unbind();
};