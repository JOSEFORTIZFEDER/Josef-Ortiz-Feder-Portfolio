/*
	You can use these two print statements for the errors:
		printf("Virtual Machine Error: Stack Overflow Error\n");
		printf("Virtual Machine Error: Out of Bounds Access Error\n");
*/

// Josef Ortiz-Feder
// Project 1 COP 3402
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#define REG_FILE_SIZE 10
#define MAX_STACK_LENGTH 100

void print_execution(int line, char *opname, instruction IR, int PC, int BP, int SP, int *stack, int *RF)
{
	int i;
	// print out instruction and registers
	printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t\t", line, opname, IR.r, IR.l, IR.m, PC, SP, BP);

	// print register file
	for (i = 0; i < REG_FILE_SIZE; i++)
		printf("%d ", RF[i]);
	printf("\n");

	// print stack
	printf("stack:\t");
	for (i = MAX_STACK_LENGTH - 1; i >= SP; i--)
		printf("%d ", stack[i]);
	printf("\n");
}

int base(int L, int BP, int *stack)
{
	int ctr = L;
	int rtn = BP;
	while (ctr > 0)
	{
		rtn = stack[rtn];
		ctr--;
	}
	return rtn;
}

// Only part of the code that was changed by Josef Ortiz-Feder
void execute_program(instruction *code, int printFlag)
{
	// Declaring Variables and putting 0's as placeholders in both arrays
	int stack[MAX_STACK_LENGTH] = {0};
	int RF[REG_FILE_SIZE] = {0};
	int PC=0;
	int BP = MAX_STACK_LENGTH-1;
	int SP = BP+1;
	int temp = -1;

	for(int i = 0; i < MAX_STACK_LENGTH; ++i)
	{
		stack[i] = 0;
	}
	for(int i = 0; i < REG_FILE_SIZE; ++i)
	{
		RF[i] = 0;
	}

	// keep this
	if (printFlag)
	{
		printf("\t\t\t\t\tPC\tSP\tBP\n");
		printf("Initial values:\t\t\t\t%d\t%d\t%d\n", 0, SP, BP); //PC, SP, BP
	}
	int halt = 1;
	int currLine=0;

	// While loop that runs until there are no more instructions
	while(halt==1)
	{
		instruction currInstruction = code[PC];

		// Switch Case format to determine which opcode was given and what to execute based off of it
		switch(currInstruction.opcode)
		{
			case 1: // LIT
					RF[currInstruction.r] = currInstruction.m;
					print_execution(currLine, "LIT", currInstruction, PC+1, BP, SP, stack, RF);
					break;
			case 2: // RET
					SP = BP+1;
					BP = stack[SP-2];
					PC = (stack[SP-3]) -1;
					print_execution(currLine, "RET", currInstruction, PC+1, BP, SP, stack, RF);
					break;
			case 3: // LOD
					if(base(currInstruction.l, BP, stack) - currInstruction.m < 0 || base(currInstruction.l, BP, stack) - currInstruction.m >= MAX_STACK_LENGTH)
					{
						printf("Virtual Machine Error: Out of Bounds Access Error\n");
						halt = 0;
						break;
					}
					RF[currInstruction.r] = stack[(base(currInstruction.l, BP, stack)) - RF[currInstruction.m]];
					print_execution(currLine, "LOD", currInstruction, PC+1, BP, SP, stack, RF);
					break;
			case 4: // STO
					if(base(currInstruction.l, BP, stack) - currInstruction.m < 0 || base(currInstruction.l, BP, stack) - currInstruction.m >= MAX_STACK_LENGTH)
					{
					  printf("%d %d ON STO Virtual Machine Error: Out of Bounds Access Error\n", currInstruction.l, BP);
						halt = 0;
						break;
					}
					stack[base(currInstruction.l, BP, stack) - RF[currInstruction.m]] = RF[currInstruction.r];
					print_execution(currLine, "STO", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 5: // CAL
					stack[SP-1] = base(currInstruction.l, BP, stack);
					temp = base(currInstruction.l, BP, stack);
					stack[SP-2] = BP;
					stack[SP-3] = PC+1;
					BP = SP -1;
					PC = currInstruction.m -1;
					print_execution(currLine, "CAL", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 6: // INC
					if(SP-currInstruction.m < 0)
					{
						printf("Virtual Machine Error: Stack Overflow Error\n");
						halt = 0;
						break;
					}
					SP = SP-currInstruction.m;
					print_execution(currLine, "INC", currInstruction, PC+1, BP, SP, stack, RF);
					break;
			case 7: // JMP
					PC = currInstruction.m - 1;
					print_execution(currLine, "JMP", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 8: // JPC
					if(RF[currInstruction.r] == 0)
					{
						PC = currInstruction.m-1;
					}
					print_execution(currLine, "JPC", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 9: // WRT
					printf("Write Value: %d\n", RF[currInstruction.r]);
					print_execution(currLine, "WRT", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 10: // RED
					printf("Please Enter a Value: ");
					scanf("%d", &RF[currInstruction.r]);
					printf("\n");
					print_execution(currLine, "RED", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 11: // HAL
					halt = 0;
					print_execution(currLine, "HLT", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 12: // NEG
					RF[currInstruction.r] = -RF[currInstruction.r];
					print_execution(currLine, "NEG", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 13: // ADD
					RF[currInstruction.r] = RF[currInstruction.l] + RF[currInstruction.m];
					print_execution(currLine, "ADD", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 14: // SUB
					RF[currInstruction.r] = RF[currInstruction.l] - RF[currInstruction.m];
					print_execution(currLine, "SUB", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 15: // MUL
					RF[currInstruction.r] = RF[currInstruction.l] * RF[currInstruction.m];
					print_execution(currLine, "MUL", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 16: // DIV
					RF[currInstruction.r] = RF[currInstruction.l] / RF[currInstruction.m];
					print_execution(currLine, "DIV", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 17: // MOD
					RF[currInstruction.r] = RF[currInstruction.l] % RF[currInstruction.m];
					print_execution(currLine, "MOD", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 18: // EQL
					if(RF[currInstruction.m] == RF[currInstruction.l])
						RF[currInstruction.r] = 1;
					else
						RF[currInstruction.r] = 0;

					print_execution(currLine, "EQL", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 19: // NEQ
					if(RF[currInstruction.m] != RF[currInstruction.l])
						RF[currInstruction.r] = 1;
					else
						RF[currInstruction.r] = 0;

					print_execution(currLine, "NEQ", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 20: // LSS
					if(RF[currInstruction.l] < RF[currInstruction.m])
						RF[currInstruction.r] = 1;
					else
						RF[currInstruction.r] = 0;

					print_execution(currLine, "LSS", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 21: // LEQ
					if(RF[currInstruction.l] <= RF[currInstruction.m])
						RF[currInstruction.r] = 1;
					else
						RF[currInstruction.r] = 0;

					print_execution(currLine, "LEQ", currInstruction, PC+1, BP, SP, stack, RF);
					break;

			case 22: // GTR
				if(RF[currInstruction.l] > RF[currInstruction.m])
					RF[currInstruction.r] = 1;
				else
					RF[currInstruction.r] = 0;

				print_execution(currLine, "GTR", currInstruction, PC+1, BP, SP, stack, RF);
				break;

			case 23: // GEQ
				if(RF[currInstruction.l] >= RF[currInstruction.m])
					RF[currInstruction.r] = 1;
				else
					RF[currInstruction.r] = 0;

				print_execution(currLine, "GEQ", currInstruction, PC+1, BP, SP, stack, RF);
				break;

			default:
				//halt = 0;
				break;

		}

		currLine = PC+1;

		PC++;
	}

}
