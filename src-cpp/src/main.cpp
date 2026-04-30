#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main() {
    try {
        // Initialize logging
        auto console = spdlog::stdout_color_mt("console");
        console->info("TRIGA Engine v1.0.0 - Starting...");
        
        // Initialize GLFW
        if (!glfwInit()) {
            console->error("Failed to initialize GLFW");
            return -1;
        }
        
        console->info("GLFW initialized successfully");
        console->info("Build system: TRIGA Engine Editor");
        console->info("Platform: Windows 64-bit");
        console->info("C++ Standard: C++20");
        
        // Cleanup
        glfwTerminate();
        console->info("TRIGA Engine shut down successfully");
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
}

