#include "Game/TextureManager.h"

#define GLEW_STATIC
#include "GL/glew.h"

#include <vendor/stb_image.h>
#include <vendor/stb_image_write.h>

#include <map>
#include <unordered_set>

struct BlockTexture {
    std::string topTexture;
    std::string bottomTexture;
    std::string posXTexture;
    std::string negXTexture;
    std::string posZTexture;
    std::string negZTexture;
};

const std::map<Utils::BlockType, std::vector<std::string>> textureConfig
{
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
#include <cstring>

std::string buildTextureArray(const std::vector<std::string>& paths) { // TODO: make the texture dimensions powers of two
    const int TEXTURE_WIDTH = 16;
    const int TEXTURE_HEIGHT = 16;
    const int TEXTURE_BYTES = TEXTURE_WIDTH * TEXTURE_HEIGHT * 4;
    const std::string OUTPUT_PATH = "../resources/textures/out/textures.png";

    std::vector<unsigned char> buffer(paths.size() * paths.size() * TEXTURE_BYTES);
    
    unsigned char* localBuffer;
    int width, height, bpp;

    
    for (int i = 0; i < paths.size(); i++) {
        localBuffer = stbi_load(paths[i].c_str(), &width, &height, &bpp, 4);
        memcpy(&buffer[i * TEXTURE_BYTES], localBuffer, TEXTURE_BYTES);
        stbi_image_free(localBuffer);
    }

    stbi_write_png(OUTPUT_PATH.c_str(), TEXTURE_WIDTH, TEXTURE_HEIGHT * paths.size(), 4, buffer.data(), TEXTURE_WIDTH * 4);
    return OUTPUT_PATH;
}

TextureManager::TextureManager() :
    blockToTextureIndex_(Utils::BlockType::SIZE, std::vector<int>(6, -1))
{
    std::cout << "TextureManager: Constructing" << std::endl;
    int numTextures = 0;
    std::vector<std::string> texturePaths;

    std::unordered_map<std::string, int> pathToId;

    for (const auto& texture: textureConfig) {
        if (texture.first == Utils::BlockType::AIR) {
            continue;
        }
        int face = 0;
        for (const auto& path: texture.second) {
            if (pathToId.find(path) == pathToId.end()) {
                pathToId.emplace(path, numTextures);
                std::cout << "TextureManager Init: found " << path << std::endl;
                texturePaths.push_back("../resources/textures/"+path);
                numTextures++;
            }
            blockToTextureIndex_[texture.first][face] = pathToId[path];
            face++;
        }
    }

    blockTextureArray_ = Texture(buildTextureArray(texturePaths), 10);
    Bind();
}

TextureManager::~TextureManager() {

}

void TextureManager::AddAvailable(const std::string path) {

}

int TextureManager::BindBlockTexture(Utils::BlockType type, uint16_t face) {
    return 0;
}

void TextureManager::Bind() {
    blockTextureArray_.Bind();
}

void TextureManager::Unbind() {
    blockTextureArray_.Unbind();
}