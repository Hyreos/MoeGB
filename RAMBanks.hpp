#pragma once

#include <array>
#include <cstddef>

class SwitchableRAMBank {
public:
    SwitchableRAMBank() = default;

    ~SwitchableRAMBank() = default;

    std::array<std::byte, 8 * 1024> data;
} __attribute__((packed, aligned(1)));


class InternalRAM {
public:
    InternalRAM() = default;

    ~InternalRAM() = default;

    std::array<std::byte, 8 * 1024> data;
} __attribute__((packed, aligned(1)));

class EchoInternalRAM {
public:
    EchoInternalRAM() = default;

    ~EchoInternalRAM() = default;

    std::array<std::byte, 8 * 1024> data;
} __attribute__((packed, aligned(1)));

class InternalRAM2 {
public:
    InternalRAM2() = default;

    ~InternalRAM2() = default;

    std::array<std::byte, 128> data;
} __attribute__((packed, aligned(1)));

class ExternalRAM {
public:
    ExternalRAM() = default;

    ~ExternalRAM() = default;

    std::array<std::byte, 8 * 1024> data;
} __attribute__((packed, aligned(1)));