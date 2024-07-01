#include "Game/Input.h"
#include <iostream>

std::vector<bool> Input::pressed_keys = std::vector<bool>(GLFW_KEY_MENU, false);

double Input::prev_mouse_x = 0.0;
double Input::prev_mouse_y = 0.0;
double Input::curr_mouse_x = 0.0;
double Input::curr_mouse_y = 0.0;

int Input::left_click = 0;
int Input::right_click = 0;

void Input::GetKeys(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UNKNOWN) {
        return;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { // TODO: exit gracefully (handle in Game or player)
        exit(1);
    }

    pressed_keys[key] = action;
}

void Input::GetMousePos(GLFWwindow* window, double x, double y) {
    curr_mouse_x = x;
    curr_mouse_y = y;
}

void Input::GetMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        left_click = action;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        right_click = action;
    }
}
