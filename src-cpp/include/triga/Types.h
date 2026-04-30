#pragma once

// ============================================================
// TRIGA ENGINE — Core Types & Definitions
// ============================================================

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <functional>
#include <array>
#include <optional>

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
    #define TRIGA_PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define TRIGA_PLATFORM_MACOS
#elif defined(__linux__)
    #define TRIGA_PLATFORM_LINUX
#endif

// Build configuration
#if defined(DEBUG) || defined(_DEBUG)
    #define TRIGA_DEBUG
#else
    #define TRIGA_RELEASE
#endif

// API export macros
#if defined(TRIGA_PLATFORM_WINDOWS)
    #ifdef TRIGA_EXPORTS
        #define TRIGA_API __declspec(dllexport)
    #else
        #define TRIGA_API __declspec(dllimport)
    #endif
#else
    #define TRIGA_API
#endif

// Forward declarations
namespace triga {
    class Entity;
    class Scene;
    class Renderer;
    class PhysicsWorld;
}

// Version info
#define TRIGA_VERSION_MAJOR 2
#define TRIGA_VERSION_MINOR 0
#define TRIGA_VERSION_PATCH 0

namespace triga {

// ============================================================
// Result & Optional Types
// ============================================================

template<typename T>
using Result = std::optional<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T>
using Scope = std::unique_ptr<T>;

// Function result
struct ResultStatus {
    bool success;
    std::string message;
    
    ResultStatus() : success(false) {}
    ResultStatus(bool s, const std::string& msg = "") : success(s), message(msg) {}
    
    static ResultStatus OK() { return ResultStatus(true); }
    static ResultStatus Error(const std::string& msg) { return ResultStatus(false, msg); }
};

} // namespace triga

