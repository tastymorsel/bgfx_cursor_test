#include "game.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

// Global game instance
static Game* g_game = nullptr;

// GLFW callbacks
void OnMouseMove(GLFWwindow* window, double x, double y) {
    if (g_game) {
        g_game->OnMouseMove(x, y);
    }
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods) {
    if (g_game) {
        g_game->OnMouseButton(button, action);
    }
}

void OnWindowResize(GLFWwindow* window, int width, int height) {
    // Handle window resize if needed
}

void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (g_game) {
            g_game->ResetGame();
        }
    }
}

int main() {
    try {
        // Initialize GLFW
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        
        // Configure GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        // Create window
        GLFWwindow* window = glfwCreateWindow(1024, 512, "Asteroids - Psychedelic Space", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        
        // Make context current
        glfwMakeContextCurrent(window);
        
        // Set callbacks
        glfwSetCursorPosCallback(window, OnMouseMove);
        glfwSetMouseButtonCallback(window, OnMouseButton);
        glfwSetFramebufferSizeCallback(window, OnWindowResize);
        glfwSetKeyCallback(window, OnKeyPress);
        
        // Create and initialize game
        g_game = new Game();
        if (!g_game->Initialize()) {
            delete g_game;
            glfwDestroyWindow(window);
            glfwTerminate();
            throw std::runtime_error("Failed to initialize game");
        }
        
        std::cout << "Game initialized successfully! Running for 5 seconds..." << std::endl;
        
        // Game loop - run for 5 seconds then exit
        auto startTime = std::chrono::high_resolution_clock::now();
        int frameCount = 0;
        
        while (!glfwWindowShouldClose(window)) {
            g_game->Run();
            glfwPollEvents();
            
            frameCount++;
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
            
            if (elapsed.count() >= 5) {
                std::cout << "Test completed! Ran " << frameCount << " frames in 5 seconds." << std::endl;
                break;
            }
        }
        
        // Cleanup
        g_game->Shutdown();
        delete g_game;
        glfwDestroyWindow(window);
        glfwTerminate();
        
        std::cout << "Game test completed successfully!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}