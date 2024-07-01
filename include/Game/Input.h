#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

// #include "Player.h"

struct Input {
    // Mouse Position variables
    static double prev_mouse_x;
    static double prev_mouse_y;
    static double curr_mouse_x;
    static double curr_mouse_y;
    
    // Mouse clicks
    static int left_click;
    static int right_click;

    // Key pressed
    static std::vector<bool> pressed_keys;

    
    static void GetKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GetMousePos(GLFWwindow* window, double xpos, double ypos);
    static void GetMouseClick(GLFWwindow* window, int button, int action, int mods);
};