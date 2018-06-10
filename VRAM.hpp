#pragma once

#include <cstddef>
#include <array>
#include <memory>
#include <tuple>

class BGMap {
public:
    BGMap() = default;

    ~BGMap() = default;

    void writePixel(uint8_t x, uint8_t y, uint8_t pixel) {
        m_data[x][y] = static_cast<std::byte>(pixel);
    }

    std::array<std::byte[32], 32>& getBuffer() {
        return m_data;
    }
private:
    std::array<std::byte[32], 32> m_data;
} __attribute__((packed, aligned(1)));

static_assert(sizeof(BGMap) == 1024);

class VRAM {
public:
    enum class Map {
        eSpritePatternTableAddrS = 0x8000,
        eSpritePatternTableAddrE = 0x8FFF,
        eSpriteAttrTableAddrS = 0xFE00,
        eSpriteAttrTableAddrE = 0xFE9F
    };

    VRAM() {
        new(m_data.data() + 0x9800)BGMap;
        new(m_data.data() + 0x9C00)BGMap;
    }

    ~VRAM() {
        auto[bgmap1, bgmap2] = bgMap();

        std::destroy_at(&bgmap1);
        std::destroy_at(&bgmap2);   
    }

    std::pair<BGMap&, BGMap&> bgMap() {
        return std::make_pair(std::ref(*reinterpret_cast<BGMap*>(m_data.data() + 0x9800)), std::ref(*reinterpret_cast<BGMap*>(m_data.data() + 0x9C00)));
    }
private:
    std::array<std::byte, 1024 * 8> m_data;
} __attribute__((packed, aligned(1)));

static_assert(sizeof(VRAM) == 1024 * 8);