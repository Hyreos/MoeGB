#pragma once

#include "Cpu.hpp"
#include "VRAM.hpp"
#include "CartridgeHeaderArea.hpp"
#include "ROMBanks.hpp"
#include "RAMBanks.hpp"
#include "OAM.hpp"
#include "IOmemory.hpp"
#include "HighRAM.hpp"
#include "InterruptEnableRegister.hpp"

#include <array>
#include <cstddef>
#include <functional>

class Memory 
{
public:
    Memory() = default;

    ~Memory() = default;

    std::array<std::byte, 256> rivt;
    CartridgeHeaderArea cartridgeHeaderArea;
    ROMBank0 romBank0;
    SwitchableROMBank switchableRomBank;
    VRAM videoRAM;
    ExternalRAM externalRAM;
    InternalRAM internalRAM;
    EchoInternalRAM echoInternalRAM;
    OAM oam;
    std::array<std::byte, 96> unused;
    IOMemory ioMemory;
    HighRAM highRAM;
    InterruptEnableRegister intEnableRegister;
} __attribute__((packed, aligned(1)));

class MMU 
{    
public:
    enum class MemoryMap : uint16_t
    {
        eROMB0Addr = 0x0000,
        eSROMBAddr = 0x4000,
        eVRAMAddr = 0x8000,
        eSRAMBAddr = 0xA000,
        eIRAM8kBAddr = 0xC000,
        eEchoAddr = 0xE000,
        eOAMAddr = 0xFE00,
        eNull0Addr = 0xFEA0,
        eIOpAddr = 0xFF00,
        eEmpty1Addr = 0xFF4C,
        eIRAMAddr = 0XFF80,
        eIERAddr = 0xFFFF
    };

    MMU() = default;

    ~MMU() = default;

    void writeByte(uint16_t address, uint8_t value)
    {
        reinterpret_cast<uint8_t*>(&memory)[address] = value;
    }

    void writeWord(uint16_t address, uint16_t value) {
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(&memory) + address) = value;
    }

    uint8_t readByte(uint16_t address) 
    {
        return reinterpret_cast<uint8_t*>(&memory)[address];
    }

    uint16_t readWord(uint16_t address)
    {
        return *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(&memory) + address);
    }
    

    Memory memory;
};