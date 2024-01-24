#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

// #include "Player.h"

struct Input {
    static double prev_mouse_x;
    static double prev_mouse_y;
    static double curr_mouse_x;
    static double curr_mouse_y;
    
    static std::vector<bool> pressed;
    static void getKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void getMouse(GLFWwindow* window, double xpos, double ypos);
};