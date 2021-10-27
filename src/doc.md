# Documentation

In this part I will explain a little about the functions within the program, for study purposes, 
if you are thinking of implementing your own intel 8080 emulator, 
you can also take my code as a reference for your implementation, lets go!!

## Index 

[Registers](#registers)

[Memory](#memory)

[Instructions](#instructions)


## API´s

part that the user can use to develop some application on top of the emulator

## Registers 

* void i8080_init()

    * function/method that will initialize the flags and registers

* byte_t get_register_c() 
    
    * will bring the value of the C Register

* word_t get_flag_sp()
  
    * will bring the value of the SP(Stack Pointer)

* word_t get_pc()
    
    * will bring the value of the PC(Program Counter)
    
* word_t get_register_hl()
  
    * will bring the value of the HL Tree Pair Register
  
* word_t get_register_bc()
  
    * will bring the value of the BC Tree Pair Register
  
* byte_t get_register_e()

    * will bring the value of the E Register

* word_t get_register_de()

    * will bring the value of the HL Tree Pair Register
    
* int get_cycles()

    * will bring the value of the Cycles 
    
## Memory 

* byte_t *memory_addr()
  
    * pointer to memory address
   

* void load_file_bin(std::string name, * byte_t *load);
 
    * it is function/method will load binary/opcode
    into processor memory/intel8080
    
* void i8080_instructions()

    * will increment the PC by reading and executing opcode the loaded processor memory

* signed get_size_mem()
  * returns size and bytes loaded in memory

## Instructions 

intel 8080 instructions implemented in my emulator
in the [book]( https://altairclone.com/downloads/manuals/8080%20Programmers%20Manual.pdf) will explain in detail what each instruction will do and what it serves in the program

* void push(word_t data16)

    * Only method/function to add to the program stack, decreasing the SP - 2

* word_t pop();

    * will unstack the program stack by 
    incrementing SP + 2

* void add(word_t data16)

    * will make an addition with the data16 and the A(Accumulator) and the affected flags will be Z,S,P,AC,C

* void adc(word_t data16)

    * will make an addition with the data16 and the A(Accumulator) and C and the affected flags will be Z,S,P,AC,C

* void dad(word_t data16)
  * adds the contents of the hl record pair, and the result is e hl

* void jmp()

    * will push memory with PC content
    and then jump to PC's incremented address + 2

void call();

* void rst(word_t addr)
  *  the program continues at the last address

* void sub(word_t data16)
  *  the accumulator subtracts the contents of the addressed position the affected flags will be Z,S,P,AC,C

* void sbb(word_t data16)
  * the accumulator subtracts any less CF the contents of the addressed position the affected flags will be Z,S,P,AC,C

* void cmp(word_t data16)
  * compare accumulator the affected flags will be Z,S,P,AC,C

* void ana(word_t data16)
  * the contents of the accumulator are logically 'and' combined and the affected flags will be Z,S,P,AC,C

* void ora(word_t data16)
    *  the contents of the accumulator are logically 'or' combined and the affected flags will be Z,S,P,AC,C

* void xra(word_t data16)
    * logically combines 'exclusive-or' the contents of the accumulator with that of the flags and the affected flags will be Z,S,P,AC,C

* word_t inr(word_t data16)
  * increment register + 1 and the affected flags will be Z,S,P,AC

* word_t dcr(word_t data16)
  * decrement register - 1  the affected flags will be Z,S,P,AC
  
