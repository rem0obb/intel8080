// LIBRARY-i8080

/*     ____________________________
      /                           /\
     /   Vitor Mob              _/ /\
    /        Intel8080         / \/
   /                           /\
  /___________________________/ /
  \___________________________\/
   \ \ \ \ \ \ \ \ \ \ \ \ \ \ \
*/

// implementation following the pdfs above, fully commented code for study purposes
// i'm doing an i8080 based implementation i'm changing some flags and registers
// implementation focused on studying how the i8080 logic works
// A sequence of instructions that get together. allow the computer perform a desired task

// References

// http://www.emulator101.com/reference/8080-by-opcode.html
// https://altairclone.com/downloads/manuals/8080%20Programmers%20Manual.pdf
// https://pastraiser.com/cpu/i8080/i8080_opcodes.html
// https://en.wikipedia.org/wiki/FLAGS_register
// http://www.emulator101.com/full-8080-emulation.html
// https://github.com/begoon/i8080-core
// https://en.wikipedia.org/wiki/Intel_8080

// License

//  Copyright (c)  VitorMob 2021 - All rights reserved.

//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:

//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "i8080.hpp"

// cycles intel 8080 variables 4, 5, 7, 10, or 11 cycles
inline static constexpr byte_t cycles_opcode[256] = {

    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4,  
    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4,  
    4, 10, 16, 5,  5,  5,  7,  4,  4, 10, 16, 5,  5,  5,  7, 4,  
    4, 10, 13, 5,  10, 10, 10, 4,  4, 10, 13, 5,  5,  5,  7, 4,  
    
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  
    7, 7,  7,  7,  7,  7,  7,  7,  5, 5,  5,  5,  5,  5,  7, 5,  
    
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  
    
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11, 
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11, 
    5, 10, 10, 18, 11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11, 
    5, 10, 10, 4,  11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11  
    
};

// The Parity bit is set to 1 for even parity, and is reset to 0 for odd parity
inline static bool parity(byte_t n)
{
    word_t p_count = 0;
    for (int i = 0; i <= 8; i++)
        p_count += (n >> i) & 1;

    return !(p_count & 1);
}

// instructions metod in class
void Instructions::push(word_t data16)
{
    SP -= 2;
    memory::write_memory_word(SP, data16);
}

word_t Instructions::pop()
{
    word_t mem = memory::read_memory_word(SP);
    SP += 2;
    return mem;
}

void Instructions::add(word_t data16)
{
    word_t work16 = A + data16;
    A = work16 & 0xff;
    CF = (work16 & 0x100) != 0;
    AC = ((A >> 7) & 0x1) != 1;
    SF = (A & 0x80) != 0;
    ZF = (A == 0);
    PF = parity(A);
}

void Instructions::dad(word_t data16)
{
    CF = ((get_hl() + data16) >> 16) & 1;
    set_hl(get_hl() + data16);
}

void Instructions::sub(word_t data16)
{
    word_t work16 = A - data16;
    A = work16 & 0xff;
    AC = ((A >> 7) & 0x1) != 1;
    CF = (work16 & 0x100) != 0;
    ZF = (A == 0);
    SF = (A & 0x80) != 0;
    PF = parity(A);
}

void Instructions::sbb(word_t data16)
{
    word_t work16 = (A - data16) - CF;
    A = work16 & 0xff;
    AC = ((A >> 7) & 0x1) != 1;
    CF = (work16 & 0x100) != 0;
    ZF = (A == 0);
    SF = (A & 0x80) != 0;
    PF = parity(A);
}

void Instructions::cmp(byte_t data8)
{
    word_t work16 = A - data8;
    CF = work16 >> 8;
    SF = (work16 & 0x80) != 0;
    ZF = (work16 & 0xff) == 0;
    PF = parity(work16 & 0xff);
    AC = ((work16 >> 7) & 0x1) != 1;
}

