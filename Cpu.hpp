#pragma once

#include <array>
#include <cassert>
#include <functional>
#include "Mmu.hpp"
#include "Screen.hpp"
#include "Cpu.hpp"
#include "Bootstrap.hpp"

template<std::size_t Size = 16, bool Splitted = true, bool DoubleMode = false>
class Register {
public:
    using data_t = std::conditional_t<Size == 16, uint16_t, std::conditional_t<DoubleMode, std::uint8_t*, std::uint8_t>>;

    Register() {
        static_assert(Size != 8 || Size != 16);
    }

    inline void write(std::remove_pointer_t<std::decay_t<data_t>> value) {
        if constexpr(std::is_same_v<data_t, std::uint16_t> || std::is_same_v<data_t, std::uint8_t>) {
            m_data = value;
        } else if constexpr(std::is_same_v<data_t, std::uint8_t*>) {
            *m_data = value;
        }
    }

    inline auto read() const {
        if constexpr(Size == 16) {
            return m_data;
        } else if constexpr(DoubleMode) {
            return *m_data;
        } else {
            return m_data;
        }
    }

    inline void inc(int16_t v = 1) {
        write(read() + v);
    }

    inline void dec(int16_t v = 1) {
        write(read() - v);
    }

    template<bool IsSplitted = Splitted>
    typename std::enable_if<IsSplitted == true, Register<8UL, false, true>>::type lower() {
        static_assert(Size == 16UL);
        return Register<8UL, false, true>( reinterpret_cast<std::uint8_t*>(&m_data) );
    }

    template<bool IsSplitted = Splitted>
    typename std::enable_if<IsSplitted == true, Register<8UL, false, true>>::type higher() {
        static_assert(Size == 16UL);
        return Register<8UL, false, true>( reinterpret_cast<std::uint8_t*>(&m_data) );
    }
private:
    template<bool IsSplitted = Splitted>
    typename std::enable_if<IsSplitted == false, Register<8UL, false, true>>::type lower() {
        static_assert(Size == 16UL);
        return Register<8UL, false, true>( reinterpret_cast<std::uint8_t*>(&m_data) );
    }

    template<bool IsSplitted = Splitted>
    typename std::enable_if<IsSplitted == false, Register<8UL, false, true>>::type higher() {
        static_assert(Size == 16UL);
        return Register<8UL, false, true>( reinterpret_cast<std::uint8_t*>(&m_data) );
    }

    Register(data_t byte) : m_data(byte) { }

    friend class Register<16UL, true, false>;

    data_t m_data;
};

struct RegisterSet {
    Register<8UL> scrollX, scrollY;
    Register<8UL> lcdc;
    Register<8UL> wndPosX, wndPosY;
    Register<8UL> flags;
    Register<16UL, true, false> af, bc, de, hl;
    Register<16UL, false, false> pc, sp;
    Register<8UL, false, true> 
    a = af.lower(), 
    f = af.higher(), 
    b = bc.lower(), 
    c = bc.higher(), 
    d = de.lower(), 
    e = de.higher(), 
    h = hl.lower(), 
    l = hl.higher();
    Register<8UL> p1;
    Register<8UL> sb;
    Register<8UL> sc;
};

class Cpu 
{
public:
    using instructionCall_t = std::function<void()>;

    enum Flags 
    {
        eNull0 = 0x1, eNull1 = 0x2, eNull2 = 0x4, eNull3 = 0x8, eC = 0x10, eH = 0x20, eN = 0x40, eZ = 0x80
    };

    enum class Status 
    {
        eStop, eNone
    };

