// the intel 8080 code is unstable, if there are bugs send an insue :)
// the code is constantly being updated, i'm planning to bring new features
// to the intel 8080, an example would be an overflow flag...
// if you wanted to send a pull stay a I will analyze them all

#include "../i8080.hpp"
#include "../disassembly.hpp"

#include <time.h>

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

const static void execute_tests(const std::string &name)
{
  i8080 cpu;
  Disassembly disass;

  byte_t *mem = cpu.memory_addr(); // memory
  // registers
  word_t PC;
  word_t DE;
  byte_t E;
  byte_t C;

  cpu.load_file_bin(name, mem); // load bin for memory and jump pc for 0x100
  int instructions = 0;                // counter instructions

  mem[0x5] = 0xc9;

  while (true)
  {
    PC = cpu.get_pc();
    E = cpu.get_register_e();
    C = cpu.get_register_c();
    DE = cpu.get_register_de();

    if (PC == 5)
    {
      if (C == 9)
        for (int i = DE; mem[i] != 0x24; i += 1)
          std::cout.put(mem[i]);
      if (C == 2)
        std::cout.put(E);
    }

    if (DISASSEMBLY == true)
    {
      disass.run_disassembly(PC, mem);
      disass.run_memory(mem, cpu.get_size_mem());
    }

    if (PC == 0 || mem[PC] == 0x76)
      break;

    instructions++;
    cpu.i8080_instructions();
  }

  std::cout << "\n\n*** Cycles=" << std::dec << cpu.get_cycles() << std::endl
            << "*** Instructions=" << instructions << std::endl;
}

int main()
{
  banner();

  clock_t start = clock();

  execute_tests("/home/mob/Documents/c-cpp-csharp/i8080-core/assets/8080EX1.COM");
  execute_tests("/home/mob/Documents/c-cpp-csharp/i8080-core/assets/TEST.COM");
  execute_tests("src/intel8080/i8080_tests/bin/CPUTEST.COM");

  clock_t result = clock() - start;

  std::cout << "\n*** Runtime=" << result << " ms" << std::endl;

  return EXIT_SUCCESS;
}