void Instructions::ana(word_t data16)
{
    byte_t work16 = A & data16;
    CF = work16 >> 8;
    AC = ((A | data16) & 0x08) != 0;
    ZF = (work16 & 0xff) == 0;
    SF = (work16 & 0x80) != 0;
    PF = parity(work16 & 0xff);
    A = work16;
}

void Instructions::ora(word_t data16)
{
    A |= data16;
    CF = 0;
    AC = 0;
    PF = parity(A);
    SF = (A & 0x80) != 0;
    ZF = A == 0;
}

void Instructions::xra(word_t data16)
{
    A ^= data16;
    CF = 0;
    AC = 0;
    PF = parity(A);
    SF = (A & 0x80) != 0;
    ZF = A == 0;
}

void Instructions::ret()
{
    PC = pop();
}

void Instructions::jmp()
{
    PC = memory::read_memory_word(PC);
}

void Instructions::call()
{
    push(PC + 2);
    jmp();
}

void Instructions::rst(word_t addr)
{
    push(PC + 2);
    PC = addr;
}

word_t Instructions::inr(byte_t data16)
{
    word_t work16 = data16 + 1;
    PF = parity(data16);
    SF = (work16 & 0x80) != 0;
    ZF = ((work16 & 0xff) == 0);
    AC = (work16 & 0xf) == 0;

    return work16;
}

word_t Instructions::dcr(byte_t data16)
{
    word_t work16 = data16 - 1;
    PF = parity(data16);
    SF = (work16 & 0x80) != 0;
    ZF = ((work16 & 0xff) == 0);
    AC = !((work16 & 0xf) == 0x0f);

    return work16;
}

void Instructions::daa()
{
    word_t work16 = 0;
    bool flag = 0;
    if (AC || (A & 0xf) > 9)
        work16 |= 0x06;
    if (CF || (A >> 4) > 9 || ((A >> 4) >= 9 && (A & 0x0f) > 9))
    {
        work16 += 0x60;
        flag = 1;
    }
    add(work16);
    CF = flag;
}

void Instructions::xthl()
{
    word_t work16 = memory::read_memory_word(SP);
    memory::write_memory_word(SP, get_hl());
    set_hl(work16);
}

void Instructions::xchg()
{
    word_t work16 = get_de();
    set_de(get_hl());
    set_hl(work16);
}

void Instructions::ral()
{
    bool flag = CF;
    CF = A >> 0x07;
    A = (A << 0x01) | flag;
}

void Instructions::rar()
{
    bool flag = CF;
    CF = A & 0x01;
    A = (A >> 1) | (flag << 7);
}

byte_t Instructions::port_in(byte_t data8)
{
    return EXIT_SUCCESS;
}

void Instructions::port_out(byte_t data8, byte_t val)
{
}

void Instructions::set_bc(word_t data16)
{
    B = data16 >> 8;
    C = data16 & 0xff;
}

void Instructions::set_hl(word_t data16)
{
    H = data16 >> 8;
    L = data16 & 0xff;
}

void Instructions::set_de(word_t data16)
{
    D = data16 >> 8;
    E = data16 & 0xff;
}

word_t Instructions::get_bc()
{
    return (B << 8) | C;
}

word_t Instructions::get_hl()
{
    return (H << 8) | L;
}

word_t Instructions::get_de()
{
    return (D << 8) | E;
}

void i8080::flags_init()
{
    PSW = 0;

    PC = 0, SP = 0;

    A = 0, C = 0, H = 0, L = 0, B = 0, D = 0, E = 0;

    AC = 0, SF = 0, CF = 0, PF = 0, ZF = 0;

    cycles = 0;
}

