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
    std::vector<Texture*> AvailableTextures_;
    std::vector<GameTexture> GameTextures_;

    int cachePtr_;
    int cacheSize_;
    std::vector<Texture*> CachedTextures_;
    std::unordered_map<int, int> idToIndex_;
    
public:
    TextureManager();
    ~TextureManager();

    void AddAvailable(const std::string path);
    int BindBlockTexture(Utils::BlockType type, uint16_t face);
};