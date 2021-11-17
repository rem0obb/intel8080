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
//  to use, copy, modify, merge, publish, distribute, 0x9sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:

//  The above copyright notice and this permission notice shall be included in
//  all copies or 0x9.....substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "disassembly.hpp"

std::string Disassembly::execute_opcode(byte_t __opcode, word_t __pc) noexcept
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
            instruction_str << "0x01.....lxi b, d16";
            break;
        case 0x02:
            instruction_str << "0x02.....stax b";
            break;
        case 0x03:
            instruction_str << "0x03.....inx b";
            break;
        case 0x04:
            instruction_str << "0x04.....inr b";
            break;
        case 0x05:
            instruction_str << "0x05.....dcr b";
            break;
        case 0x06:
            instruction_str << "0x06.....mvi b, d8";
            break;
        case 0x07:
            instruction_str << "0x07.....rlc";
            break;
        case 0x09:
            instruction_str << "0x09.....dad b";
            break;
        case 0x0a:
            instruction_str << "0x0a.....ldax b";
            break;
        case 0x0b:
            instruction_str << "0x0b.....dcx b";
            break;
        case 0x0c:
            instruction_str << "0x0c.....inr c";
            break;
        case 0x0d:
            instruction_str << "0x0d.....dcr c";
            break;
        case 0x0e:
            instruction_str << "0x0e.....mvi c, d18";
            break;
        case 0x0f:
            instruction_str << "0x0f.....rrc";
            break;
        case 0x11:
            instruction_str << "0x11.....lxi d16";
            break;
        case 0x12:
            instruction_str << "0x12.....stax d";
            break;
        case 0x13:
            instruction_str << "0x13.....inx de";
            break;
        case 0x14:
            instruction_str << "0x14.....inx d";
            break;
        case 0x15:
            instruction_str << "0x15.....dcr d";
            break;
        case 0x16:
            instruction_str << "0x16.....mvi d, d8";
            break;
        case 0x17:
            instruction_str << "0x17.....ral";
            break;
        case 0x19:
            instruction_str << "0x19.....dad d";
            break;
        case 0x1a:
            instruction_str << "0x1a.....lax d";
            break;
        case 0x1b:
            instruction_str << "0x1b.....inr d";
            break;
        case 0x1c:
            instruction_str << "0x1c.....inr e";
            break;
        case 0x1d:
            instruction_str << "0x1d.....dcr e";
            break;
        case 0x1e:
            instruction_str << "0x1e.....mvi e, d8";
            break;
        case 0x1f:
            instruction_str << "0x1f.....rar";
            break;
        case 0x21:
            instruction_str << "0x21.....lxi hl";
            break;
        case 0x22:
            instruction_str << "0x22.....shld";
            break;
        case 0x23:
            instruction_str << "0x23.....inx h";
            break;
        case 0x24:
            instruction_str << "0x24.....inr h";
            break;
        case 0x25:
            instruction_str << "0x25.....dcr h";
            break;
        case 0x26:
            instruction_str << "0x26.....mvi h, d8";
            break;
        case 0x27:
            instruction_str << "0x27.....daa";
            break;
        case 0x29:
            instruction_str << "0x29.....dad h";
            break;
        case 0x2a:
            instruction_str << "0x2a.....lhld";
            break;
        case 0x2b:
            instruction_str << "0x2b.....dcx h";
            break;
        case 0x2c:
            instruction_str << "0x2c.....inr l";
            break;
        case 0x2d:
            instruction_str << "0x2d.....dcr l";
            break;
        case 0x2e:
            instruction_str << "0x2e.....mvi l, d8";
            break;
        case 0x2f:
            instruction_str << "0x2f.....cma";
            break;
        case 0x31:
            instruction_str << "0x31.....lxi sp";
            break;
        case 0x32:
            instruction_str << "0x32.....sta addr";
            break;
        case 0x33:
            instruction_str << "0x33.....inx sp";
            break;
        case 0x34:
            instruction_str << "0x34.....inr m";
            break;
        case 0x35:
            instruction_str << "0x35.....dcr m";
            break;
        case 0x36:
            instruction_str << "0x36.....mvi m, d8";
            break;
        case 0x37:
            instruction_str << "0x37.....stc";
            break;
        case 0x39:
            instruction_str << "0x39.....dad sp";
            break;
        case 0x3a:
            instruction_str << "0x3a.....lda adr";
            break;
        case 0x3b:
            instruction_str << "0x3b.....dcx sp";
            break;
        case 0x3c:
            instruction_str << "0x3c.....inr a";
            break;
        case 0x3d:
            instruction_str << "0x3d.....dcr a";
            break;
        case 0x3e:
            instruction_str << "0x3e.....mvi a, d8";
            break;
        case 0x3f:
            instruction_str << "0x3f.....cmc";
            break;
        case 0x40:
            instruction_str << "0x40.....mov b, b";
            break;
        case 0x41:
            instruction_str << "0x41.....mov b, c";
            break;
        case 0x42:
            instruction_str << "0x42.....mov b, d";
            break;
        case 0x43:
            instruction_str << "0x43.....mov b, e";
            break;
        case 0x44:
            instruction_str << "0x44.....mov b, h";
            break;
        case 0x45:
            instruction_str << "0x45.....mov b, l";
            break;
        case 0x46:
            instruction_str << "0x46.....mov b, hl";
            break;
        case 0x47:
            instruction_str << "0x47.....mov b, a";
            break;
        case 0x48:
            instruction_str << "0x48.....mov c, b";
            break;
        case 0x49:
            instruction_str << "0x49.....mov c, c";
            break;
        case 0x4a:
            instruction_str << "0x4a.....mov c, d";
            break;
        case 0x4b:
            instruction_str << "0x4b.....mov c, e";
            break;
        case 0x4c:
            instruction_str << "0x4c.....mov c, h";
            break;
        case 0x4d:
            instruction_str << "0x4d.....mov c, l";
            break;
        case 0x4e:
            instruction_str << "0x4e.....mov c, hl";
            break;
        case 0x4f:
            instruction_str << "0x4f.....mov c, a";
            break;
        case 0x50:
            instruction_str << "0x50.....mov d, b";
            break;
        case 0x51:
            instruction_str << "0x51.....mov d, c";
            break;
        case 0x52:
            instruction_str << "0x52.....mov d, d";
            break;
        case 0x53:
            instruction_str << "0x53.....mov d, e";
            break;
        case 0x54:
            instruction_str << "0x54.....mov d, h";
            break;
        case 0x55:
            instruction_str << "0x55.....mov d, l";
            break;
        case 0x56:
            instruction_str << "0x56.....mov d, hl";
            break;
        case 0x57:
            instruction_str << "0x57.....mov d, a";
            break;
        case 0x58:
            instruction_str << "0x58.....mov e, b";
            break;
        case 0x59:
            instruction_str << "0x59.....mov e, c";
            break;
        case 0x5a:
            instruction_str << "0x5a.....mov e, d";
            break;
        case 0x5b:
            instruction_str << "0x5b.....mov e, e";
            break;
        case 0x5c:
            instruction_str << "0x5c.....mov e, h";
            break;
        case 0x5d:
            instruction_str << "0x5d.....mov e, l";
            break;
        case 0x5e:
            instruction_str << "0x5e.....mov e, hl";
            break;
        case 0x5f:
            instruction_str << "0x5f.....mov e, a";
            break;
        case 0x60:
            instruction_str << "0x60.....mov h, b";
            break;
        case 0x61:
            instruction_str << "0x61.....mov h, c";
            break;
        case 0x62:
            instruction_str << "0x62.....mov h, d";
            break;
        case 0x63:
            instruction_str << "0x63.....mov h, e";
            break;
        case 0x64:
            instruction_str << "0x64.....mov h, h";
            break;
        case 0x65:
            instruction_str << "0x65.....mov h, l";
            break;
        case 0x66:
            instruction_str << "0x66.....mov h, hl";
            break;
        case 0x67:
            instruction_str << "0x67.....mov h, a";
            break;
        case 0x68:
            instruction_str << "0x68.....mov l, b";
            break;
        case 0x69:
            instruction_str << "0x69.....mov l, c";
            break;
        case 0x6a:
            instruction_str << "0x6a.....mov l, d";
            break;
        case 0x6b:
            instruction_str << "0x6b.....mov l, e";
            break;
        case 0x6c:
            instruction_str << "0x6c.....mov l, h";
            break;
        case 0x6d:
            instruction_str << "0x6d.....mov l, l";
            break;
        case 0x6e:
            instruction_str << "0x6e.....mov l, hl";
            break;
        case 0x6f:
            instruction_str << "0x6f.....mov l, a";
            break;
        case 0x70:
            instruction_str << "0x70.....mov hl, b";
            break;
        case 0x71:
            instruction_str << "0x71.....mov hl, c";
            break;
        case 0x72:
            instruction_str << "0x72.....mov hl, d";
            break;
        case 0x73:
            instruction_str << "0x73.....mov hl, e";
            break;
        case 0x74:
            instruction_str << "0x74.....mov hl, h";
            break;
        case 0x75:
            instruction_str << "0x75.....mov hl, l";
            break;
        case 0x76:
            instruction_str << "0x76.....hlt";
            break;
        case 0x77:
            instruction_str << "0x77.....mov hl, a";
            break;
        case 0x78:
            instruction_str << "0x78.....mov a, b";
            break;
        case 0x79:
            instruction_str << "0x79.....mov a, c";
            break;
        case 0x7a:
            instruction_str << "0x7a.....mov a, d";
            break;
        case 0x7b:
            instruction_str << "0x7b.....mov a, e";
            break;
        case 0x7c:
            instruction_str << "0x7c.....mov a, h";
            break;
        case 0x7d:
            instruction_str << "0x7d.....mov a, l";
            break;
        case 0x7e:
            instruction_str << "0x7e.....mov a, hl";
            break;
        case 0x7f:
            instruction_str << "0x7f.....mov a, a";
            break;
        case 0x80:
            instruction_str << "0x80.....add b";
            break;
        case 0x81:
            instruction_str << "0x81.....add c";
            break;
        case 0x82:
            instruction_str << "0x82.....add d";
            break;
        case 0x83:
            instruction_str << "0x83.....add e";
            break;
        case 0x84:
            instruction_str << "0x84.....add h";
            break;
        case 0x85:
            instruction_str << "0x85.....add l";
            break;
        case 0x86:
            instruction_str << "0x86.....add hl";
            break;
        case 0x87:
            instruction_str << "0x87.....add a";
            break;
        case 0x88:
            instruction_str << "0x88.....adc b";
            break;
        case 0x89:
            instruction_str << "0x89.....adc c";
            break;
        case 0x8a:
            instruction_str << "0x8a.....adc d";
            break;
        case 0x8b:
            instruction_str << "0x8b.....adc e";
            break;
        case 0x8c:
            instruction_str << "0x8c.....adc h";
            break;
        case 0x8d:
            instruction_str << "0x8d.....adc l";
            break;
        case 0x8e:
            instruction_str << "0x8e.....adc hl";
            break;
        case 0x8f:
            instruction_str << "0x8f.....adc a";
            break;
        case 0x90:
            instruction_str << "0x90.....sub b";
            break;
        case 0x91:
            instruction_str << "0x91.....sub c";
            break;
        case 0x92:
            instruction_str << "0x92.....sub d";
            break;
        case 0x93:
            instruction_str << "0x93.....sub e";
            break;
        case 0x94:
            instruction_str << "0x94.....sub h";
            break;
        case 0x95:
            instruction_str << "0x95.....sub l";
            break;
        case 0x96:
            instruction_str << "0x96.....sub hl";
            break;
        case 0x97:
            instruction_str << "0x97.....sbb a";
            break;
        case 0x98:
            instruction_str << "0x98.....sbb b";
            break;
        case 0x99:
            instruction_str << "0x99.....sbb c";
            break;
        case 0x9a:
            instruction_str << "0x9a.....sbb d";
            break;
        case 0x9b:
            instruction_str << "0x9b.....sbb e";
            break;
        case 0x9c:
            instruction_str << "0x9c.....sbb h";
            break;
        case 0x9d:
            instruction_str << "0x9d.....sbb l";
            break;
        case 0x9e:
            instruction_str << "0x9e.....sbb hl";
            break;
        case 0x9f:
            instruction_str << "0x9f.....sbb a";
            break;
        case 0xa0:
            instruction_str << "0xa0.....ana b";
            break;
        case 0xa1:
            instruction_str << "0xa1.....ana c";
            break;
        case 0xa2:
            instruction_str << "0xa2.....ana d";
            break;
        case 0xa3:
            instruction_str << "0xa3.....ana e";
            break;
        case 0xa4:
            instruction_str << "0xa4.....ana h";
            break;
        case 0xa5:
            instruction_str << "0xa5.....ana l";
            break;
        case 0xa6:
            instruction_str << "0xa6.....ana hl";
            break;
        case 0xa7:
            instruction_str << "0xa7.....ana a";
            break;
        case 0xa8:
            instruction_str << "0xa8.....xra b";
            break;
        case 0xa9:
            instruction_str << "0xa9.....xra c";
            break;
        case 0xaa:
            instruction_str << "0xaa.....xra d";
            break;
        case 0xab:
            instruction_str << "0xab.....xra e";
            break;
        case 0xac:
            instruction_str << "0xac.....xra h";
            break;
        case 0xad:
            instruction_str << "0xad.....xra l";
            break;
        case 0xae:
            instruction_str << "0xae.....xra hl";
            break;
        case 0xaf:
            instruction_str << "0xaf.....xra a";
            break;
        case 0xb0:
            instruction_str << "0xb0.....ora b";
            break;
        case 0xb1:
            instruction_str << "0xb1.....ora c";
            break;
        case 0xb2:
            instruction_str << "0xb2.....ora d";
            break;
        case 0xb3:
            instruction_str << "0xb3.....ora e";
            break;
        case 0xb4:
            instruction_str << "0xb4.....ora h";
            break;
        case 0xb5:
            instruction_str << "0xb5.....ora l";
            break;
        case 0xb6:
            instruction_str << "0xb6.....ora hl";
            break;
        case 0xb7:
            instruction_str << "0xb7.....ora a";
            break;
        case 0xb8:
            instruction_str << "0xb8.....cmp b";
            break;
        case 0xb9:
            instruction_str << "0xb9.....cmp c";
            break;
        case 0xba:
            instruction_str << "0xba.....cmp bd";
            break;
        case 0xbb:
            instruction_str << "0xbb.....cmp e";
            break;
        case 0xbc:
            instruction_str << "0xbc.....cmp h";
            break;
        case 0xbd:
            instruction_str << "0xbd.....cmp l";
            break;
        case 0xbe:
            instruction_str << "0xbe.....cmp hl";
            break;
        case 0xbf:
            instruction_str << "0xbf.....cmp a";
            break;
        case 0xc0:
            instruction_str << "0xc0.....rnz";
            break;
        case 0xc1:
            instruction_str << "0xc1.....pop b";
            break;
        case 0xc2: 
            instruction_str << "0xc2.....jnz 0x8";
            break;
        case 0xc3:
            instruction_str << "0xc3.....jmp";
            break;
        case 0xc4:
            instruction_str << "0xc4.....cnz";
            break;
        case 0xc5:
            instruction_str << "0xc5.....push bc";
            break;
        case 0xc6:
            instruction_str << "0xc6.....adi  d8";
            break;
        case 0xc7:
            instruction_str << "0xc7.....rst 0x00";
            break;
        case 0xc8:
            instruction_str << "0xc8.....rz";
            break;
        case 0xc9:
            instruction_str << "0xc9.....ret";
            break;
        case 0xca:
            instruction_str << "0xca.....jz";
            break;
        case 0xcb:
            instruction_str << "0xcb.....jmp";
            break;
        case 0xcc:
            instruction_str << "0xcc.....cz 0x8";
            break;
        case 0xcd:
            instruction_str << "0xcd.....call 0x8";
            break;
        case 0xce:
            instruction_str << "0xce.....aci d8";
            break;
        case 0xcf:
            instruction_str << "0xcf.....rst 0x01";
            break;
        case 0xd0:
            instruction_str << "0xd0.....rnc";
            break;
        case 0xd1:
            instruction_str << "0xd1.....pop de";
            break;
        case 0xd2:
            instruction_str << "0xd2.....jnc 0x8";
            break;
        case 0xd3:
            instruction_str << "0xd3.....out d8";
            break;
        case 0xd4:
            instruction_str << "0xd4.....cnc 0x8";
            break;
        case 0xd5:
            instruction_str << "0xd5.....push de";
            break;
        case 0xd6:
            instruction_str << "0xd6.....sui d8";
            break;
        case 0xd7:
            instruction_str << "0xd7.....rst 0x10";
            break;
        case 0xd8:
            instruction_str << "0xd8.....rc";
            break;
        case 0xd9:
            instruction_str << "0xd9.....ret";
            break;
        case 0xda:
            instruction_str << "0xda.....jc 0x8";
            break;
        case 0xdb:
            instruction_str << "0xdb.....in d8";
            break;
        case 0xdc:
            instruction_str << "0xdc.....cc 0x8";
            break;
        case 0xdd:
            instruction_str << "0xdd.....call";
            break;
        case 0xde:
            instruction_str << "0xde.....sbi d8";
            break;
        case 0xdf:
            instruction_str << "0xdf.....rst 0x18";
            break;
        case 0xe0:
            instruction_str << "0xe0.....rpo";
            break;
        case 0xe1:
            instruction_str << "0xe1.....pop hl";
            break;
        case 0xe2:
            instruction_str << "0xe2.....jpo 0x8";
            break;
        case 0xe3:
            instruction_str << "0xe3.....xthl";
            break;
        case 0xe4:
            instruction_str << "0xe4.....cpo";
            break;
        case 0xe5:
            instruction_str << "0xe5.....push hl";
            break;
        case 0xe6:
            instruction_str << "0xe6.....ani d8";
            break;
        case 0xe7:
            instruction_str << "0xe7.....rst 0x20";
            break;
        case 0xe8:
            instruction_str << "0xe8.....rpe";
            break;
        case 0xe9:
            instruction_str << "0xe9.....pchl";
            break;
        case 0xea:
            instruction_str << "0xea.....jpe";
            break;
        case 0xeb:
            instruction_str << "0xeb.....xchg";
            break;
        case 0xec:
            instruction_str << "0xec.....cpe 0x8";
            break;
        case 0xed:
            instruction_str << "0xed.....call";
            break;
        case 0xee:
            instruction_str << "0xee.....xra d8";
            break;
        case 0xef:
            instruction_str << "0xef.....rst 0x28";
            break;
        case 0xf0:
            instruction_str << "0xf0.....rp";
            break;
        case 0xf1:
            instruction_str << "0xf1.....pop psw";
            break;
        case 0xf2:
            instruction_str << "0xf2.....jp 0x8";
            break;
        case 0xf3:
            instruction_str << "0xf3.....di";
            break;
        case 0xf4:
            instruction_str << "0xf4.....cp 0x8";
            break;
        case 0xf5:
            instruction_str << "0xf5.....push psw";
            break;
        case 0xf6:
            instruction_str << "0xf6.....ori d8";
            break;
        case 0xf7:
            instruction_str << "0xf7.....rst 30";
            break;
        case 0xf8:
            instruction_str << "0xf8.....rm";
            break;
        case 0xf9:
            instruction_str << "0xf9.....sphl";
            break;
        case 0xfa:
            instruction_str << "0xfa.....jm 0x8";
            break;
        case 0xfb:
            instruction_str << "0xfb.....ei";
            break;
        case 0xfc:
            instruction_str << "0xfc.....cm 0x8";
            break;
        case 0xfe:
            instruction_str << "0xfe.....cpi d8";
            break;
        case 0xff:
            instruction_str << "0xff.....rst 38";
            break;
        case 0xfd:
            instruction_str << "0xfd.....call";
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

byte_t Disassembly::read_memory(word_t addr, byte_t *__mem)
{
    return __mem[addr];
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
        file_mem << std::hex << __mem[i] << std::endl;
}