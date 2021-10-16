// the intel 8080 code is unstable, if there are bugs send an insue :)
// the code is constantly being updated, i'm planning to bring new features
// to the intel 8080, an example would be an overflow flag...
// if you wanted to send a pull stay a I will analyze them all

#include "i8080.hpp"
#include <time.h>

void execute_tests(std::string name)
{
    i8080 cpu;
    cpu.i8080_init(); // inicializing flags

    byte_t *mem = cpu.memory_addr();
    word_t PC = 0;
    word_t DE = 0;
    byte_t E = 0;
    byte_t C = 0;

    cpu.load_file_bin(name, mem, 0x100); // load bin for memory and jump pc for 0x100
    int instructions = 0;                // counter instructions

    mem[5] = 0xc9;

    while (true)
    {
        PC = cpu.get_pc();
        E = cpu.get_register_e();
        C = cpu.get_register_c();
        DE = cpu.get_register_de();

        if (PC == 5)
        {
            if (C == 2)
                std::cout.put(E);
            if (C == 9)
                for (int i = DE; mem[i] != '$'; i++)
                    std::cout.put(mem[i]);
        }

        cpu.i8080_instructions();
        instructions++;

        if (PC == 0)
            break;
    }
    std::cout << "\n\n*** Cycles=" << cpu.get_cycles() << std::endl
              << "*** Instructions=" << instructions << std::endl
              << std::endl;
}

int main()
{

    clock_t start = clock();

    execute_tests("src/intel8080/i8080_tests/bin/TST8080.COM");
    execute_tests("src/intel8080/i8080_tests/bin/8080PRE.COM");

    clock_t result = clock() - start;

    std::cout << "*** runtime=" << result << " ms" << std::endl;

    return EXIT_SUCCESS;
}