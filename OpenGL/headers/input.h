//
// Created by ulver on 7/15/2023.
//

#ifndef OPENGLRENDERER_INPUT_H
#define OPENGLRENDERER_INPUT_H

#include "../classes/Camera.h"

#endif //OPENGLRENDERER_INPUT_H

inline float deltaTime = 0.0f;
inline float lastFrame = 0.0f;

inline float lastX = 400, lastY = 300;
inline float fov = 90.0f;
inline bool firstMouse = true;
inline bool flashLightOn = true;

inline static glm::vec3 lightPos(-0.2f, -1.0f, -0.3f);

inline Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

inline void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
        lightPos.y = lightPos.y += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        lightPos.y = lightPos.y -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        lightPos.x = lightPos.x += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        lightPos.x = lightPos.x -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
        lightPos.z = lightPos.z += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
        lightPos.z = lightPos.z -= 0.01f;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        if (flashLightOn)
        {
            flashLightOn = false;
        }
        else if (!flashLightOn)
        {
            flashLightOn = true;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed = 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        camera.MovementSpeed = 2.5f;
    }
}

inline void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

inline void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}