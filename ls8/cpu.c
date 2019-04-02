#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).

    int instruction = cpu_ram_read(cpu, cpu->PC);

    unsigned int total_operands = instruction >> 6;
    // 2. Figure out how many operands this next instruction requires

    switch (instruction)
    {
    case 0b10000010: //LDI
      int operandA = cpu_ram_read(cpu, cpu->PC + 1);
      int operandB = cpu_ram_read(cpu, cpu->PC + 2);
      break;
    case 0b01000111: //PRN
      int operandA = cpu_ram_read(cpu, cpu->PC + 1);
      printf("%s\n", cpu->registers[operandA]);
      break;
    case 0b00000001: //HLT
      running = 0;
      break;
    default:
      printf("ERROR: invalid instruction.\n");
      exit(1);
    };

    // 3. Get the appropriate value(s) of the operands following this instruction

    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
    cpu->PC += total_operands + 1;
    }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  memset(cpu->ram, 0, 8 * sizeof(unsigned char));
  memset(cpu->registers, 0, 256 * sizeof(unsigned char));
}

int cpu_ram_read(struct cpu *cpu, int index)
{
  return cpu->ram[index];
}
void cpu_ram_write(struct cpu *cpu, int index, int value)
{
  cpu->ram[index] = value;
}
