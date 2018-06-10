#pragma once

#include <cstddef>
#include <array>

class HighRAM {
public:
    std::array<std::byte, 128> data;
} __attribute__((packed, aligned(1)));