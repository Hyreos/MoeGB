#pragma once

#include <cstddef>

class InterruptEnableRegister {
public:
    std::byte data;
} __attribute__((packed, aligned(1)));