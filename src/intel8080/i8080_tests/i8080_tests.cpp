// the intel 8080 code is unstable, if there are bugs send an insue :) 
// the code is constantly being updated, i'm planning to bring new features 
// to the intel 8080, an example would be an overflow flag... 
// if you wanted to send a pull stay a I will analyze them all

#include "i8080.hpp"

void execute_tests(std::string name)
{
    i8080 cpu;
    cpu.i8080_init(); // inicializing flags

    byte_t *mem = cpu.memory_addr();

    cpu.load_file_bin(name, mem, 0x100); // load bin for memory and jump pc for 0x100
    int instructions = 0;

    mem[5] = 0xc9; // inject memory for subrotine

    while (true)
    {
        if (cpu.get_pc() == 5)
            if (cpu.get_register_c() == 2)
                std::cout << cpu.get_register_e();

        cpu.i8080_instructions();
        instructions++;

        if (cpu.get_pc() == 0)
            break;
        else if (mem[cpu.get_pc()] == 0x76) // not implemented hlt
            break;
    
    }
    std::cout << "\n *** Cycles[" << cpu.get_cycles() << "] Instructions[" << instructions << "] " << std::endl;
}

int main()
{
    execute_tests("src/intel8080/i8080_tests/bin/TEST.COM");

    return 0;
}