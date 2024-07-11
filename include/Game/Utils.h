#pragma once

#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <string>

namespace Utils {
// Window Constants:
const int RESOLUTION_X = 1920;
const int RESOLUTION_Y = 1080;

// Game Constants
const uint32_t CHUNK_SIZE = 16;
const uint32_t WORLD_HEIGHT = 32;

const uint32_t DEFAULT_RENDER_DISTANCE = 2;

const uint32_t TICKS_PER_SECOND = 20;
constexpr long long MILLIS_BETWEEN_TICKS = 1000 / TICKS_PER_SECOND;

typedef long long millis;
typedef long long micros;

enum BlockType {
    AIR = 0,
    GRASS,
    DIRT,
    STONE,
    BEDROCK,
    LOG,
    LEAF,
    WOOD_PLANK,
    SIZE
};

const int MAX_SUPPORTED_BLOCKTYPE = static_cast<int>(BlockType::BEDROCK + 1);

struct BlockTexture {
    const std::string top;
    const std::string side;
    const std::string bottom;
};

// Player Constants
const float PLAYER_INTERACT_RANGE = 6.0;

}

namespace math {

inline float normal(float x) {
    return (x > 0) - (x < 0);
}

}