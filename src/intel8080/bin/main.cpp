// the intel 8080 code is unstable, if there are bugs send an insue :)
// the code is constantly being updated, i'm planning to bring new features
// to the intel 8080, an example would be an overflow flag...
// if you wanted to send a pull stay a I will analyze them all

#include <time.h>

#include "../disassembly.hpp"
#include "../i8080.hpp"

#define DISASSEMBLY false

static void banner()
{
    std::cout << "       ____________________________    " << std::endl;
    std::cout << "      /                           /\\  " << std::endl;
    std::cout << "     /   Vitor Mob              _/ /\\ " << std::endl;
    std::cout << "    /        Intel8080         / \\    " << std::endl;
    std::cout << "   /                           /\\     " << std::endl;
    std::cout << "  /___________________________/ /      " << std::endl;
    std::cout << "  \\___________________________\\/     " << std::endl;
    std::cout << "   \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ " << std::endl
              << std::endl;
}

void intelExecute(std::string p_name, word_t p_pc)
{
    i8080 *cpu = new i8080();
    Disassembly *disass = new Disassembly();

    byte_t *mem = cpu->memory_addr();  // memory
    // registers
    word_t PC = 0;
    word_t DE = 0;
    byte_t E = 0;
    byte_t C = 0;

    cpu->load_file_bin(p_name, mem,
                       p_pc);  // load bin for memory and jump pc for 0x100
    int instructions = 0;      // counter instructions

    mem[0x00005] = 0xc9;

    while (true) {
        PC = cpu->get_pc();
        E = cpu->get_register_e();
        C = cpu->get_register_c();
        DE = cpu->get_register_de();

        if (PC == 5) {
            if (C == 2)
                std::cout.put(E);
            else if (C == 9)
                for (int i = DE; mem[i] != 0x24; i++) std::cout.put(mem[i]);
        }

        instructions++;
        cpu->i8080_instructions();
        if (DISASSEMBLY == true) {
            disass->run_disassembly(PC, mem);
            disass->run_memory(mem, cpu->get_size_mem());
        }
        if (PC == 0 || mem[PC] == 0x76) break;
    }

#if DEBUG
    std::cout << "\n\n*** Cycles=" << std::dec << cpu->get_cycles() << std::endl
              << "*** Instructions=" << instructions << std::endl;
#endif

    delete disass;
    delete cpu;
}

int main(int argc, char *argv[])
{
    banner();

#if DEBUG
    clock_t start = clock();
#endif
    if (argc >= 3)
        intelExecute((std::string)argv[1], atoi(argv[2]));
    else
        std::cerr << "*** Error : execute : " << argv[0] << " <name.bin> <PC>"
                  << std::endl;
#if DEBUG
    clock_t result = clock() - start;
    std::cout << "\n*** Runtime=" << result << " ms" << std::endl;
#endif
    return EXIT_SUCCESS;
}
