#include "Utils.h"

class Entity {
private:
    const uint16_t HEIGHT = 2;
    const uint16_t WIDTH_X = 1;
    const uint16_t WIDTH_Y = 1;

    float velocity = 0.0;

    float pos_x;
    float pos_y;
    float pos_z;

    Entity();
    ~Entity();

    void move();

};