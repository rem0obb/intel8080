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
//  of this software and associated documentation return he "Software", to deal
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

#include "disassembly.hpp"

std::string Disassembly::execute_opcode(byte_t __opcode, word_t __pc)
{
    std::stringstream instruction_str;
    switch (__opcode)
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

        case 0x01:
            instruction_str << "lxi b, d16";
            break;
        case 0x02:
            instruction_str << "stax b";
            break;
        case 0x03:
            instruction_str << "inx b";
            break;
        case 0x04:
            instruction_str << "inr b";
            break;
        case 0x05:
            instruction_str << "dcr b";
            break;
        case 0x06:
            instruction_str << "mvi b, d8";
            break;
        case 0x07:
            instruction_str << "rlc";
            break;
        case 0x09:
            instruction_str << "dad b";
            break;
        case 0x0a:
            instruction_str << "ldax b";
            break;
        case 0x0b:
            instruction_str << "dcx b";
            break;
        case 0x0c:
            instruction_str << "inr c";
            break;
        case 0x0d:
            instruction_str << "dcr c";
            break;
        case 0x0e:
            instruction_str << "mvi c, d18";
            break;
        case 0x0f:
            instruction_str << "rrc";
            break;
        case 0x11:
            instruction_str << "lxi d16";
            break;
        case 0x12:
            instruction_str << "stax d";
            break;
        case 0x13:
            instruction_str << "inx de";
            break;
        case 0x14:
            instruction_str << "inx d";
            break;
        case 0x15:
            instruction_str << "dcr d";
            break;
        case 0x16:
            instruction_str << "mvi d, d8";
            break;
        case 0x17:
            instruction_str << "ral";
            break;
        case 0x19:
            instruction_str << "dad d";
            break;
        case 0x1a:
            instruction_str << "lax d";
            break;
        case 0x1b:
            instruction_str << "inr d";
            break;
        case 0x1c:
            instruction_str << "inr e";
            break;
        case 0x1d:
            instruction_str << "dcr e";
            break;
        case 0x1e:
            instruction_str << "mvi e, d8";
            break;
        case 0x1f:
            instruction_str << "rar";
            break;
        case 0x21:
            instruction_str << "lxi hl";
            break;
        case 0x22:
            instruction_str << "shld";
            break;
        case 0x23:
            instruction_str << "inx h";
            break;
        case 0x24:
            instruction_str << "inr h";
            break;
        case 0x25:
            instruction_str << "dcr h";
            break;
        case 0x26:
            instruction_str << "mvi h, d8";
            break;
        case 0x27:
            instruction_str << "daa";
            break;
        case 0x29:
            instruction_str << "dad h";
            break;
        case 0x2a:
            instruction_str << "lhld";
            break;
        case 0x2b:
            instruction_str << "dcx h";
            break;
        case 0x2c:
            instruction_str << "inr l";
            break;
        case 0x2d:
            instruction_str << "dcr l";
            break;
        case 0x2e:
            instruction_str << "mvi l, d8";
            break;
        case 0x2f:
            instruction_str << "cma";
            break;
        case 0x31:
            instruction_str << "lxi sp";
            break;
        case 0x32:
            instruction_str << "sta addr";
            break;
        case 0x33:
            instruction_str << "inx sp";
            break;
        case 0x34:
            instruction_str << "inr m";
            break;
        case 0x35:
            instruction_str << "dcr m";
            break;
        case 0x36:
            instruction_str << "mvi m, d8";
            break;
        case 0x37:
            instruction_str << "stc";
            break;
        case 0x39:
            instruction_str << "dad sp";
            break;
        case 0x3a:
            instruction_str << "lda adr";
            break;
        case 0x3b:
            instruction_str << "dcx sp";
            break;
        case 0x3c:
            instruction_str << "inr a";
            break;
        case 0x3d:
            instruction_str << "dcr a";
            break;
        case 0x3e:
            instruction_str << "mvi a, d8";
            break;
        case 0x3f:
            instruction_str << "cmc";
            break;
        case 0x40:
            instruction_str << "mov b, b";
            break;
        case 0x41:
            instruction_str << "mov b, c";
            break;
        case 0x42:
            instruction_str << "mov b, d";
            break;
        case 0x43:
            instruction_str << "mov b, e";
            break;
        case 0x44:
            instruction_str << "mov b, h";
            break;
        case 0x45:
            instruction_str << "mov b, l";
            break;
        case 0x46:
            instruction_str << "mov b, hl";
            break;
        case 0x47:
            instruction_str << "mov b, a";
            break;
        case 0x48:
            instruction_str << "mov c, b";
            break;
        case 0x49:
            instruction_str << "mov c, c";
            break;
        case 0x4a:
            instruction_str << "mov c, d";
            break;
        case 0x4b:
            instruction_str << "mov c, e";
            break;
        case 0x4c:
            instruction_str << "mov c, h";
            break;
        case 0x4d:
            instruction_str << "mov c, l";
            break;
        case 0x4e:
            instruction_str << "mov c, hl";
            break;
        case 0x4f:
            instruction_str << "mov c, a";
            break;
        case 0x50:
            instruction_str << "mov d, b";
            break;
        case 0x51:
            instruction_str << "mov d, c";
            break;
        case 0x52:
            instruction_str << "mov d, d";
            break;
        case 0x53:
            instruction_str << "mov d, e";
            break;
        case 0x54:
            instruction_str << "mov d, h";
            break;
        case 0x55:
            instruction_str << "mov d, l";
            break;
        case 0x56:
            instruction_str << "mov d, hl";
            break;
        case 0x57:
            instruction_str << "mov d, a";
            break;
        case 0x58:
            instruction_str << "mov e, b";
            break;
        case 0x59:
            instruction_str << "mov e, c";
            break;
        case 0x5a:
            instruction_str << "mov e, d";
            break;
        case 0x5b:
            instruction_str << "mov e, e";
            break;
        case 0x5c:
            instruction_str << "mov e, h";
            break;
        case 0x5d:
            instruction_str << "mov e, l";
            break;
        case 0x5e:
            instruction_str << "mov e, hl";
            break;
        case 0x5f:
            instruction_str << "mov e, a";
            break;
        case 0x60:
            instruction_str << "mov h, b";
            break;
        case 0x61:
            instruction_str << "mov h, c";
            break;
        case 0x62:
            instruction_str << "mov h, d";
            break;
        case 0x63:
            instruction_str << "mov h, e";
            break;
        case 0x64:
            instruction_str << "mov h, h";
            break;
        case 0x65:
            instruction_str << "mov h, l";
            break;
        case 0x66:
            instruction_str << "mov h, hl";
            break;
        case 0x67:
            instruction_str << "mov h, a";
            break;
        case 0x68:
            instruction_str << "mov l, b";
            break;
        case 0x69:
            instruction_str << "mov l, c";
            break;
        case 0x6a:
            instruction_str << "mov l, d";
            break;
        case 0x6b:
            instruction_str << "mov l, e";
            break;
        case 0x6c:
            instruction_str << "mov l, h";
            break;
        case 0x6d:
            instruction_str << "mov l, l";
            break;
        case 0x6e:
            instruction_str << "mov l, hl";
            break;
        case 0x6f:
            instruction_str << "mov l, a";
            break;
        case 0x70:
            instruction_str << "mov hl, b";
            break;
        case 0x71:
            instruction_str << "mov hl, c";
            break;
        case 0x72:
            instruction_str << "mov hl, d";
            break;
        case 0x73:
            instruction_str << "mov hl, e";
            break;
        case 0x74:
            instruction_str << "mov hl, h";
            break;
        case 0x75:
            instruction_str << "mov hl, l";
            break;
        case 0x76:
            instruction_str << "hlt";
            break;
        case 0x77:
            instruction_str << "mov hl, a";
            break;
        case 0x78:
            instruction_str << "mov a, b";
            break;
        case 0x79:
            instruction_str << "mov a, c";
            break;
        case 0x7a:
            instruction_str << "mov a, d";
            break;
        case 0x7b:
            instruction_str << "mov a, e";
            break;
        case 0x7c:
            instruction_str << "mov a, h";
            break;
        case 0x7d:
            instruction_str << "mov a, l";
            break;
        case 0x7e:
            instruction_str << "mov a, hl";
            break;
        case 0x7f:
            instruction_str << "mov a, a";
            break;
        case 0x80:
            instruction_str << "add b";
            break;
        case 0x81:
            instruction_str << "add c";
            break;
        case 0x82:
            instruction_str << "add d";
            break;
        case 0x83:
            instruction_str << "add e";
            break;
        case 0x84:
            instruction_str << "add h";
            break;
        case 0x85:
            instruction_str << "add l";
            break;
        case 0x86:
            instruction_str << "add hl";
            break;
        case 0x87:
            instruction_str << "add a";
            break;
        case 0x88:
            instruction_str << "adc b";
            break;
        case 0x89:
            instruction_str << "adc c";
            break;
        case 0x8a:
            instruction_str << "adc d";
            break;
        case 0x8b:
            instruction_str << "adc e";
            break;
        case 0x8c:
            instruction_str << "adc h";
            break;
        case 0x8d:
            instruction_str << "adc l";
            break;
        case 0x8e:
            instruction_str << "adc hl";
            break;
        case 0x8f:
            instruction_str << "adc a";
            break;
        case 0x90:
            instruction_str << "sub b";
            break;
        case 0x91:
            instruction_str << "sub c";
            break;
        case 0x92:
            instruction_str << "sub d";
            break;
        case 0x93:
            instruction_str << "sub e";
            break;
        case 0x94:
            instruction_str << "sub h";
            break;
        case 0x95:
            instruction_str << "sub l";
            break;
        case 0x96:
            instruction_str << "sub hl";
            break;
        case 0x97:
            instruction_str << "sbb a";
            break;
        case 0x98:
            instruction_str << "sbb b";
            break;
        case 0x99:
            instruction_str << "sbb c";
            break;
        case 0x9a:
            instruction_str << "sbb d";
            break;
        case 0x9b:
            instruction_str << "sbb e";
            break;
        case 0x9c:
            instruction_str << "sbb h";
            break;
        case 0x9d:
            instruction_str << "sbb l";
            break;
        case 0x9e:
            instruction_str << "sbb hl";
            break;
        case 0x9f:
            instruction_str << "sbb a";
            break;
        case 0xa0:
            instruction_str << "ana b";
            break;
        case 0xa1:
            instruction_str << "ana c";
            break;
        case 0xa2:
            instruction_str << "ana d";
            break;
        case 0xa3:
            instruction_str << "ana e";
            break;
        case 0xa4:
            instruction_str << "ana h";
            break;
        case 0xa5:
            instruction_str << "ana l";
            break;
        case 0xa6:
            instruction_str << "ana hl";
            break;
        case 0xa7:
            instruction_str << "ana a";
            break;
        case 0xa8:
            instruction_str << "xra b";
            break;
        case 0xa9:
            instruction_str << "xra c";
            break;
        case 0xaa:
            instruction_str << "xra d";
            break;
        case 0xab:
            instruction_str << "xra e";
            break;
        case 0xac:
            instruction_str << "xra h";
            break;
        case 0xad:
            instruction_str << "xra l";
            break;
        case 0xae:
            instruction_str << "xra hl";
            break;
        case 0xaf:
            instruction_str << "xra a";
            break;
        case 0xb0:
            instruction_str << "ora b";
            break;
        case 0xb1:
            instruction_str << "ora c";
            break;
        case 0xb2:
            instruction_str << "ora d";
            break;
        case 0xb3:
            instruction_str << "ora e";
            break;
        case 0xb4:
            instruction_str << "ora h";
            break;
        case 0xb5:
            instruction_str << "ora l";
            break;
        case 0xb6:
            instruction_str << "ora hl";
            break;
        case 0xb7:
            instruction_str << "ora a";
            break;
        case 0xb8:
            instruction_str << "cmp b";
            break;
        case 0xb9:
            instruction_str << "cmp c";
            break;
        case 0xba:
            instruction_str << "cmp bd";
            break;
        case 0xbb:
            instruction_str << "cmp e";
            break;
        case 0xbc:
            instruction_str << "cmp h";
            break;
        case 0xbd:
            instruction_str << "cmp l";
            break;
        case 0xbe:
            instruction_str << "cmp hl";
            break;
        case 0xbf:
            instruction_str << "cmp a";
            break;
        case 0xc0:
            instruction_str << "rnz";
            break;
        case 0xc1:
            instruction_str << "pop b";
            break;
        case 0xc2: // jnz
            instruction_str << "jnz addr";
            break;
        case 0xc3:
            instruction_str << "jmp";
            break;
        case 0xc4:
            instruction_str << "cnz";
            break;
        case 0xc5:
            instruction_str << "push bc";
            break;
        case 0xc6:
            instruction_str << "adi  d8";
            break;
        case 0xc7:
            instruction_str << "rst 0x00";
            break;
        case 0xc8:
            instruction_str << "rz";
            break;
        case 0xc9:
            instruction_str << "ret";
            break;
        case 0xca:
            instruction_str << "jz addr";
            break;
        case 0xcb:
            instruction_str << "jmp";
            break;
        case 0xcc:
            instruction_str << "cz addr";
            break;
        case 0xcd:
            instruction_str << "call addr";
            break;
        case 0xce:
            instruction_str << "aci d8";
            break;
        case 0xcf:
            instruction_str << "rst 0x01";
            break;
        case 0xd0:
            instruction_str << "rnc";
            break;
        case 0xd1:
            instruction_str << "pop de";
            break;
        case 0xd2:
            instruction_str << "jnc addr";
            break;
        case 0xd3:
            instruction_str << "out d8";
            break;
        case 0xd4:
            instruction_str << "cnc addr";
            break;
        case 0xd5:
            instruction_str << "push de";
            break;
        case 0xd6:
            instruction_str << "sui d8";
            break;
        case 0xd7:
            instruction_str << "rst 0x10";
            break;
        case 0xd8:
            instruction_str << "rc";
            break;
        case 0xd9:
            instruction_str << "ret";
            break;
        case 0xda:
            instruction_str << "jc addr";
            break;
        case 0xdb:
            instruction_str << "in d8";
            break;
        case 0xdc:
            instruction_str << "cc addr";
            break;
        case 0xdd:
            instruction_str << "call";
            break;
        case 0xde:
            instruction_str << "sbi d8";
            break;
        case 0xdf:
            instruction_str << "rst 0x18";
            break;
        case 0xe0:
            instruction_str << "rpo";
            break;
        case 0xe1:
            instruction_str << "pop hl";
            break;
        case 0xe2:
            instruction_str << "jpo addr";
            break;
        case 0xe3:
            instruction_str << "xthl";
            break;
        case 0xe4:
            instruction_str << "cpo";
            break;
        case 0xe5:
            instruction_str << "push hl";
            break;
        case 0xe6:
            instruction_str << "ani d8";
            break;
        case 0xe7:
            instruction_str << "rst 0x20";
            break;
        case 0xe8:
            instruction_str << "rpe";
            break;
        case 0xe9:
            instruction_str << "pchl";
            break;
        case 0xea:
            instruction_str << "jpe";
            break;
        case 0xeb:
            instruction_str << "xchg";
            break;
        case 0xec:
            instruction_str << "cpe addr";
            break;
        case 0xed:
            instruction_str << "call";
            break;
        case 0xee:
            instruction_str << "xra d8";
            break;
        case 0xef:
            instruction_str << "rst 0x28";
            break;
        case 0xf0:
            instruction_str << "rp";
            break;
        case 0xf1:
            instruction_str << "pop psw";
            break;
        case 0xf2:
            instruction_str << "jp addr";
            break;
        case 0xf3:
            instruction_str << "di";
            break;
        case 0xf4:
            instruction_str << "cp addr";
            break;
        case 0xf5:
            instruction_str << "push psw";
            break;
        case 0xf6:
            instruction_str << "ori d8";
            break;
        case 0xf7:
            instruction_str << "rst 30";
            break;
        case 0xf8:
            instruction_str << "rm";
            break;
        case 0xf9:
            instruction_str << "sphl";
            break;
        case 0xfa:
            instruction_str << "jm addr";
            break;
        case 0xfb:
            instruction_str << "ei";
            break;
        case 0xfc:
            instruction_str << "cm addr";
            break;
        case 0xfe:
            instruction_str << "cpi d8";
            break;
        case 0xff:
            instruction_str << "rst 38";
            break;
        case 0xfd:
            instruction_str << "call";
            break;
        default:
            instruction_str << "not implemented mem";

        }
        return instruction_str.str();
}

void Disassembly::create_file()
{
    file_disass.open(__file_disass__);
    file_mem.open(__file_mem__);
    if(!file_disass.is_open() || !file_mem.is_open())
        return;
}

byte_t Disassembly::read_memory(word_t __addr, byte_t *__mem)
{
    return __mem[__addr];
}

void Disassembly::file_save_disass(byte_t __opcode, word_t __pc)
{
    file_disass << Disassembly::execute_opcode(__opcode, __pc) << std::endl;
}

Disassembly::~Disassembly()
{
    file_disass.close();
    file_mem.close();
}

Disassembly::Disassembly()
{
    create_file();
}

void Disassembly::run_disassembly(word_t __pc, byte_t *__mem)
{
    byte_t __opcode = Disassembly::read_memory(__pc, __mem);
    Disassembly::file_save_disass(__opcode, __pc);
}

void Disassembly::run_memory(byte_t *__mem, signed __size)
{
    for(signed i = 0; i <= __size; i++)
        file_mem << __mem[i];
}
