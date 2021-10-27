/*     ____________________________
      /                           /\
     /   Vitor Mob              _/ /\
    /        Disassembly       / \/
   /                           /\
  /___________________________/ /
  \___________________________\/
   \ \ \ \ \ \ \ \ \ \ \ \ \ \ \
*/

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

#ifndef disass_h
#define disass_h

#include <iostream>
#include <fstream>
#include <sstream>

#include "i8080.hpp"

#define __file_disass__ "src/intel8080/utils/disassembly.asm"
#define __file_mem__ "src/intel8080/utils/memory.bin"
#define MAX_MEMORY 0x10000

typedef uint16_t word_t;
typedef uint8_t byte_t;

class Disassembly
{
private:
    std::string execute_opcode(byte_t __opcode, word_t __pc);
    byte_t read_memory(word_t __addr, byte_t *__mem);
    void file_save_disass(byte_t __opcode, word_t __pc);

public:
    std::ofstream file_disass;
    std::ofstream file_mem;

    void create_file();
    Disassembly();
    ~Disassembly();
    void run_disassembly(word_t __pc, byte_t *__mem);
    void run_memory(byte_t *__mem, signed __size);
};

#endif // ! disass_h