void i8080::execute_opcode(byte_t opcode) noexcept
{
    cycles += cycles_opcode[opcode];

    switch (opcode)
    {
    // undocumented and nop
    case 0x00:
    case 0x08:
    case 0x10:
    case 0x18:
    case 0x20:
    case 0x28:
    case 0x30:
    case 0x38:
        break;

    case 0x01: // lxi bc
        set_bc(memory::read_memory_word(PC));
        PC += 2;
        break;
    case 0x02: // stax bc
        memory::write_memory_byte(get_bc(), A);
        break;
    case 0x03: // inx b
        set_bc(get_bc() + 1);
        break;
    case 0x04: // inr b
        B = inr(B);
        break;
    case 0x05: // dcr b
        B = dcr(B);
        break;
    case 0x06: // mvi b, d8
        B = memory::read_memory_byte(PC++);
        break;
    case 0x07: // rlc
        CF = (A & 0x80) != 0;
        A = (A << 1) | CF;
        break;
    case 0x09: // dad b
        dad(get_bc());
        break;
    case 0x0a: // ldax b
        A = memory::read_memory_byte(get_bc());
        break;
    case 0x0b: // dcx  bc
        set_bc(get_bc() - 1);
        break;
    case 0x0c: // inr c
        C = inr(C);
        break;
    case 0x0d: // dcr c
        C = dcr(C);
        break;
    case 0x0e: // mvi C, d8
        C = memory::read_memory_byte(PC++);
        break;
    case 0x0f:
        CF = A & 0x01; // rrc
        A = (A >> 1) | (CF << 7);
        break;
    case 0x11: // lxi de
        set_de(memory::read_memory_word(PC));
        PC += 2;
        break;
    case 0x12: // stax de
        memory::write_memory_byte(get_de(), A);
        break;
    case 0x13: // inx de
        set_de(get_de() + 1);
        break;
    case 0x14: // inr d
        D = inr(D);
        break;
    case 0x15: // dcr d
        D = dcr(D);
        break;
    case 0x16: // mvi d, d8
        D = memory::read_memory_byte(PC++);
        break;
    case 0x17: // ral
        ral();
        break;
    case 0x19: // dad d
        dad(get_de());
        break;
    case 0x1a: // ldax d
        A = memory::read_memory_byte(get_de());
        break;
    case 0x1b: // dcx de
        set_de(get_de() - 1);
        break;
    case 0x1c: // inr e
        E = inr(E);
        break;
    case 0x1d: // dcr e
        E = dcr(E);
        break;
    case 0x1e: // mvi e, d8
        E = memory::read_memory_byte(PC++);
        break;
    case 0x1f: // rar
        rar();
        break;
    case 0x21: // lxi hl
        set_hl(memory::read_memory_word(PC));
        PC += 2;
        break;
    case 0x22: // shld
        memory::write_memory_word(memory::read_memory_word(PC), get_hl());
        PC += 2;
        break;
    case 0x23: // inx h
        set_hl(get_hl() + 1);
        break;
    case 0x24: // inr H
        H = inr(H);
        break;
    case 0x25: // dcr H
        H = dcr(H);
        break;
    case 0x26: // mvi h, d8
        H = memory::read_memory_byte(PC++);
        break;
    case 0x27: // daa
        daa();
        break;
    case 0x29: // dad h
        dad(get_hl());
        break;
    case 0x2a: // lhld
        set_hl(memory::read_memory_word(memory::read_memory_word(PC)));
        PC += 2;
        break;
    case 0x2b: // dcx h
        set_hl(get_hl() - 1);
        break;
    case 0x2c: // inr l
        L = inr(L);
        break;
    case 0x2d: // dcr l
        L = dcr(L);
        break;
    case 0x2e: // mvi l, d8
        L = memory::read_memory_byte(PC++);
        break;
    case 0x2f: // cma, if A = 51H converting for aeh
        A = ~A;
        break;
    case 0x31: // lxi sp
        SP = memory::read_memory_word(PC);
        PC += 2;
        break;
    case 0x32: // sta addr
        memory::write_memory_byte(memory::read_memory_word(PC), A);
        PC += 2;
        break;
    case 0x33: // inx sp
        SP++;
        break;
    case 0x34:
        memory::write_memory_word(get_hl(), inr(memory::read_memory_byte(get_hl())));
        break;
    case 0x35:
        memory::write_memory_word(get_hl(), dcr(memory::read_memory_byte(get_hl())));
        break;
    case 0x36: // mvi h, d8
        memory::write_memory_byte(get_hl(), memory::read_memory_byte(PC));
        PC++;
        break;
    case 0x37:
        CF = 1;
        break;
    case 0x39:
        dad(SP);
        break;
    case 0x3a: // lda adr
        A = memory::read_memory_byte(memory::read_memory_word(PC));
        PC += 2;
        break;
    case 0x3b:
        SP -= 1; // dcx sp
        break;
    case 0x3c:
        A = inr(A);
        break;
    case 0x3d:
        A = dcr(A);
        break;
    case 0x3e: // mvi a, d8
        A = memory::read_memory_byte(PC++);
        break;
    case 0x3f: // cmc
        CF = !CF;
        break;
    case 0x40:
        B = B;
        break;
    case 0x41:
        B = C;
        break;
    case 0x42:
        B = D;
        break;
    case 0x43:
        B = E;
        break;
    case 0x44:
        B = H;
        break;
    case 0x45:
        B = L;
        break;
    case 0x46:
        B = memory::read_memory_byte(get_hl());
        break;
    case 0x47:
        B = A;
        break;
    case 0x48:
        C = B;
        break;
    case 0x49:
        C = C;
        break;
    case 0x4a:
        C = D;
        break;
    case 0x4b:
        C = E;
        break;
    case 0x4c:
        C = H;
        break;
    case 0x4d:
        C = L;
        break;
    case 0x4e:
        C = memory::read_memory_byte(get_hl());
        break;
    case 0x4f:
        C = A;
        break;
    case 0x50:
        D = B;
        break;
    case 0x51:
        D = C;
        break;
    case 0x52:
        D = D;
        break;
    case 0x53:
        D = E;
        break;
    case 0x54:
        D = H;
        break;
    case 0x55:
        D = L;
        break;
    case 0x56:
        D = memory::read_memory_byte(get_hl());
        break;
    case 0x57:
        D = A;
        break;
    case 0x58:
        E = B;
        break;
    case 0x59:
        E = C;
        break;
    case 0x5a:
        E = D;
        break;
    case 0x5b:
        E = E;
        break;
    case 0x5c:
        E = H;
        break;
    case 0x5d:
        E = L;
        break;
    case 0x5e:
        E = memory::read_memory_byte(get_hl());
        break;
    case 0x5f:
        E = A;
        break;
    case 0x60:
        H = B;
        break;
    case 0x61:
        H = C;
        break;
    case 0x62:
        H = D;
        break;
    case 0x63:
        H = E;
        break;
    case 0x64:
        H = H;
        break;
    case 0x65:
        H = L;
        break;
    case 0x66:
        H = memory::read_memory_byte(get_hl());
        break;
    case 0x67:
        H = A;
        break;
    case 0x68:
        L = B;
        break;
    case 0x69:
        L = C;
        break;
    case 0x6a:
        L = D;
        break;
    case 0x6b:
        L = E;
        break;
    case 0x6c:
        L = H;
        break;
    case 0x6d:
        L = L;
        break;
    case 0x6e:
        L = memory::read_memory_byte(get_hl());
        break;
    case 0x6f:
        L = A;
        break;
    case 0x70:
        memory::write_memory_byte(get_hl(), B);
        break;
    case 0x71:
        memory::write_memory_byte(get_hl(), C);
        break;
    case 0x72:
        memory::write_memory_byte(get_hl(), D);
        break;
    case 0x73:
        memory::write_memory_byte(get_hl(), E);
        break;
    case 0x74:
        memory::write_memory_byte(get_hl(), H);
        break;
    case 0x75:
        memory::write_memory_byte(get_hl(), L);
        break;
    case 0x76:
        break; // not implemented hlt
    case 0x77:
        memory::write_memory_byte(get_hl(), A);
        break;
    case 0x78:
        A = B;
        break;
    case 0x79:
        A = C;
        break;
    case 0x7a:
        A = D;
        break;
    case 0x7b:
        A = E;
        break;
    case 0x7c:
        A = H;
        break;
    case 0x7d:
        A = L;
        break;
    case 0x7e:
        A = memory::read_memory_byte(get_hl());
        break;
    case 0x7f:
        A = A;
        break;
    case 0x80:
        add(B);
        break;
    case 0x81:
        add(C);
        break;
    case 0x82:
        add(D);
        break;
    case 0x83:
        add(E);
        break;
    case 0x84:
        add(H);
        break;
    case 0x85:
        add(L);
        break;
    case 0x86:
        add(memory::read_memory_byte(get_hl()));
        break;
    case 0x87:
        add(A);
        break;
    case 0x88:
        add(B + CF);
        break;
    case 0x89:
        add(C + CF);
        break;
    case 0x8a:
        add(D + CF);
        break;
    case 0x8b:
        add(E + CF);
        break;
    case 0x8c:
        add(H + CF);
        break;
    case 0x8d:
        add(L + CF);
        break;
    case 0x8e:
        add(memory::read_memory_byte(get_hl()) + CF);
        break;
    case 0x8f:
        add(A + CF);
        break;
    case 0x90:
        sub(B);
        break;
    case 0x91:
        sub(C);
        break;
    case 0x92:
        sub(D);
        break;
    case 0x93:
        sub(E);
        break;
    case 0x94:
        sub(H);
        break;
    case 0x95:
        sub(L);
        break;
    case 0x96:
        sub(memory::read_memory_byte(get_hl()));
        break;
    case 0x97:
        sub(A);
        break;
    case 0x98:
        sbb(B);
        break;
    case 0x99:
        sbb(C);
        break;
    case 0x9a:
        sbb(D);
        break;
    case 0x9b:
        sbb(E);
        break;
    case 0x9c:
        sbb(H);
        break;
    case 0x9d:
        sbb(L);
        break;
    case 0x9e:
        sbb(memory::read_memory_byte(get_hl()));
        break;
    case 0x9f:
        sbb(A);
        break;
    case 0xa0:
        ana(B);
        break;
    case 0xa1:
        ana(C);
        break;
    case 0xa2:
        ana(D);
        break;
    case 0xa3:
        ana(E);
        break;
    case 0xa4:
        ana(H);
        break;
    case 0xa5:
        ana(L);
        break;
    case 0xa6:
        ana(memory::read_memory_byte(get_hl()));
        break;
    case 0xa7:
        ana(A);
        break;
    case 0xa8:
        xra(B);
        break;
    case 0xa9:
        xra(C);
        break;
    case 0xaa:
        xra(D);
        break;
    case 0xab:
        xra(E);
        break;
    case 0xac:
        xra(H);
        break;
    case 0xad:
        xra(L);
        break;
    case 0xae:
        xra(memory::read_memory_byte(get_hl()));
        break;
    case 0xaf:
        xra(A);
        break;
    case 0xb0:
        ora(B);
        break;
    case 0xb1:
        ora(C);
        break;
    case 0xb2:
        ora(D);
        break;
    case 0xb3:
        ora(E);
        break;
    case 0xb4:
        ora(H);
        break;
    case 0xb5:
        ora(L);
        break;
    case 0xb6:
        ora(memory::read_memory_byte(get_hl()));
        break;
    case 0xb7:
        ora(A);
        break;
    case 0xb8:
        cmp(B);
        break;
    case 0xb9:
        cmp(C);
        break;
    case 0xba:
        cmp(D);
        break;
    case 0xbb:
        cmp(E);
        break;
    case 0xbc:
        cmp(H);
        break;
    case 0xbd:
        cmp(L);
        break;
    case 0xbe:
        cmp(memory::read_memory_byte(get_hl()));
        break;
    case 0xbf:
        cmp(A);
        break;
    case 0xc0:
        if (!ZF)
            ret();
        break;
    case 0xc1:
        set_bc(pop());
        break;
    case 0xc2: // jnz
        if (!ZF)
            jmp();
        else
            PC += 2;
        break;
    case 0xc3:
        jmp();
        break;
    case 0xc4:
        if (!ZF)
            call();
        else
            PC += 2;
        break;
    case 0xc5:
        push(get_bc());
        break;
    case 0xc6:
        add(memory::read_memory_byte(PC++));
        break;
    case 0xc7:
        rst(0x00);
        break;
    case 0xc8: // rz
        if (ZF)
            ret();
        break;
    case 0xc9:
        ret(); // ret
        break;
    case 0xca:
        if (ZF)
            jmp();
        else
            PC += 2;
        break;
    case 0xcb:
        jmp();
        break;
    case 0xcc:
        if (ZF)
            call();
        else
            PC += 2;
        break;
    case 0xcd:
        call();
        break;
    case 0xce:
        add(memory::read_memory_byte(PC++) + CF);
        break;
    case 0xcf:
        rst(0x08);
        break;
    case 0xd0:
        if (!CF)
            ret();
        break;
    case 0xd1:
        set_de(pop());
        break;
    case 0xd2: // jnc
        if (!CF)
            jmp();
        else
            PC += 2;
        break;
    case 0xd3:
        port_out(memory::read_memory_byte(PC++), A);
        break;
    case 0xd4:
        if (!CF)
            call();
        else
            PC += 2;
        break;
    case 0xd5:
        push(get_de());
        break;
    case 0xd6:
        sub(memory::read_memory_byte(PC++));
        break;
    case 0xd7:
        rst(0x10);
        break;
    case 0xd8:
        if (CF)
            ret();
        break;
    case 0xd9:
        ret();
        break;
    case 0xda:
        if (CF)
            jmp();
        else
            PC += 2;
        break;
    case 0xdb:
        A = port_in(memory::read_memory_byte(PC++));
        break;
    case 0xdc: // cc
        if (CF)
            call();
        else
            PC += 2;
        break;
    case 0xdd:
        call();
        break;
    case 0xde:
        sbb(memory::read_memory_byte(PC++));
        break;
    case 0xdf:
        rst(0x18);
        break;
    case 0xe0:
        if (!PF)
            ret();
        break;
    case 0xe1:
        set_hl(pop());
        break;
    case 0xe2: // jpo
        if (!PF)
            jmp();
        else
            PC += 2;
        break;
    case 0xe3: // xthl
        xthl();
        break;
    case 0xe4: // cpo
        if (!PF)
            call();
        else
            PC += 2;
        break;
    case 0xe5:
        push(get_hl());
        break;
    case 0xe6:
        ana(memory::read_memory_byte(PC++));
        break;
    case 0xe7:
        rst(0x20);
        break;
    case 0xe8:
        if (PF)
            ret();
        break;
    case 0xe9:
        PC = get_hl(); // pchl
        break;
    case 0xea: // jpe
        if (PF)
            jmp();
        else
            PC += 2;
        break;
    case 0xeb: // xchg
        xchg();
        break;
    case 0xec:
        if (PF)
            call();
        else
            PC += 2;
        break;
    case 0xed:
        call();
        break;
    case 0xee:
        xra(memory::read_memory_byte(PC++));
        break;
    case 0xef:
        rst(0x28);
        break;
    case 0xf0:
        if (!SF)
            ret();
        break;
    case 0xf1:
        AF = pop();
        A = AF >> 8;
        PSW = AF & 0xff;
        SF = ((PSW >> 0x7) & 0x1);
        ZF = ((PSW >> 0x6) & 0x1);
        AC = ((PSW >> 0x4) & 0x1);
        PF = ((PSW >> 0x2) & 0x1);
        CF = ((PSW >> 0x0) & 0x1);
        break;
    case 0xf2:
        if (!SF)
            jmp();
        else
            PC += 2;
        break;
    case 0xf3: // di
        break; // not implemented
    case 0xf4:
        if (!SF)
            call();
        else
            PC += 2;
        break;
    case 0xf5:
        PSW |= SF << 0x7;
        PSW |= ZF << 0x6;
        PSW |= AC << 0x4;
        PSW |= PF << 0x2;
        PSW |= CF << 0x0;
        push(A << 8 | PSW);
        break;
    case 0xf6:
        ora(memory::read_memory_byte(PC++));
        break;
    case 0xf7:
        rst(0x30);
        break;
    case 0xf8: // rm
        if (SF)
            ret();
        break;
    case 0xf9: // sphl
        SP = get_hl();
        break;
    case 0xfa:
        if (SF)
            jmp();
        else
            PC += 2;
        break;
    case 0xfb: // ei
        break; // not implemented
    case 0xfc:
        if (SF)
            call();
        else
            PC += 2;
        break;
    case 0xfe:
        cmp(memory::read_memory_byte(PC++));
        break;
    case 0xff:
        rst(0x38);
        break;
    case 0xfd:
        call();
        break;
    default:
        std::cout << "*** Instruction not implemented " << memory::memory[PC] << std::endl;
    }
}

