#define STB_IMAGE_IMPLEMENTATION
#include "triga/render/Texture.h"
#include "triga/core/Logger.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#endif

namespace triga {

Texture::Texture() : m_id(0), m_width(0), m_height(0), m_format(TextureFormat::RGBA), m_loaded(false) {
    glGenTextures(1, &m_id);
}

Texture::~Texture() {
    if (m_id) {
        glDeleteTextures(1, &m_id);
    }
}

bool Texture::loadFromFile(const std::string& filepath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbiLoad(filepath.c_str(), &width, &height, &channels, 4);
    
    if (!data) {
        TRIGA_LOG_ERROR("Failed to load texture: {}", filepath);
        return false;
    }

    m_width = width;
    m_height = height;
    m_format = TextureFormat::RGBA;

    glBindTexture(GL_TEXTURE_2D, m_id);
    
    GLenum format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbiFree(data);
    
    m_loaded = true;
    TRIGA_LOG_INFO("Loaded texture: {} ({}x{})", filepath, width, height);
    return true;
}

bool Texture::create(int width, int height, TextureFormat format, const void* data) {
    m_width = width;
    m_height = height;
    m_format = format;

    glBindTexture(GL_TEXTURE_2D, m_id);

    GLenum internalFormat, format;
    switch (format) {
        case TextureFormat::RGBA:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            break;
        case TextureFormat::RGB:
            internalFormat = GL_RGB;
            format = GL_RGB;
            break;
        case TextureFormat::Alpha:
            internalFormat = GL_RED;
            format = GL_RED;
            break;
        case TextureFormat::Depth:
            internalFormat = GL_DEPTH_COMPONENT;
            format = GL_DEPTH_COMPONENT;
            break;
        default:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    m_loaded = true;
    return true;
}

void Texture::bind(int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setFilter(TextureFilter min, TextureFilter mag) {
    glBindTexture(GL_TEXTURE_2D, m_id);

    GLenum minFilter, magFilter;
    switch (min) {
        case TextureFilter::Nearest: minFilter = GL_NEAREST; break;
        case TextureFilter::Linear: minFilter = GL_LINEAR; break;
        case TextureFilter::LinearMipmap: minFilter = GL_LINEAR_MIPMAP_LINEAR; break;
    }
    switch (mag) {
        case TextureFilter::Nearest: magFilter = GL_NEAREST; break;
        case TextureFilter::Linear: 
        case TextureFilter::LinearMipmap: magFilter = GL_LINEAR; break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::setWrap(TextureWrap wrapS, TextureWrap wrapT) {
    glBindTexture(GL_TEXTURE_2D, m_id);

    GLenum wrapSMode, wrapTMode;
    switch (wrapS) {
        case TextureWrap::Repeat: wrapSMode = GL_REPEAT; break;
        case TextureWrap::Clamp: wrapSMode = GL_CLAMP_TO_EDGE; break;
        case TextureWrap::Mirror: wrapSMode = GL_MIRRORED_REPEAT; break;
    }
    switch (wrapT) {
        case TextureWrap::Repeat: wrapTMode = GL_REPEAT; break;
        case TextureWrap::Clamp: wrapTMode = GL_CLAMP_TO_EDGE; break;
        case TextureWrap::Mirror: wrapTMode = GL_MIRRORED_REPEAT; break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapSMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapTMode);
}

unsigned char* Texture::stbiLoad(const char* path, int* width, int* height, int* channels, int desired_channels) {
    return stbi_load(path, width, height, channels, desired_channels);
}

void Texture::stbiFree(void* raw) {
    stbi_image_free(raw);
}

} // namespace triga
