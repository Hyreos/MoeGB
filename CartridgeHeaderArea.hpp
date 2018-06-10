#pragma once

#include <array>
#include <cstddef>
#include <algorithm>
#include <cstring>
#include <iostream>

#include "Cartrigbe.hpp"

class CartridgeHeaderArea {
public:
    CartridgeHeaderArea() {
        std::memset(m_title, 0, 10);
    }

    enum {
        logoSize = 48
    };

    void validate() {
        static auto clogo = std::array<uint8_t, logoSize> {
            0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
            0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
            0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
        };

        auto res = std::mismatch(clogo.begin(), clogo.end(), logo.begin(), logo.end());
        
        if (res.first != clogo.end()) {
            std::string str = "Invalid cartridge header at offset \"";
            str.append(std::to_string(std::distance(logo.begin(), res.second)));
            str.append("\"\n");
            throw std::runtime_error(str);
        }
    }

    std::array<std::byte, 4> nopjp;
    std::array<uint8_t, logoSize>  logo;
    char m_title[14];
    std::array<std::byte, 4> designation;
    std::byte colorCompatibilityByte;
    std::byte licenseCode;
    std::byte sgbCompatibilityByte;
    Cartrigbe::CartrigbeType cartType;
    Cartrigbe::ROMSize cartROMsize;
    Cartrigbe::RAMSize cartRAMsize;
    Cartrigbe::DestCode destCode;
    Cartrigbe::LicenseCodeOld oldLicenseCode;
    Cartrigbe::MaskROMVNumber maskROMversion;
    std::uint8_t complChecksum;
    std::uint16_t checksum;
} __attribute__((packed, aligned(1)));