byte_t i8080::get_register_c()
{
    return C;
}

word_t i8080::get_pc()
{
    return PC;
}

word_t i8080::get_register_hl()
{
    return get_hl();
}

word_t i8080::get_register_bc()
{
    return get_bc();
}

byte_t i8080::get_register_e()
{
    return E;
}

word_t i8080::get_register_de()
{
    return get_de();
}

byte_t i8080::get_register_d()
{
    return D;
}

byte_t i8080::get_register_b()
{
    return B;
}

byte_t i8080::get_register_l()
{
    return L;
}

byte_t i8080::get_register_h()
{
    return H;
}

int i8080::get_cycles()
{
    return cycles;
}

byte_t *i8080::memory_addr()
{
    return memory::memory;
}

signed i8080::get_size_mem()
{
    return size_mem;
}

void i8080::load_file_bin(std::string name, byte_t *load, word_t jump)
{
    std::fstream file(name, std::ios::binary);
    memset(memory::memory, 0, MAX_MEMORY);

    try
    {
        if(MAX_MEMORY != 0x10000L)
            throw std::runtime_error("Memory not supported, memory intel this suport 65536d");

        size_mem = 0;
        PC = jump;

        file.open(name);
        if (file.is_open())
        {
            if (file.peek() == std::ifstream::traits_type::eof())
                throw std::runtime_error("File " + name + " empty");

            while (!file.eof())
            {
                file.read((char *)load + PC, 1028);
                size_mem += file.gcount();
                load += file.gcount();
            }
            std::cout << "******************************************************" << std::endl
                      << "*** File " << name << std::endl
                      << "*** Size " << size_mem << " bytes" << std::endl
                      << "*** Jumped 0x" << std::hex << PC << std::endl
                      << std::endl;
        }
        else
            throw std::runtime_error("File not found or not permission for reading");
    }
    catch (std::exception &error)
    {
        std::cerr << "*** Error " << error.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    file.close();
}

void i8080::i8080_instructions()
{
    byte_t opcode = memory::read_memory_byte(PC++);
    execute_opcode(opcode);
}

Microprocessor::Microprocessor()
{
    flags_init();
}

Microprocessor::~Microprocessor()
{
}