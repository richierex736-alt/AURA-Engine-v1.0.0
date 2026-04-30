#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace triga {

enum class TextureFormat {
    RGBA,
    RGB,
    Alpha,
    Depth
};

enum class TextureFilter {
    Nearest,
    Linear,
    LinearMipmap
};

enum class TextureWrap {
    Repeat,
    Clamp,
    Mirror
};

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& filepath);
    bool create(int width, int height, TextureFormat format, const void* data = nullptr);

    void bind(int slot = 0) const;
    void unbind() const;

    void setFilter(TextureFilter min, TextureFilter mag);
    void setWrap(TextureWrap wrapS, TextureWrap wrapT);

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    TextureFormat getFormat() const { return m_format; }
    unsigned int getID() const { return m_id; }

    bool isLoaded() const { return m_loaded; }

private:
    unsigned int m_id;
    int m_width;
    int m_height;
    TextureFormat m_format;
    bool m_loaded;

    static unsigned char* stbiLoad(const char* path, int* width, int* height, int* channels, int desired_channels);
    static void stbiFree(void* raw);
};

} // namespace triga
