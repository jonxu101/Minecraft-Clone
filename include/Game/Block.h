#pragma once

#include "Utils.h"
#include <glm/glm.hpp>

struct Block {
public:
    glm::vec3 pos;

    Utils::BlockType type;

public:
    Block();
    Block(float x, float y, float z, Utils::BlockType type);
    ~Block();
};