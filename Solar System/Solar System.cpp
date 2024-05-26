#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <SOIL2/SOIL2.h>

#include "Shader.h"
#include "Planet.h"
#include "Camera.h"
#include "Light.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Kamera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

// Callbacki
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);



int main() {
    // Inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Solar System", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader planetShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Shader sunShader("shaders/sun_vertex_shader.glsl", "shaders/sun_fragment_shader.glsl");

    float rotateSpeed = 0.01f;

    // Dodaj planety
    Planet sun("textures/sun.png", 3.0f, 0.0f, 0.0f);                         // Słońce
    Planet mercury("textures/mercury.png", 0.3f, 5.0f, 48.0f * rotateSpeed);  // Merkury
    Planet venus("textures/venus.png", 0.35f, 8.0f, 35.0f * rotateSpeed);     // Wenus
    Planet earth("textures/earth.png", 0.4f, 11.0f, 29.0f * rotateSpeed);     // Ziemia
    Planet mars("textures/mars.png", 0.35f, 14.0f, 24.0f * rotateSpeed);      // Mars
    Planet jupiter("textures/jupiter.png", 0.9f, 18.0f, 13.0f * rotateSpeed); // Jowisz
    Planet saturn("textures/saturn.png", 0.8f, 22.0f, 10.0f * rotateSpeed, true);   // Saturn
    Planet uranus("textures/uranus.png", 0.7f, 26.0f, 7.0f * rotateSpeed);    // Uran
    Planet neptune("textures/neptune.png", 0.7f, 30.0f, 5.0f * rotateSpeed);  // Neptun

    Light sunLight(
        glm::vec3(0.0f, 0.0f, 0.0f),  // Pozycja słońca
        glm::vec3(0.7f, 0.7f, 0.7f),  // Ambient 
        glm::vec3(0.9f, 0.9f, 0.9f),  // Diffuse 
        glm::vec3(1.0f, 1.0f, 1.0f)   // Specular 
    );

    sunLight.apply(planetShader);
    sunLight.apply(sunShader);


    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    planetShader.use();
    planetShader.setMat4("view", view);
    planetShader.setMat4("projection", projection);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Pętla główna programu
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Ustawienie macierzy widoku i projekcji
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        // Przekazanie macierzy widoku i projekcji do shaderów
        planetShader.use();
        planetShader.setMat4("view", view);
        planetShader.setMat4("projection", projection);
        sunShader.use();
        sunShader.setMat4("view", view);
        sunShader.setMat4("projection", projection);

        // Renderowanie słońca
        sunShader.use();
        sun.draw(sunShader);

        // Renderowanie planet
        planetShader.use();
        mercury.draw(planetShader);
        venus.draw(planetShader);
        earth.draw(planetShader);
        mars.draw(planetShader);
        jupiter.draw(planetShader);
        saturn.draw(planetShader);
        uranus.draw(planetShader);
        neptune.draw(planetShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

