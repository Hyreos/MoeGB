#pragma once

#include <array>
#include <cstddef>

struct ROMBank0 {
     std::array<std::byte, 16046> data;
} __attribute__((packed, aligned(1)));

struct SwitchableROMBank {
    std::array<std::byte, 1024*16> data;
} __attribute__((packed, aligned(1)));