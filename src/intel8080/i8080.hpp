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

#ifndef i8080_h
#define i8080_h

#include <fstream>
#include <iostream>
#include <cstring>

#define MAX_MEMORY 0x10000
#define PORT_OUT 0

typedef uint16_t word_t;
typedef uint8_t byte_t;

namespace memory
{
    inline byte_t memory[MAX_MEMORY];

    inline byte_t read_memory_byte(word_t addr)
    {
        return memory[addr];
    }

    inline word_t read_memory_word(word_t addr)
    {
        return read_memory_byte(addr + 1) << 8 |
               read_memory_byte(addr);
    }

    inline void write_memory_byte(word_t addr, byte_t data16)
    {
        memory[addr] = data16;
    }

    inline void write_memory_word(word_t addr, word_t data16)
    {
        memory::write_memory_byte(addr, data16);
        memory::write_memory_byte(addr + 1, data16 >> 8);
    }
}

typedef class instructions
{
    protected:
        signed size_mem;
        // program status word
        byte_t PSW;

        // program counter, stack pointer
        word_t PC, SP, AF;

        // registers
        byte_t A, C, H, L, B, D, E, V;
        word_t BC, HL, DE; //  pairs of registers

        // flags
        bool AC, SF, CF, PF, ZF;

        // variables to save results and retrieve
        int cycles; // count cycles 
        word_t data16;
        byte_t data8;
        bool flags;

        // stack manipulation
        void push(word_t data16);
        word_t pop();

        // instructions
        void add(word_t data16);
        void dad(word_t data16);
        void sub(word_t data16);
        void sbb(word_t data16);
        void cmp(byte_t data8);
        void ana(word_t data16);
        void ora(word_t data16);
        void xra(word_t data16);
        void ret();
        void jmp();
        void call();
        void rst(word_t addr);
        word_t inr(word_t data16);
        word_t dcr(word_t data16);

        void port_out(byte_t data8, byte_t val);
        byte_t port_in(byte_t data8);

        void set_bc(word_t data16);
        void set_hl(word_t data16);
        void set_de(word_t data16);
        word_t get_bc();
        word_t get_hl();
        word_t get_de();        

} Instructions;

typedef class Microprocessor : protected Instructions
{
    private:
        void flags_init();
        void execute_opcode(byte_t opcode);

    public:
        byte_t get_register_c();
        word_t get_pc();
        word_t get_register_hl();
        word_t get_register_bc();
        byte_t get_register_e();
        word_t get_register_de();
        byte_t get_register_d();
        byte_t get_register_b();
        byte_t get_register_l();
        byte_t get_register_h();
        int get_cycles();
        signed get_size_mem();
        byte_t *memory_addr();

        void load_file_bin(std::string name, byte_t *load, word_t jump);
        void i8080_instructions();

        Microprocessor();
        ~Microprocessor();

} i8080;

#endif // i8080_h
