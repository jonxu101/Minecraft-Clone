#include "Game/TextureManager.h"

#define GLEW_STATIC
#include "GL/glew.h"

#include <map>

struct BlockTexture {
    std::string topTexture;
    std::string bottomTexture;
    std::string posXTexture;
    std::string negXTexture;
    std::string posZTexture;
    std::string negZTexture;
};

std::map<Utils::BlockType, std::vector<std::string>> textureInit{
    {Utils::BlockType::AIR,         {   "",
                                        "",
                                        "",
                                        "",
                                        "",
                                        ""}},
    {Utils::BlockType::GRASS,       {   "grass_block_top.png",
                                        "dirt.png",
                                        "dirt.png",
                                        "dirt.png",
                                        "dirt.png",
                                        "dirt.png"}},
    {Utils::BlockType::DIRT,       {    "dirt.png",
                                        "dirt.png",
                                        "dirt.png",
                                        "dirt.png",
                                        "dirt.png",
                                        "dirt.png"}},                                    
    {Utils::BlockType::STONE,       {   "stone.png",
                                        "stone.png",
                                        "stone.png",
                                        "stone.png",
                                        "stone.png",
                                        "stone.png"}}                            
};

#include <iostream>

TextureManager::TextureManager() :
    cachePtr_(0)
    // AvailableTextures_(1000)
    // GameTextures_()
{
    std::cout << "TextureManager: Init" << std::endl;
    std::unordered_map<std::string, int> pathToId;
    for (const auto& texture: textureInit) {
        if (texture.first == Utils::BlockType::AIR) {
            for (int i = 0; i < 6; i++) {
                GameTextures_.push_back({-1, -1, -1, -1});
            }
            continue;
        }
        for (const auto& path: texture.second) {
            if (pathToId.count(path) == 0) {
                // pathToId[path] = aI;
                pathToId[path] = AvailableTextures_.size();
                // AvailableTextures_[aI++] = Texture("../resources/textures/" + path, pathToId[path]);
                AvailableTextures_.push_back(new Texture("../resources/textures/" + path, pathToId[path]));
                // std::cout << "Texture pointer: " << &AvailableTextures_ << std::endl;
            }
            GameTextures_.push_back({pathToId[path], -1, -1, -1});
        }
    }
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &cacheSize_);
    CachedTextures_ = std::vector<Texture*>(cacheSize_, nullptr);
    std::cout << "Maximum number of textures: " << cacheSize_ << std::endl;
    std::cout << "TextureManager: gotten avilable: " << AvailableTextures_.size() << std::endl;
    std::cout << "TextureManager: game textures size: " << GameTextures_.size() << std::endl;
}

TextureManager::~TextureManager() {

}

void TextureManager::AddAvailable(const std::string path) {

}

int TextureManager::BindBlockTexture(Utils::BlockType type, uint16_t face) {
    int id = type * 6 + face;
    int availableTextureId = GameTextures_[id].id;
    auto itr = idToIndex_.find(availableTextureId);
    if (itr == idToIndex_.end()) {
        std::cout << "TextureManager: Cache miss" << std::endl;
        if (CachedTextures_[cachePtr_]) {
            idToIndex_.erase(CachedTextures_[cachePtr_]->GetID());
        }
        // std::cout << "erased" << std::endl;
        idToIndex_.emplace(availableTextureId, cachePtr_);
        Texture* texture = AvailableTextures_[availableTextureId];
        CachedTextures_[cachePtr_] = texture;
        texture->Bind(cachePtr_);
        int ret = cachePtr_;
        cachePtr_++; cachePtr_ %= cacheSize_;
        return ret;
    }
    return itr->second;
}