#include "Game/Input.h"
#include "Game/Player.h"
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

const float start_x = 0.0f;
const float start_z = 32.0f;
const float start_y = 16.0f;


Player::Player() : 
    pos_xz(start_x,start_z),    pos_y(start_y), 
    vel_xz(0.0f),        vel_y(0.0f),
    accel_xz(0.0f),      accel_y(0.0f),
    view_theta(1.50f * glm::pi<float>()),           
    view_phi(0.0f),
    rotational_xz(0.0f) {
    std::cout << "Player: init" << std::endl;
}

Player::~Player() {

}

void Player::handleKeys() {
    float multiplier = 1.0;

    rotational_xz = glm::mat2();
    accel_y = 0.0f;

    for (size_t key = 0; key < GLFW_KEY_MENU; key++) {
        multiplier = Input::pressed[key] ? 1.0f : 0.0f;
        switch(key) {
            case GLFW_KEY_W:
                rotational_xz[0][0] += multiplier;
                rotational_xz[1][1] += multiplier;
                break;
            case GLFW_KEY_A:
                rotational_xz[0][1] += -multiplier;
                rotational_xz[1][0] +=  multiplier;
                break;
            case GLFW_KEY_S:
                rotational_xz[0][0] += -multiplier;
                rotational_xz[1][1] += -multiplier;
                break;
            case GLFW_KEY_D:
                rotational_xz[0][1] +=  multiplier;
                rotational_xz[1][0] += -multiplier;
                break;
            case GLFW_KEY_SPACE:
                accel_y += multiplier * VERT_ACCEL;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                accel_y += -multiplier * VERT_ACCEL;
                break;
            default:
                break;
        }
    }   
}

void Player::handleMouse() {
    double sensitivity = 2.0 * glm::pi<double>() / 1920 / 10;
    view_theta += sensitivity * (Input::curr_mouse_x - Input::prev_mouse_x);
    view_phi += -1.0 * sensitivity * (Input::curr_mouse_y - Input::prev_mouse_y);;
    Input::prev_mouse_x = Input::curr_mouse_x;
    Input::prev_mouse_y = Input::curr_mouse_y;
}

// void Player::handleMouse() {

// }

void Player::Update(std::chrono::high_resolution_clock::time_point current) {
    Utils::micros timeDelta = std::chrono::duration_cast<std::chrono::microseconds>(current - previousTimestamp_).count();
    previousTimestamp_ = current;
    handleKeys();
    handleMouse();
    // std::cout << "Time delta: " << timeDelta << std::endl;
    glm::vec2 forward(glm::cos(view_theta), glm::sin(view_theta));
    // std::cout << "("<< forward.x << "," << forward.y << ")" << std::endl;
    accel_xz = rotational_xz * forward;
    // std::cout << "("<< accel_xz.x << "," << accel_xz.y << ")" << std::endl;
    if (glm::length(accel_xz) > 0.0f) {
        accel_xz = glm::normalize(accel_xz) * HORIZ_ACCEL;
    } else { // dampening and come to a stop if no input
        accel_xz = -15.0f * vel_xz;
    }

    // std::cout << accel_y << std::endl;
    if (accel_y == 0.0f) {
        // std::cout << "Dampening vert" << std::endl;
        accel_y = -15.0f * vel_y;
    }

    // std::cout << "("<< accel_xz.x << "," << accel_xz.y << ")" << std::endl;
    vel_xz += (float) timeDelta / 1000000.0f * accel_xz;
    vel_y += (float) timeDelta / 1000000.0f * accel_y;

    if (glm::length(accel_xz) > 0.0) {
        vel_xz = vel_xz * std::min(glm::length(vel_xz), MAX_HORIZONTAL_SPEED) / glm::length(vel_xz);
    }
    if (vel_y != 0.0) {
        vel_y = vel_y * std::min(vel_y, MAX_HORIZONTAL_SPEED) / vel_y;
    }

    pos_xz += (float) timeDelta / 1000000.0f * vel_xz;
    pos_y += (float) timeDelta / 1000000.0f * vel_y;

    SetView();
    // std::cout << "Updated pos: (" << pos_xz.x << ", " << pos_y << ", " << pos_xz.y << ")" << std::endl; 
}

glm::mat4* Player::GetViewPtr() {
    return &viewMat_;
}

void Player::SetView() {
    viewMat_ = glm::lookAt( glm::vec3(pos_xz.x, pos_y, pos_xz.y), 
                            glm::vec3(pos_xz.x, pos_y, pos_xz.y) + 
                            glm::vec3(glm::cos(view_theta) * glm::cos(view_phi), glm::sin(view_phi), glm::sin(view_theta) * glm::cos(view_phi)), 
                            glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Player::view() {
    return viewMat_;
//     return glm::lookAt( glm::vec3(pos_xz.x, pos_y, pos_xz.y), 
//   		                glm::vec3(pos_xz.x, pos_y, pos_xz.y) + 
//                         glm::vec3(glm::cos(view_theta) * glm::cos(view_phi), glm::sin(view_phi), glm::sin(view_theta) * glm::cos(view_phi)), 
//   		                glm::vec3(0.0f, 1.0f, 0.0f));
// }
}