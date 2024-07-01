#include "Game/Block.h"

Block::Block() : 
    pos(0.0), 
    type(Utils::BlockType::AIR) 
{

}

Block::Block(float x, float y, float z, Utils::BlockType t) : 
    pos(x,y,z), 
    type(t) 
{

}

Block::~Block() {}