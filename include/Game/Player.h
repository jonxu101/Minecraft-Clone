#pragma once

#include "Utils.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <chrono>

class Player {
private:
    const uint16_t HEIGHT = 2;
    const uint16_t WIDTH_X = 1;
    const uint16_t WIDTH_Y = 1;

    const float MAX_HORIZONTAL_SPEED = 20.0;
    const float MAX_VERTICAL_SPEED = 20.0;

    const float HORIZ_ACCEL = 100.0;
    const float VERT_ACCEL = 100.0;

    std::chrono::high_resolution_clock::time_point previousTimestamp_;

    glm::vec2 pos_xz;
    float pos_y;
    
    glm::vec2 vel_xz;
    float vel_y;

    glm::vec2 accel_xz;
    float accel_y;

    float view_theta, view_phi;

    // glm::vec3 lookAt;
    glm::vec3 up;
    glm::vec3 forward;
    glm::vec2 forward_xz;
    glm::mat2 rotational_xz;

    glm::mat4 viewMat_;

public:
    Player();
    ~Player();

    void handleKeys();
    void handleMouse();

    void Update(std::chrono::high_resolution_clock::time_point current);
    
    glm::mat4* GetViewPtr();
    void SetView();
    glm::mat4 view();
};