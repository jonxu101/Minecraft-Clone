#pragma once

#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <string>

namespace Utils {

const uint16_t CHUNK_SIZE = 1;
const uint16_t WORLD_HEIGHT = 32;

const uint16_t DEFAULT_RENDER_DISTANCE = 8;

const uint16_t TICKS_PER_SECOND = 20;

typedef long long millis;
typedef long long micros;

enum BlockType {
    AIR = 0,
    GRASS,
    DIRT,
    STONE,
    LOG,
    LEAF,
    WOOD_PLANK,
    SIZE
};

struct BlockTexture {
    const std::string top;
    const std::string side;
    const std::string bottom;
};

const std::vector<BlockTexture> BlockToTexture {
    {"grass_block_top.png", "dirt.png"},

    {"dirt.png", "dirt.png", "dirt.png"},
    
};

}
