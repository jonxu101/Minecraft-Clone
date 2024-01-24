#include "Game/Input.h"
#include <iostream>

std::vector<bool> Input::pressed = std::vector<bool>(GLFW_KEY_MENU, false);
double Input::prev_mouse_x = 0.0;
double Input::prev_mouse_y = 0.0;
double Input::curr_mouse_x = 0.0;
double Input::curr_mouse_y = 0.0;

// Input::Input(Player* player) : player_(player) {}

// Input::~Input() {}

void Input::getKeys(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UNKNOWN) {
        return;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { // TODO: exit gracefully (handle in Game or player)
        exit(1);
    }

    if (action == GLFW_PRESS) {
        pressed[key] = true;
    } else if (action == GLFW_RELEASE) {
        pressed[key] = false;
    }
}

void Input::getMouse(GLFWwindow* window, double x, double y) {
    curr_mouse_x = x;
    curr_mouse_y = y;
}