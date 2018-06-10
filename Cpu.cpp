#include "Cpu.hpp"

#include <iostream>
#include <cstring>

Cpu::Cpu() {
    m_opcodefunset[OPCodes::eNOP] = [&] {
    };

    m_opcodefunset[OPCodes::eLD_BC_d16] = [&] {
        auto& dest = registers().bc;
        auto src = mmu().readByte(registers().pc.read() + 1);
        dest.write(src);
    };

    m_opcodefunset[OPCodes::eLD_rBC_A] = [&] {
        mmu().writeByte(registers().bc.read(), registers().a.read());
    };

    m_opcodefunset[OPCodes::eINC_BC] = [&] {
        registers().bc.write(registers().bc.read() + 1);
    };

    m_opcodefunset[OPCodes::eINC_B] = [&] {
        registers().b.write(registers().b.read() + 1);
        auto& flags = registers().flags;
        flags.write(flags.read() | Flags::eN);
    };

    m_opcodefunset[OPCodes::eDEC_B] = [&] {
        registers().b.write(registers().b.read() - 1);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_B_d8] = [&] {
        registers().b.write(mmu().readByte(registers().pc.read() + 1));
    };

    m_opcodefunset[OPCodes::eRLCA] = [&] {
        auto& flags = registers().flags;
        flags.write(((flags.read() & ~Flags::eN) & ~Flags::eZ) & ~Flags::eH);
    };

    m_opcodefunset[OPCodes::eLD_ra16_SP] = [&] {
        mmu().writeWord(mmu().readWord(registers().pc.read() + 1), registers().sp.read());
    };

    m_opcodefunset[OPCodes::eADD_HL_BC] = [&] {
        registers().hl.write(registers().bc.read());
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_A_rBC] = [&] {
        registers().a.write(mmu().readByte(registers().bc.read()));
    };

    m_opcodefunset[OPCodes::eDEC_BC] = [&] {
        registers().bc.write(registers().bc.read() - 1);
    };

    m_opcodefunset[OPCodes::eINC_C] = [&] {
        registers().c.write(registers().c.read() + 1);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eDEC_C] = [&] {
        registers().c.write(registers().c.read() - 1);
        auto& flags = registers().flags;
        flags.write(flags.read() | Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_C_d8] = [&] {
        registers().c.write(mmu().readByte(registers().pc.read() + 1));
    };

    m_opcodefunset[OPCodes::eRRCA] = [&] {
        auto& flags = registers().flags;
        flags.write(((flags.read() & ~Flags::eN) & ~Flags::eZ) & ~Flags::eH);
    };

    m_opcodefunset[OPCodes::eSTOP_0] = [&] {

    };

    m_opcodefunset[OPCodes::eLD_DE_d16] = [&] {
        registers().de.write(mmu().readWord(registers().pc.read() + 1));
    };

    m_opcodefunset[OPCodes::eLD_rDE_A] = [&] {
        mmu().writeByte(registers().de.read(), registers().a.read());
    };

    m_opcodefunset[OPCodes::eINC_DE] = [&] {
        registers().de.write(registers().de.read() + 1);
    };

    m_opcodefunset[OPCodes::eINC_D] = [&] {
        registers().d.write(registers().d.read() + 1);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eDEC_D] = [&] {
        registers().d.write(registers().d.read() - 1);
        auto& flags = registers().flags;
        flags.write(flags.read() | Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_D_d8] = [&] {
        registers().d.write(mmu().readByte(registers().pc.read() + 1));
    };

    m_opcodefunset[OPCodes::eRLA] = [&] {
        auto& flags = registers().flags;
        flags.write(flags.read() & ~(Flags::eN | Flags::eZ | Flags::eH));
    };

    m_opcodefunset[OPCodes::eJR_r8] = [&] {
        registers().pc.write(registers().pc.read() + static_cast<int8_t>(mmu().readByte(registers().pc.read() + 1)));
    };

    m_opcodefunset[OPCodes::eADD_HL_DE] = [&] {
        registers().hl.write(registers().hl.read() + registers().de.read());
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_A_rDE] = [&] {
        registers().a.write(mmu().readByte(registers().pc.read() + 1));
    };

    m_opcodefunset[OPCodes::eDEC_DE] = [&] {
        registers().de.write(registers().de.read() - 1);
    };

    m_opcodefunset[OPCodes::eINC_E] = [&] {
        registers().e.write(registers().e.read() + 1);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eDEC_E] = [&] {
        registers().e.write(registers().e.read() - 1);
        auto& flags = registers().flags;
        flags.write(flags.read() | Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_E_d8] = [&] {
        registers().e.write(mmu().readByte(registers().pc.read() + 1));
    };

    m_opcodefunset[OPCodes::eRRA] = [&] {
        flags.write(flags.read() & ~(Flags::eN | Flags::eZ | Flags::eH));
    };

    m_opcodefunset[OPCodes::eJR_NZ_r8] = [&] {
        auto offaddr = static_cast<int8_t>(mmu().readByte(registers().pc.read() + 1));
        if (!(registers().flags.read() & Flags::eZ)) {
            registers().pc.write(registers().pc.read() + offaddr);
        }
    };

    m_opcodefunset[OPCodes::eLD_HL_d16] = [&] {
        auto src = mmu().readWord(registers().pc.read() + 1);
        registers().hl.write(src);
    };

    m_opcodefunset[OPCodes::eLD_rHLp_A] = [&] {
        auto addr = registers().hl.read();
        mmu().writeByte(addr, registers().a.read());
        registers().hl.write(addr + 1);
    };

    m_opcodefunset[OPCodes::eINC_HL] = [&] {
        registers().hl.write(registers().hl.read() + 1);
    };

    m_opcodefunset[OPCodes::eINC_H] = [&] {
        registers().h.write(registers().h.read() + 1);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eDEC_H] = [&] {
        registers().h.write(registers().h.read() - 1);
        auto& flags = registers().flags;
        flags.write(flags.read() | Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_H_d8] = [&] {
        auto operand = mmu().readByte(registers().pc.read() + 1);
        registers().h.write(operand);
    };

    m_opcodefunset[OPCodes::eDAA] = [&] {
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eH);
    };

    m_opcodefunset[OPCodes::eJR_Z_r8] = [&] {
        auto operand = mmu().readByte(registers().pc.read() + 1);
        if (registers().flags.read() & Flags::eZ) {
            registers().pc.write(registers().pc.read() + operand);
        }
    };

    m_opcodefunset[OPCodes::eADD_HL_HL] = [&] {
        registers().hl.write(registers().hl.read() * 2);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_A_rHLp] = [&] {
        auto address = registers().hl.read();
        registers().a.write(address);
        registers().hl.write(address + 1);
    };

    m_opcodefunset[OPCodes::eDEC_HL] = [&] {
        registers().hl.write(registers().hl.read() - 1);
    };

    m_opcodefunset[OPCodes::eINC_L] = [&] {
        registers().l.write(registers().l.read() + 1);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~Flags::eN);
    };

    m_opcodefunset[OPCodes::eDEC_L] = [&] {
        registers().l.write(registers().l.read() - 1);
        auto& flags = registers().flags;
        flags.write(flags.read() | Flags::eN);
    };

    m_opcodefunset[OPCodes::eLD_L_d8] = [&] {
        auto operand = mmu().readByte(registers().pc.read() + 1);
        registers().l.write(operand);
    };

    m_opcodefunset[OPCodes::eCPL] = [&] {
        registers().a.write(registers().a.read() ^ 0xFF);
        auto& flags = registers().flags;
        flags.write(flags.read() & ~(Flags::eN | Flags::eH));
    };

    m_opcodefunset[OPCodes::eJR_NC_r8] = [&] {
        auto operand = mmu().readByte(registers().pc.read() + 1);
        if (!(registers().flags.read() & Flags::eC)) {
            registers().pc.write(registers().pc.read() + operand);
        }
    };

    m_opcodefunset[OPCodes::eLD_SP_d16] = [&] {
        auto operand = mmu().readWord(registers().pc.read() + 1);
        registers().sp.write(operand);
    };

    m_opcodefunset[OPCodes::eLD_rHLm_A] = [&] {
        auto address = registers().hl.read();
        registers().hl.dec();
        mmu().writeByte(address, registers().a.read());
    };

    m_opcodefunset[OPCodes::eINC_SP] = [&] {
        registers().sp.inc();
    };

    m_opcodefunset.at(OPCodes::eINC_rHL) = [&] {
        auto address = registers().hl.read();
        auto v = mmu().readByte(address);
        mmu().writeByte(address, v + 1);
    };

    m_opcodefunset.at(OPCodes::eDEC_rHL) = [&] {
        auto address = registers().hl.read();
        auto v = mmu().readByte(address);
        mmu().writeByte(address, v - 1);
    };

    m_opcodefunset.at(OPCodes::eLD_rHL_d8) = [&] {
        auto operand = mmu().readByte(registers().pc.read() + 1);
        auto address = registers().hl.read();
        mmu().writeByte(address, operand);
    };

    m_opcodefunset.at(OPCodes::eSCF) = [&] {

    };

    m_opcodefunset.at(OPCodes::eJR_C_r8) = [&] {
        auto operand = mmu().readByte(registers().pc.read() + 1);
        if (registers().flags.read() & Flags::eC) {
            registers().pc.inc(operand);
        }
    };

    m_opcodefunset.at(OPCodes::eADD_HL_SP) = [&] {
        registers().hl.inc(registers().sp.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_rHLm) = [&] {
        auto address = registers().hl.read();
        registers().hl.dec();
        registers().a.write(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eDEC_SP) = [&] {
        registers().sp.dec();
    };

    m_opcodefunset.at(OPCodes::eINC_A) = [&] {
        registers().a.inc();
    };

    m_opcodefunset.at(OPCodes::eDEC_A) = [&] {
        registers().a.dec();
    };

    m_opcodefunset.at(OPCodes::eLD_A_d8) = [&] {
        auto operand = mmu().readByte(registers().pc.read() + 1);
        registers().a.write(operand);
    };

    m_opcodefunset.at(OPCodes::eCCF) = [&] {

    };

    m_opcodefunset.at(OPCodes::eLD_B_B) = [&] {
        registers().b.write(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_B_C) = [&] {
        registers().b.write(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_B_D) = [&] {
        registers().b.write(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_B_E) = [&] {
        registers().b.write(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_B_H) = [&] {
        registers().b.write(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_B_L) = [&] {
        registers().b.write(registers().l.read());   
    };

    m_opcodefunset.at(OPCodes::eLD_B_rHL) = [&] {
        auto address = registers().hl.read();
        registers().b.write(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eLD_B_A) = [&] {
        registers().b.write(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eLD_C_B) = [&] {
        registers().c.write(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_C_C) = [&] {
        registers().c.write(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_C_D) = [&] {
        registers().c.write(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_C_E) = [&] {
        registers().c.write(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_C_H) = [&] {
        registers().c.write(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_C_L) = [&] {
        registers().c.write(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eLD_C_rHL) = [&] {
        registers().c.write(mmu().readByte(registers().hl.read()));
    };

    m_opcodefunset.at(OPCodes::eLD_C_A) = [&] {
        registers().c.write(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eLD_D_B) = [&] {
        registers().d.write(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_D_C) = [&] {
        registers().d.write(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_D_D) = [&] {
        registers().d.write(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_D_E) = [&] {
        registers().d.write(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_D_H) = [&] {
        registers().d.write(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_D_L) = [&] {
        registers().d.write(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eLD_D_rHL) = [&] {
        auto address = registers().hl.read();
        registers().d.write(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eLD_D_A) = [&] {
        registers().d.write(registers().a.read());
    };  

    m_opcodefunset.at(OPCodes::eLD_E_B) = [&] {
        registers().e.write(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_E_C) = [&] {
        registers().e.write(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_E_D) = [&] {
        registers().e.write(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_E_E) = [&] {
        registers().e.write(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_E_H) = [&] {
        registers().e.write(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_E_L) = [&] {
        registers().e.write(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eLD_E_rHL) = [&] {
        auto address = registers().hl.read();
        registers().e.write(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eLD_E_A) = [&] {
        registers().e.write(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eLD_H_B) = [&] {
        registers().h.write(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_H_C) = [&] {
        registers().h.write(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_H_D) = [&] {
        registers().h.write(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_H_E) = [&] {
        registers().h.write(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_H_H) = [&] {
        registers().h.write(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_H_L) = [&] {
        registers().h.write(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eLD_H_rHL) = [&] {
        auto address = registers().hl.read();
        registers().h.write(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eLD_H_A) = [&] {
        registers().h.write(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eLD_L_B) = [&] {
        registers().l.write(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_L_C) = [&] {
        registers().l.write(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_L_D) = [&] {
        registers().l.write(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_L_E) = [&] {
        registers().l.write(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_L_H) = [&] {
        registers().l.write(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_L_L) = [&] {
        registers().l.write(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eLD_L_rHL) = [&] {
        auto address = registers().hl.read();
        registers().l.write(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eLD_L_A) = [&] {
        registers().l.write(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eLD_rHL_B) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_rHL_C) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_rHL_D) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_rHL_E) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_rHL_H) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_rHL_L) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eHALT) = [&] {

    };

    m_opcodefunset.at(OPCodes::eLD_rHL_A) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_B) = [&] {
        registers().a.write(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_C) = [&] {
        registers().a.write(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_D) = [&] {
        registers().a.write(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_E) = [&] {
        registers().a.write(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_H) = [&] {
        registers().a.write(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_L) = [&] {
        registers().a.write(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_rHL) = [&] {
        auto address = registers().hl.read();
        mmu().writeByte(address, registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eLD_A_A) = [&] {
        registers().a.write(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eADD_A_B) = [&] {
        registers().a.inc(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eADD_A_C) = [&] {
        registers().a.inc(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eADD_A_D) = [&] {
        registers().a.inc(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eADD_A_E) = [&] {
        registers().a.inc(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eADD_A_H) = [&] {
        registers().a.inc(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eADD_A_L) = [&] {
        registers().a.inc(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eADD_A_rHL) = [&] {
        auto address = registers().hl.read();
        registers().a.inc(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eADD_A_A) = [&] {
        registers().a.inc(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eADC_A_B) = [&] {
        registers().a.inc(registers().b.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eADC_A_C) = [&] {
        registers().a.inc(registers().c.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eADC_A_D) = [&] {
        registers().a.inc(registers().d.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eADC_A_E) = [&] {
        registers().a.inc(registers().e.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eADC_A_H) = [&] {
        registers().a.inc(registers().h.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eADC_A_L) = [&] {
        registers().a.inc(registers().l.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eADC_A_rHL) = [&] {
        auto address = registers().hl.read();
        registers().a.inc(mmu().readByte(address) + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eADC_A_A) = [&] {
        registers().a.inc(registers().a.read() + (registers().flags.read() & Flags::eC));
    };


    m_opcodefunset.at(OPCodes::eSUB_B) = [&] {
        registers().a.dec(registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eSUB_C) = [&] {
        registers().a.dec(registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eSUB_D) = [&] {
        registers().a.dec(registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eSUB_E) = [&] {
        registers().a.dec(registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eSUB_H) = [&] {
        registers().a.dec(registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eSUB_L) = [&] {
        registers().a.dec(registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eSUB_rHL) = [&] {
        auto address = registers().hl.read();
        registers().a.dec(mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eSUB_A) = [&] {
        registers().a.dec(registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eSBC_A_B) = [&] {
        registers().a.dec(registers().b.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eSBC_A_C) = [&] {
        registers().a.dec(registers().c.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eSBC_A_D) = [&] {
        registers().a.dec(registers().d.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eSBC_A_E) = [&] {
        registers().a.dec(registers().e.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eSBC_A_H) = [&] {
        registers().a.dec(registers().h.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eSBC_A_L) = [&] {
        registers().a.dec(registers().l.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eSBC_A_rHL) = [&] {
        auto address = registers().hl.read();
        registers().a.dec(mmu().readByte(address) + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eSBC_A_A) = [&] {
        registers().a.dec(registers().a.read() + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eAND_B) = [&] {
        registers().a.write(registers().a.read() & registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eAND_C) = [&] {
        registers().a.write(registers().a.read() & registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eAND_D) = [&] {
        registers().a.write(registers().a.read() & registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eAND_E) = [&] {
        registers().a.write(registers().a.read() & registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eAND_H) = [&] {
        registers().a.write(registers().a.read() & registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eAND_L) = [&] {
        registers().a.write(registers().a.read() & registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eAND_rHL) = [&] {
        auto address = registers().hl.read();

        registers().a.write(registers().a.read() & mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eAND_A) = [&] {
        registers().a.write(registers().a.read() & registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eXOR_B) = [&] {
        registers().a.write(registers().a.read() ^ registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eXOR_C) = [&] {
        registers().a.write(registers().a.read() ^ registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eXOR_D) = [&] {
        registers().a.write(registers().a.read() ^ registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eXOR_E) = [&] {
        registers().a.write(registers().a.read() ^ registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eXOR_H) = [&] {
        registers().a.write(registers().a.read() ^ registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eXOR_L) = [&] {
        registers().a.write(registers().a.read() ^ registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eXOR_rHL) = [&] {
        auto address = registers().hl.read();
        registers().a.write(registers().a.read() ^ mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eXOR_A) = [&] {
        registers().a.write(registers().a.read() ^ registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eOR_B) = [&] {
        registers().a.write(registers().a.read() | registers().b.read());
    };

    m_opcodefunset.at(OPCodes::eOR_C) = [&] {
        registers().a.write(registers().a.read() | registers().c.read());
    };

    m_opcodefunset.at(OPCodes::eOR_D) = [&] {
         registers().a.write(registers().a.read() | registers().d.read());
    };

    m_opcodefunset.at(OPCodes::eOR_E) = [&] {
        registers().a.write(registers().a.read() | registers().e.read());
    };

    m_opcodefunset.at(OPCodes::eOR_H) = [&] {
        registers().a.write(registers().a.read() | registers().h.read());
    };

    m_opcodefunset.at(OPCodes::eOR_L) = [&] {
         registers().a.write(registers().a.read() | registers().l.read());
    };

    m_opcodefunset.at(OPCodes::eOR_rHL) = [&] {
        auto address = registers().hl.read();

        registers().a.write(registers().a.read() | mmu().readByte(address));
    };

    m_opcodefunset.at(OPCodes::eOR_A) = [&] {
        registers().a.write(registers().a.read() | registers().a.read());
    };

    m_opcodefunset.at(OPCodes::eCP_B) = [&] {

    };

    m_opcodefunset.at(OPCodes::eCP_C) = [&] {

    };

    m_opcodefunset.at(OPCodes::eCP_D) = [&] {

    };

    m_opcodefunset.at(OPCodes::eCP_E) = [&] {

    };

    m_opcodefunset.at(OPCodes::eCP_H) = [&] {

    };

    m_opcodefunset.at(OPCodes::eCP_L) = [&] {

    };

    m_opcodefunset.at(OPCodes::eCP_rHL) = [&] {

    };

    m_opcodefunset.at(OPCodes::eCP_A) = [&] {

    };

    m_opcodefunset.at(OPCodes::eRET_NZ) = [&] {
        if (!(registers().flags.read() & Flags::eZ)) {
            auto& sp = registers().sp;
            registers().pc.write(mmu().readWord(sp.read()));
            sp.inc(0x2);
        }
    };

    m_opcodefunset.at(OPCodes::ePOP_BC) = [&] {
        auto& sp = registers().sp;
        registers().bc.write(mmu().readWord(sp.read()));
        sp.inc(0x2);
    };

    m_opcodefunset.at(OPCodes::eJP_NZ_a16) = [&] {
        if (!(registers().flags.read() & Flags::eZ)) {
            auto& pc = registers().pc;
            auto operand = mmu().readWord(pc.read() + 1);
            pc.write(operand);
        }
    };

    m_opcodefunset.at(OPCodes::eJP_a16) = [&] {
        auto& pc = registers().pc;
        auto operand = mmu().readWord(pc.read() + 1);
        pc.write(operand);
    };

    m_opcodefunset.at(OPCodes::eCALL_NZ_a16) = [&] {
        auto& pc = registers().pc;
        auto operand = mmu().readWord(pc.read() + 1);
        auto& sp = registers().sp;
        
        mmu().writeWord(sp.read(), registers().pc.read());
        
        pc.write(operand);
        sp.dec(0x2);
    };

    m_opcodefunset.at(OPCodes::ePUSH_BC) = [&] {
        auto& sp = registers().sp;

        mmu().writeWord(sp.read(), registers().bc.read());
        
        sp.dec(0x2);
    };

    m_opcodefunset.at(OPCodes::eADD_A_d8) = [&] {
        auto& pc = registers().pc;
        registers().a.inc(mmu().readByte(pc.read() + 1));
    };

    m_opcodefunset.at(OPCodes::eRST_00H) = [&] {
        auto& sp = registers().sp;
        auto& pc = registers().pc;

        mmu().writeWord(sp.read(), pc.read());
        sp.dec(0x2);

        pc.write(0x0);
    };

    m_opcodefunset.at(OPCodes::eRET_Z) = [&] {
        if (registers().flags.read() & Flags::eZ) {
            auto& sp = registers().sp;
            auto& pc = registers().pc;
            pc.write(mmu().readWord(sp.read()));
            sp.inc(0x2);
        }
    };

    m_opcodefunset.at(OPCodes::eRET) = [&] {
        auto& sp = registers().sp;
        auto& pc = registers().pc;
        pc.write(mmu().readWord(sp.read()));
        sp.inc(0x2);
    };

    m_opcodefunset.at(OPCodes::eJP_Z_a16) = [&] {
        if (registers().flags.read() & Flags::eZ) {
            auto& pc = registers().pc;
            pc.write(mmu().readWord(pc.read() + 1));
        }
    };

    m_opcodefunset.at(OPCodes::ePREFIX_CB) = [&] {
    };

    m_opcodefunset.at(OPCodes::eCALL_Z_a16) = [&] {
        if (registers().flags.read() & Flags::eZ) {
            auto& pc = registers().pc;
            auto& sp = registers().sp;

            sp.dec(0x2);
            mmu().writeWord(sp.read(), pc.read());

            auto operand = mmu().readWord(pc.read() + 1);

            pc.write(operand);
        }
    };

    m_opcodefunset.at(OPCodes::eCALL_a16) = [&] {
        auto& pc = registers().pc;
        auto& sp = registers().sp;

        sp.dec(0x2);
        mmu().writeWord(sp.read(), pc.read());

        auto operand = mmu().readWord(pc.read() + 1);

        pc.write(operand);
    };

    m_opcodefunset.at(OPCodes::eADC_A_d8) = [&] {
        auto& pc = registers().pc;

        auto operand = mmu().readByte(pc.read() + 1);

        registers().a.inc(operand + (registers().flags.read() & Flags::eC));
    };

    m_opcodefunset.at(OPCodes::eRST_08H) = [&] {
        auto& sp = registers().sp;
        auto& pc = registers().pc;

        mmu().writeWord(sp.read(), pc.read());
        sp.dec(0x2);

        pc.write(0x8);
    };

    m_opcodefunset.at(OPCodes::eRET_NC) = [&] {
        if (!(registers().flags.read() & Flags::eC)) {
            auto& sp = registers().sp;
            auto& pc = registers().pc;
            pc.write(mmu().readWord(sp.read()));
            sp.inc(0x2);
        }
    };

    m_opcodefunset.at(OPCodes::ePOP_DE) = [&] {
        auto& sp = registers().sp;
        auto& pc = registers().pc;

        registers().de.write( mmu().readWord(sp.read()) );

        sp.inc(0x2);
    };

    m_opcodefunset.at(OPCodes::eJP_NC_a16) = [&] {
        if (!(registers().flags.read() & Flags::eC)) {
            auto& pc = registers().pc;

            auto operand = mmu().readWord(pc.read() + 1);

            registers().pc.write(operand);
        }
    };

    m_opcodefunset.at(OPCodes::eCALL_NC_a16) = [&] {
        if (!(registers().flags.read() & Flags::eC)) {
            auto& pc = registers().pc;
            auto& sp = registers().sp;

            auto operand = mmu().readWord(pc.read() + 1);

            sp.dec(0x2);
            mmu().writeWord(sp.read(), pc.read());

            registers().pc.write(operand);
        }
    };

    m_opcodefunset.at(OPCodes::ePUSH_DE) = [&] {
        auto& sp = registers().sp;
        auto& de = registers().de;

        sp.dec(0x2);

        mmu().writeWord(sp.read(), de.read());
    };

    m_opcodefunset.at(OPCodes::eSUB_d8) = [&] {
        auto& pc = registers().pc;
        auto& a = registers().a;
        auto operand = mmu().readByte(pc.read() + 1);
        a.dec(operand);
    };

    m_opcodefunset.at(OPCodes::eRST_10H) = [&] {
        auto& sp = registers().sp;
        auto& pc = registers().pc;

        mmu().writeWord(sp.read(), pc.read());
        sp.dec(0x2);

        pc.write(0x10);
    };

    m_opcodefunset.at(OPCodes::eRET_C) = [&] {
        if (registers().flags.read() & Flags::eC) {
            auto& pc = registers().pc;
            auto& sp = registers().sp;

            auto retAddr = mmu().readWord(sp.read());
            sp.inc(0x2);

            pc.write(retAddr);
        }
    };
}

Cpu::Cpu(Cartrigbe& cartrigbe) : Cpu()
{
    boot(cartrigbe);
}

MMU& Cpu::mmu() noexcept {
    return m_mmu;
}

void Cpu::boot(Cartrigbe& cartrigbe) 
{
    registers().pc.write(0x1000);
    registers().sp.write(0xFFFE);

    std::memcpy(&m_mmu.memory, cartrigbe.content().data(), cartrigbe.content().size());
    
    m_mmu.memory.cartridgeHeaderArea.validate();

    auto& headers = m_mmu.memory.cartridgeHeaderArea;
    std::cout << headers.m_title << std::endl;
}

Cpu::instructionCall_t& Cpu::decode(OPCodes inst) 
{
    return m_opcodefunset.at(static_cast<std::size_t>(inst));
}

Cpu::OPCodes Cpu::fetch() {
    auto& pc = registers().pc;

    auto inst = m_mmu.readByte(pc.read());

    return static_cast<Cpu::OPCodes>(inst);    
}

Cpu::Status Cpu::status() const noexcept
{
    return m_status;
}

void Cpu::update()
{
    screen().setCoord(sf::Vector2f(static_cast<float>(registers().wndPosX.read()), static_cast<float>(registers().wndPosY.read())));

    screen().getView().move(sf::Vector2f(static_cast<float>(registers().scrollX.read()), static_cast<float>(registers().scrollY.read())));

    auto opcode = fetch();

    std::cout << "exec: " << std::hex << static_cast<size_t>(opcode) << std::endl;

    auto f = decode(opcode);

    f();

    auto pc = registers().pc.read();

    registers().pc.write(pc + 1);

    if (status() == Status::eStop) 
    {
        opcode = static_cast<Cpu::OPCodes>(m_mmu.readByte(pc + 1U));
        
        f = decode(opcode);
        
        f();

        return;
    }    
}

Screen& Cpu::screen() noexcept 
{
    return m_screen;
}