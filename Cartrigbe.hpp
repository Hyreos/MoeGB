#pragma once

#include <string_view>
#include <fstream>
#include <vector>
#include <array>

class Cartrigbe 
{
public:
    Cartrigbe() = delete;

    Cartrigbe(const std::string_view path);

    ~Cartrigbe() = default;

    void load(const std::string_view path);

    std::vector<uint8_t>& content();

    enum class ReservedMemoryLocations : std::uint16_t
    {
        eRestart0Addr = 0x0000,
        eRestart8Addr = 0x0008,
        eRestart10Addr = 0x0010,
        eRestart18Addr = 0x0018,
        eRestart20Addr = 0X0020,
        eRestart28Addr = 0x0028,
        eRestart30Addr = 0x0030,
        eRestart38Addr = 0x0038,
        eVBlankIntSAddr = 0x0040,
        eLCDCSttsIntSAddr = 0x0048,
        eTimerOverflowISAddr = 0x0050,
        eSerialTransferCompletionISAddr = 0x0058,
        eP1013IntSAddr = 0x0060,
        eIInfoAreaSAddr = 0x100,
        eIInfoAreaEAddr = 0x103,
        eNintendoGraphicsSAddr = 0x104,
        eNintendoGraphicsEAddr = 0x113,
        eTitleSaddr = 0x134,
        eTitleEaddr = 0x142,
        eConTypeAddr = 0x143, /* 0x80 = CGB, 0x00 or other = no CGB */
        eLCHighNibbleAddr = 0x144,
        eLCLowNibbleAddr = 0x145,
        eGB_SGB_IndicatorAddr = 0x146,
        eCartridgeTypeAddr = 0x147,
        eROMSizeAddr = 0x148,
        eRAMSizeAddr = 0x149,
        eDestCodeAddr = 0x14A,
        eLColdAddr = 0x14B,
        eMaskROMVNumberAddr = 0x14C,
        eComplCheckAddr = 0x14D,
        eCheckSumSAddr = 0x14E,
        eCheckSumEAddr = 0x14F
    };

    enum class CartrigbeType : std::uint8_t
    {
        eROM_ONLY = 0x0,
        eROM_MBC1 = 0x1,
        eROM_MBC1_RAM = 0x2,
        eROM_MBC1_RAM_BATT = 0x3,
        eROM_MBC2 = 0x5,
        eROM_MBC2_BATTERY = 0x6,
        eROM_RAM = 0x8,
        eROM_RAM_BATTERY = 0x9,
        eROM_MMM01 = 0xB,
        eROM_MMM01_SRAM = 0xC,
        eROM_MMM01_SRAM_BATT = 0xD,
        eROM_MBC3_RAM = 0x12,
        eROM_MBC3_RAM_BATT = 0x13,
        eROM_MBC5 = 0x19,
        eROM_MBC5_RAM = 0x1A,
        eROM_MBC5_RAM_BATT = 0x1B,
        eROM_MBC5_RUMBLE = 0x1C,
        eROM_MBC5_RUMBLE_SRAM = 0x1D,
        eROM_MBC5_RUMBLE_SRAM_BATT = 0x1E,
        ePocketCamera = 0x1F,
        eBandai_TAMA5 = 0xFD,
        eHudson_HuC3 = 0xFE,
        eROM_MBC3_TIMER_BATT = 0xF,
        eROM_MBC3_TIMER_RAM_BATT = 0x10,
        eROM_MBC3 = 0x11,
        eHudson_HuC1 = 0xFF
    };

    enum class ROMSize : std::uint8_t
    {
        e32KB,
        e64KB,
        e128KB,
        e256KB,
        e512KB,
        e1MB,
        e1_1MB = 0x52,
        e1_2MB = 0x53,
        e1_5MB = 0x54
    };

    enum class RAMSize : std::uint8_t
    {
        eNone,
        e2KB,
        e8KB,
        e32KB,
        e128KB
    };

    enum class DestCode : std::uint8_t
    {
        Japanese,
        NOnJapanese
    };

    enum class LicenseCodeOld : std::uint8_t
    {
        eNoIdea = 0x33,
        eAccolade = 0x79,
        eKonami = 0xA4
    };

    enum class MaskROMVNumber : std::uint16_t
    {
        eZero
    };
private:
    std::vector<uint8_t> m_content;
};
