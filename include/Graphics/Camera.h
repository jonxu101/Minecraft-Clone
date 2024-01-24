#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;
    glm::vec3 up;

public:
    Camera() {
        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    glm::mat4 lookAt() {
        return glm::lookAt(cameraPos, cameraTarget, up);
    }
};

