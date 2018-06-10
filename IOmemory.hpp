#pragma once

#include <array>
#include <cstddef>

class IOMemory {
public:
    std::array<std::byte, 128> data;
} __attribute__((packed, aligned(1)));