    enum OPCodes 
    {
        eNOP,
        eLD_BC_d16,
        eLD_rBC_A,
        eINC_BC,
        eINC_B,
        eDEC_B,
        eLD_B_d8,
        eRLCA,
        eLD_ra16_SP,
        eADD_HL_BC,
        eLD_A_rBC,eDEC_BC,
        eINC_C,
        eDEC_C,
        eLD_C_d8,
        eRRCA,
        eSTOP_0,
        eLD_DE_d16,
        eLD_rDE_A,
        eINC_DE,
        eINC_D,
        eDEC_D,
        eLD_D_d8,
        eRLA,
        eJR_r8,
        eADD_HL_DE,
        eLD_A_rDE,eDEC_DE,
        eINC_E,
        eDEC_E,
        eLD_E_d8,
        eRRA,
        eJR_NZ_r8,
        eLD_HL_d16,
        eLD_rHLp_A,
        eINC_HL,
        eINC_H,
        eDEC_H,
        eLD_H_d8,
        eDAA,
        eJR_Z_r8,
        eADD_HL_HL,
        eLD_A_rHLp,
        eDEC_HL,
        eINC_L,
        eDEC_L,
        eLD_L_d8,
        eCPL,
        eJR_NC_r8,
        eLD_SP_d16,
        eLD_rHLm_A,
        eINC_SP,
        eINC_rHL,
        eDEC_rHL,
        eLD_rHL_d8,
        eSCF,
        eJR_C_r8,
        eADD_HL_SP,
        eLD_A_rHLm,
        eDEC_SP,
        eINC_A,
        eDEC_A,
        eLD_A_d8,
        eCCF,
        eLD_B_B,
        eLD_B_C,
        eLD_B_D,
        eLD_B_E,
        eLD_B_H,
        eLD_B_L,
        eLD_B_rHL,
        eLD_B_A,
        eLD_C_B,
        eLD_C_C,
        eLD_C_D,
        eLD_C_E,
        eLD_C_H,
        eLD_C_L,
        eLD_C_rHL,
        eLD_C_A,
        eLD_D_B,
        eLD_D_C,
        eLD_D_D,
        eLD_D_E,
        eLD_D_H,
        eLD_D_L,
        eLD_D_rHL,
        eLD_D_A,
        eLD_E_B,
        eLD_E_C,
        eLD_E_D,
        eLD_E_E,
        eLD_E_H,
        eLD_E_L,
        eLD_E_rHL,
        eLD_E_A,
        eLD_H_B,
        eLD_H_C,
        eLD_H_D,
        eLD_H_E,
        eLD_H_H,
        eLD_H_L,
        eLD_H_rHL,
        eLD_H_A,
        eLD_L_B,
        eLD_L_C,
        eLD_L_D,
        eLD_L_E,
        eLD_L_H,
        eLD_L_L,
        eLD_L_rHL,
        eLD_L_A,
        eLD_rHL_B,
        eLD_rHL_C,
        eLD_rHL_D,
        eLD_rHL_E,
        eLD_rHL_H,
        eLD_rHL_L,
        eHALT,
        eLD_rHL_A,
        eLD_A_B,
        eLD_A_C,
        eLD_A_D,
        eLD_A_E,
        eLD_A_H,
        eLD_A_L,
        eLD_A_rHL,
        eLD_A_A,
        eADD_A_B,
        eADD_A_C,
        eADD_A_D,
        eADD_A_E,
        eADD_A_H,
        eADD_A_L,
        eADD_A_rHL,
        eADD_A_A,
        eADC_A_B,
        eADC_A_C,
        eADC_A_D,
        eADC_A_E,
        eADC_A_H,
        eADC_A_L,
        eADC_A_rHL,
        eADC_A_A,
        eSUB_B,
        eSUB_C,
        eSUB_D,
        eSUB_E,
        eSUB_H,
        eSUB_L,
        eSUB_rHL,
        eSUB_A,
        eSBC_A_B,
        eSBC_A_C,
        eSBC_A_D,
        eSBC_A_E,
        eSBC_A_H,
        eSBC_A_L,
        eSBC_A_rHL,
        eSBC_A_A,
        eAND_B,
        eAND_C,
        eAND_D,
        eAND_E,
        eAND_H,
        eAND_L,
        eAND_rHL,
        eAND_A,
        eXOR_B,
        eXOR_C,
        eXOR_D,
        eXOR_E,
        eXOR_H,
        eXOR_L,
        eXOR_rHL,
        eXOR_A,
        eOR_B,
        eOR_C,
        eOR_D,
        eOR_E,
        eOR_H,
        eOR_L,
        eOR_rHL,
        eOR_A,
        eCP_B,
        eCP_C,
        eCP_D,
        eCP_E,
        eCP_H,
        eCP_L,
        eCP_rHL,
        eCP_A,
        eRET_NZ,
        ePOP_BC,
        eJP_NZ_a16,
        eJP_a16,
        eCALL_NZ_a16,
        ePUSH_BC,
        eADD_A_d8,
        eRST_00H,
        eRET_Z,
        eRET,
        eJP_Z_a16,
        ePREFIX_CB,
        eCALL_Z_a16,
        eCALL_a16,
        eADC_A_d8,
        eRST_08H,
        eRET_NC,
        ePOP_DE,
        eJP_NC_a16,
        EMPTY0,
        eCALL_NC_a16,
        ePUSH_DE,
        eSUB_d8,
        eRST_10H,
        eRET_C,
        eRETI,
        eJP_C_a16,
        EMPTY1,
        eCALL_C_a16,
        EMPTY2,
        eSBC_A_d8,
        eRST_18H,
        eLDH_ra8_A,
        ePOP_HL,
        eLD_rC_A,
        EMPTY3,
        EMPTY4,
        ePUSH_HL,
        eAND_d8,
        eRST_20H,
        eADD_SP_r8,
        eJP_rHL,
        eLD_r16_A,
        EMPTY5,
        EMPTY6,
        EMPTY7,
        eXOR_d8,
        eRST_28H,
        eLDH_A_ra8,
        ePOP_AF,
        eLD_A_rC,
        eDI,
        EMPTY8,
        ePUSH_AF,
        eOR_d8,
        eRST_30H,
        eLD_HL_SP_p_r8,
        eLD_SP_HL,
        eLD_A_ra16,
        eEI,
        EMPTY9,
        EMPTY10,
        eCP_d8,
        eRST_38H,
        OPCODE_N
    };

