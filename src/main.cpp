#include "Game/Game.h"

int main(void) {
    std::cout << "BEGINNING GAME: " << std::endl;

    std::cout << "Running game!" << std::endl;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(640, 480, "Craftmine", NULL, NULL);

    /* Create a windowed mode window and its OpenGL context */
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl; 
        return -1;
    }

    glClearColor(1.0,1.0,1.0,1.0);
    std::cout << "Using GL version: " << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ChunkRenderer::Init();
    ChunkIndexBuffer::Init();
    
    Game game = Game();
    return game.Run(window);
}