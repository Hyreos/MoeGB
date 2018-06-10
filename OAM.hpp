#pragma once

#include <array>
#include <cstddef>

class SpriteAttrBlock 
{
public:
    SpriteAttrBlock() = default;

    ~SpriteAttrBlock() = default;

    std::byte y, x, number, flags;

    enum class Flags {
        ePalleteNumber = 0x8,
        eXFlip = 0x10,
        eYFlip = 0x20,
        ePriority = 0x40
    };
} __attribute__((packed, aligned(1)));

static_assert(sizeof(SpriteAttrBlock) == 4);

class OAM
{
public:
    OAM() = default;

    ~OAM() = default;

    std::array<SpriteAttrBlock, 40> blocks;
} __attribute__((packed, aligned(1)));

static_assert(sizeof(OAM) == 4 * 40);