    Cpu();

    Cpu(Cartrigbe& cartrigbe);

    ~Cpu() = default;

    void boot(Cartrigbe& cartrigbe); 

    instructionCall_t& decode(OPCodes inst);

    inline RegisterSet& registers() 
    {
        return m_registers;
    }

    OPCodes fetch();

    Status status() const noexcept;

    void update();

    Screen& screen() noexcept;

    MMU& mmu() noexcept;

    std::array<instructionCall_t, 0xFF> m_opcodefunset;

    MMU m_mmu;

    Screen m_screen;

    Status m_status;

    RegisterSet m_registers;
};

class ResIntVectorTable {
public:
    using intFunc_t = std::function<void(const Cpu&)>;

    static void intVBlank(const Cpu& cpu) 
    {

    }

    static void intLCDC(const Cpu& cpu) 
    {

    }

    static void intTimer(const Cpu& cpu) 
    {

    }

    static void intSerial(const Cpu& cpu) 
    {
        
    }

    static void intJoypad(const Cpu& cpu) 
    {

    }

    ResIntVectorTable() 
    {
        m_intFuncs = {
            intVBlank,
            intLCDC,
            intTimer,
            intSerial,
            intJoypad
        };
    }

    ~ResIntVectorTable() = default;

    enum class Interrupts : uint8_t 
    {
        eVBlank,
        eLCDC,
        eTimer,
        eSerial,
        eJoypad
    };

    intFunc_t call(Interrupts interrupt) 
    {
        return m_intFuncs.at(static_cast<uint8_t>(interrupt));
    }
private:
    std::array<intFunc_t, 6U> m_intFuncs;
};
