// Josef Ortiz-Feder
// COP 3402 Almalki
// Project 3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"

#define MAX_CODE_LENGTH 200
#define MAX_SYMBOL_COUNT 50
#define MAX_REG_COUNT 10

// generated code
instruction *code;
int cIndex;

// symbol table
symbol *table;
int tIndex;

// lex list
lexeme *lexList;
int listIndex;

// extra globals to keep track of levels and counters
int level;
int registerCounter;

void emit(int opname, int reg, int level, int mvalue);
void addToSymbolTable(int k, char n[], int s, int l, int a, int m);
void mark();
int multipledeclarationcheck(char name[]);
int findsymbol(char name[], int kind);
void printparseerror(int err_code);
void printsymboltable();
void printassemblycode();

// These functions as well as parse is what I implemented
void block();
int var_declaration();
void procedure_declaration();
void statement();
void condition();
void expression();
void term();
void factor();

// parse function that starts the parsing process
instruction *parse(lexeme *list, int printTable, int printCode)
{
	// set up program variables
	code = malloc(sizeof(instruction) * MAX_CODE_LENGTH);
	cIndex = 0;
	table = malloc(sizeof(symbol) * MAX_SYMBOL_COUNT);
	tIndex = 0;
	lexList = list;
	listIndex = 0;
	registerCounter = -1;
	emit(7, 0, 0, 0);
	addToSymbolTable(3, "main", 0, 0, 0, 0);
	level = -1;
	block();
	if(lexList[listIndex].type != periodsym)
	{
		printparseerror(1);
	}
	emit(11, 0, 0, 0);
	code[0].m = table[0].addr;
	for(int i = 0; i < cIndex; ++i)
	{
		if(code[i].opcode == 5)
		{
			code[i].m = table[code[i].m].addr;
		}
	}

	// print off table and code
	if (printTable)
		printsymboltable();
	if (printCode)
		printassemblycode();

	// mark the end of the code
	code[cIndex].opcode = -1;
	return code;
}
// block function that runs for each "block" in a program: the level variable increments whenever it enters block and decrements when it leaves
void block()
{
	level = level+1;
	int procedureIndex = tIndex-1;
	int x = var_declaration();
	procedure_declaration();
	table[procedureIndex].addr = cIndex;
	emit(6, 0, 0, x);
	statement();
	mark();
	level = level -1;
}
// var_declaration function that checks if the var name you want to declare is valid
int var_declaration()
{
	int memSize = 3;
	char* symbolName;
	int arrSize;
	if(lexList[listIndex].type == varsym)
	{
		do {
			listIndex = listIndex +1;
			if(lexList[listIndex].type != identsym)
			{
				printparseerror(2);
			}
			if(multipledeclarationcheck(lexList[listIndex].name) != -1)
			{
				printparseerror(3);
			}
			symbolName = lexList[listIndex].name;
			listIndex = listIndex + 1;
			if(lexList[listIndex].type == lbracketsym)
			{
				listIndex = listIndex + 1;
				if(lexList[listIndex].type != numbersym || lexList[listIndex].value == 0)
				{
					printparseerror(4);
				}
				arrSize = lexList[listIndex].value;
				listIndex = listIndex + 1;
				if(lexList[listIndex].type == multsym || lexList[listIndex].type == divsym || lexList[listIndex].type == modsym || lexList[listIndex].type == addsym || lexList[listIndex].type == subsym)
				{
					printparseerror(4);
				}
				else if(lexList[listIndex].type != rbracketsym)
				{
					printparseerror(5);
				}
				listIndex = listIndex + 1;
				addToSymbolTable(2, symbolName, arrSize, level, memSize, 0);
				memSize = memSize + arrSize;
			}
			else
			{
				addToSymbolTable(1, symbolName, 0, level, memSize, 0);
				memSize = memSize + 1;
			}
		} while(lexList[listIndex].type == commasym);
		if(lexList[listIndex].type == identsym)
		{
			printparseerror(6);
		}
		else if(lexList[listIndex].type != semicolonsym)
		{
			printparseerror(7);
		}
		listIndex = listIndex + 1;
		return memSize;
	}
	else
	{
		return memSize;
	}
}
// procedure_declaration function that checks to see if the procedure you want to declare is valid
void procedure_declaration()
{
	char* symbolName;
	while(lexList[listIndex].type == procsym)
	{
		listIndex = listIndex + 1;
		if(lexList[listIndex].type != identsym)
		{
			printparseerror(2);
		}
		else if(multipledeclarationcheck(lexList[listIndex].name) != -1)
		{
			printparseerror(3);
		}
		symbolName = lexList[listIndex].name;
		listIndex = listIndex + 1;
		if(lexList[listIndex].type != semicolonsym)
		{
			printparseerror(8);
		}
		listIndex = listIndex + 1;
		addToSymbolTable(3, symbolName, 0, level, 0, 0);
		block();
		if(lexList[listIndex].type != semicolonsym)
		{
			printparseerror(7);
		}
		listIndex = listIndex + 1;
		emit(2, 0, 0, 0);
	}
}
// statement function that will use recursion to go through every line of code (wherever specified by block) and process
void statement()
{
	char* symbolName;
	int symIdx, arrIdxReg, varlocreg, jpcIdx, jmpIdx, loopIdx;

	if(lexList[listIndex].type == identsym)
	{
		symbolName = lexList[listIndex].name;
		listIndex = listIndex + 1;
		if(lexList[listIndex].type == lbracketsym)
		{
			listIndex = listIndex + 1;
			symIdx = findsymbol(symbolName, 2);
			if(symIdx == -1)
			{
				if(findsymbol(symbolName, 1) != -1)
				{
					printparseerror(11);
				}
				else if(findsymbol(symbolName, 3) != -1)
				{
					printparseerror(9);
				}
				else
				{
					printparseerror(10);
				}
			}
			expression();// check later
			arrIdxReg = registerCounter;
			if(lexList[listIndex].type != rbracketsym)
			{
				printparseerror(5);
			}
			listIndex = listIndex + 1;
			if(lexList[listIndex].type != assignsym)
			{
				printparseerror(13);
			}
			listIndex = listIndex + 1;
			expression(); // check later
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(1, registerCounter, 0, table[symIdx].addr);
			emit(13, arrIdxReg, arrIdxReg, registerCounter);
			registerCounter = registerCounter - 1;
			emit(4, registerCounter, level - table[symIdx].level, arrIdxReg);

			registerCounter = registerCounter - 2;
		}
		else
		{
			symIdx = findsymbol(symbolName, 1);
			if(symIdx == -1)
			{
				if(findsymbol(symbolName, 2) != -1)
				{
					printparseerror(12);
				}
				else if(findsymbol(symbolName, 3) != -1)
				{
					printparseerror(9);
				}
				else
				{
					printparseerror(10);
				}

			}
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(1, registerCounter, 0, table[symIdx].addr);
			varlocreg = registerCounter;
			if(lexList[listIndex].type != assignsym) // problem child could be wrong check video
			{
				printparseerror(13);
			}
			listIndex = listIndex + 1;
			expression();
			emit(4, registerCounter, level - table[symIdx].level, varlocreg);
			registerCounter = registerCounter - 2;
		}
	}
	else if(lexList[listIndex].type == callsym)
	{
		listIndex = listIndex + 1;
		if(lexList[listIndex].type != identsym)
		{
			printparseerror(15);
		}
		symIdx = findsymbol(lexList[listIndex].name, 3);
		if(symIdx == -1)
		{
			if(findsymbol(lexList[listIndex].name, 1) != -1 || findsymbol(lexList[listIndex].name, 2) != -1)
			{
				printparseerror(15);
			}
			else
			{
				printparseerror(10);
			}
		}
		emit(5, 0, level - table[symIdx].level, symIdx);
		listIndex = listIndex + 1;
	}
	else if(lexList[listIndex].type == beginsym) // could also be or endsym
	{
		do
		{
			listIndex = listIndex + 1;
			statement();
		}while(lexList[listIndex].type == semicolonsym);
		if(lexList[listIndex].type != endsym)
		{
			if(lexList[listIndex].type == identsym || lexList[listIndex].type == callsym || lexList[listIndex].type == beginsym || lexList[listIndex].type == ifsym || lexList[listIndex].type == dosym || lexList[listIndex].type == readsym || lexList[listIndex].type == writesym)
			{
				//printf("%s", lexList[listIndex].name);
				printparseerror(16);
			}
			else
			{
				printparseerror(17);
			}
		}
		listIndex = listIndex + 1;
	}
	else if(lexList[listIndex].type == ifsym)
	{
		listIndex = listIndex + 1;
		condition();
		jpcIdx = cIndex;
		emit(8, registerCounter, 0, 0);
		registerCounter = registerCounter - 1;
		if(lexList[listIndex].type != questionsym)
		{
			printparseerror(18);
		}
		listIndex = listIndex + 1;
		statement();
		if(lexList[listIndex].type == colonsym)
		{
			listIndex = listIndex + 1;
			jmpIdx = cIndex;
			emit(7, 0, 0, 0);
			code[jpcIdx].m = cIndex;
			statement();
			code[jmpIdx].m = cIndex;
		}
		else
		{
			code[jpcIdx].m = cIndex;
		}
	}

	else if(lexList[listIndex].type == dosym)
	{
		listIndex = listIndex + 1;
		loopIdx = cIndex;
		statement();
		if(lexList[listIndex].type != whilesym)
		{
			printparseerror(19);
		}
		listIndex = listIndex + 1;
		condition();
		registerCounter = registerCounter + 1;
		if(registerCounter >= 10)
		{
			printparseerror(14);
		}
		emit(1, registerCounter, 0, 0);
		emit(18, registerCounter-1, registerCounter-1, registerCounter);
		registerCounter = registerCounter - 1;
		emit(8, registerCounter, 0, loopIdx);
		registerCounter = registerCounter - 1;
	}

	else if(lexList[listIndex].type == readsym)
	{
		listIndex = listIndex + 1;
		if(lexList[listIndex].type != identsym)
		{
			printparseerror(20);
		}
		symbolName = lexList[listIndex].name;
		listIndex = listIndex + 1;

		if(lexList[listIndex].type == lbracketsym)
		{
			listIndex = listIndex + 1;
			symIdx = findsymbol(symbolName, 2);
			if(symIdx == -1)
			{
				if(findsymbol(symbolName, 1) != -1)
				{
					printparseerror(11);
				}
				else if(findsymbol(symbolName, 3) != -1)
				{
					printparseerror(9);
				}
				else
				{
					printparseerror(10);
				}
			}
			expression();
			arrIdxReg = registerCounter;
			if(lexList[listIndex].type != rbracketsym)
			{
				printparseerror(5);
			}
			listIndex = listIndex + 1;
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(10, registerCounter, 0, 0);
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(1, registerCounter, 0, table[symIdx].addr);
			emit(13, arrIdxReg, arrIdxReg, registerCounter);
			registerCounter = registerCounter -1;
			emit(4, registerCounter, level - table[symIdx].level, arrIdxReg);
			registerCounter = registerCounter -2;
		}
		else
		{
			symIdx = findsymbol(symbolName, 1);
			if(symIdx == -1)
			{
				if(findsymbol(symbolName, 2) != -1)
				{
					printparseerror(12);
				}
				else if(findsymbol(symbolName, 3) != -1)
				{
					printparseerror(9);
				}
				else
				{
					printparseerror(10);
				}
			}
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(1, registerCounter, 0, table[symIdx].addr);
			varlocreg = registerCounter;
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(10, registerCounter, 0, 0);
			emit(4, registerCounter, level-table[symIdx].level, varlocreg);
			registerCounter = registerCounter -2;
		}
	}
	else if(lexList[listIndex].type == writesym)
	{
		listIndex = listIndex + 1;
		expression();
		emit(9, registerCounter, 0, 0);
		registerCounter = registerCounter - 1;
	}

	else
	{
		//return;
	}

}
// condition function that checks for conditional processes ex: (<=, >=, ==, >, < , != )
void condition()
{
	expression();
	if(lexList[listIndex].type == eqlsym)
	{
		listIndex = listIndex + 1;
		expression();
		emit(18, registerCounter - 1, registerCounter - 1, registerCounter);
		registerCounter = registerCounter -1;
	}
	else if(lexList[listIndex].type == neqsym)
	{
		listIndex = listIndex + 1;
		expression();
		emit(19, registerCounter -1, registerCounter - 1, registerCounter);
		registerCounter = registerCounter -1;
	}
	else if(lexList[listIndex].type == lsssym)
	{
		listIndex = listIndex + 1;
		expression();
		emit(20, registerCounter -1, registerCounter - 1, registerCounter);
		registerCounter = registerCounter -1;
	}
	else if(lexList[listIndex].type == leqsym)
	{
		listIndex = listIndex + 1;
		expression();
		emit(21, registerCounter -1, registerCounter - 1, registerCounter);
		registerCounter = registerCounter -1;
	}
	else if(lexList[listIndex].type == gtrsym)
	{
		listIndex = listIndex + 1;
		expression();
		emit(22, registerCounter -1, registerCounter - 1, registerCounter);
		registerCounter = registerCounter -1;
	}
	else if(lexList[listIndex].type == geqsym)
	{
		listIndex = listIndex + 1;
		expression();
		emit(23, registerCounter -1, registerCounter - 1, registerCounter);
		registerCounter = registerCounter -1;
	}
	else
	{
		printparseerror(21);
	}
}
// expression function that checks for addition and subtraction operations
void expression()
{
	if(lexList[listIndex].type == subsym)
	{
		listIndex = listIndex + 1;
		term();
		emit(12, registerCounter, 0, registerCounter);
		while(lexList[listIndex].type == addsym || lexList[listIndex].type == subsym)
		{
			if(lexList[listIndex].type == addsym)
			{
				listIndex = listIndex + 1;
				term();
				emit(13, registerCounter -1, registerCounter -1, registerCounter);
				registerCounter = registerCounter - 1;
			}
			else
			{
				listIndex = listIndex + 1;
				term();
				emit(14, registerCounter-1, registerCounter -1, registerCounter);
				registerCounter = registerCounter -1;
			}
		}
	}
	else
	{
		term();
		while(lexList[listIndex].type == addsym || lexList[listIndex].type == subsym)
		{
			if(lexList[listIndex].type == addsym)
			{
				listIndex = listIndex + 1;
				term();
				emit(13, registerCounter -1, registerCounter -1, registerCounter);
				registerCounter = registerCounter - 1;
			}
			else
			{
				listIndex = listIndex + 1;
				term();
				emit(14, registerCounter-1, registerCounter -1, registerCounter);
				registerCounter = registerCounter -1;
			}
		}
	}
	if(lexList[listIndex].type == lparenthesissym || lexList[listIndex].type == identsym || lexList[listIndex].type == numbersym)
	{
		printparseerror(22);
	}
}
// term function that checks for multiplication, division, and modulus operations
void term()
{
	factor();
	while(lexList[listIndex].type == multsym || lexList[listIndex].type == divsym || lexList[listIndex].type == modsym)
	{
		if(lexList[listIndex].type == multsym)
		{
			listIndex = listIndex + 1;
			factor();
			emit(15, registerCounter -1, registerCounter -1, registerCounter);
			registerCounter = registerCounter -1;
		}
		else if(lexList[listIndex].type == divsym)
		{
			listIndex = listIndex + 1;
			factor();
			emit(16, registerCounter -1, registerCounter -1, registerCounter);
			registerCounter = registerCounter -1;
		}
		else
		{
			listIndex = listIndex + 1;
			factor();
			emit(17, registerCounter -1, registerCounter -1, registerCounter);
			registerCounter = registerCounter -1;
		}
	}
}

void factor()
{
	char* symbolName;
	int symIdx, arrIdxReg, varlocreg;

	if(lexList[listIndex].type == identsym)
	{
		symbolName = lexList[listIndex].name;
		listIndex = listIndex + 1;
		if(lexList[listIndex].type == lbracketsym)
		{
			listIndex = listIndex + 1;
			symIdx = findsymbol(symbolName, 2);
			if(symIdx == -1)
			{
				if(findsymbol(symbolName, 1) != -1)
				{
					printparseerror(11);
				}
				else if(findsymbol(symbolName, 3) != -1)
				{
					printparseerror(9);
				}
				else
				{
					printparseerror(10);
				}
			}
			expression();
			arrIdxReg = registerCounter;
			if(lexList[listIndex].type != rbracketsym)
			{
				printparseerror(5);
			}
			listIndex = listIndex + 1;
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(1, registerCounter, 0, table[symIdx].addr);
			emit(13, arrIdxReg, arrIdxReg, registerCounter);
			registerCounter = registerCounter -1;

			emit(3, registerCounter, level - table[symIdx].level, arrIdxReg);

		}
		else
		{
			symIdx	= findsymbol(symbolName, 1);
			if(symIdx == -1)
			{
				if(findsymbol(symbolName, 2) != -1)
				{
					printparseerror(12);
				}
				else if(findsymbol(symbolName, 3) != -1)
				{
					printparseerror(9);
				}
				else
				{
					printparseerror(10);
				}

			}
			registerCounter = registerCounter + 1;
			if(registerCounter >= 10)
			{
				printparseerror(14);
			}
			emit(1, registerCounter, 0, table[symIdx].addr);
			varlocreg = registerCounter;
			emit(3, registerCounter, level-table[symIdx].level, varlocreg);
		}
	}
	else if(lexList[listIndex].type == numbersym)
	{
		registerCounter = registerCounter + 1;
		if(registerCounter >= 10)
		{
			printparseerror(14);
		}
		emit(1, registerCounter, 0, lexList[listIndex].value);
		listIndex = listIndex + 1;
	}
	else if(lexList[listIndex].type == lparenthesissym)
	{
		listIndex = listIndex + 1;
		expression();
		if(lexList[listIndex].type != rparenthesissym)
		{
			printparseerror(23);
		}
		listIndex = listIndex + 1;
	}
	else
	{
		printparseerror(24);
	}
}
void emit(int opname, int reg, int level, int mvalue)
{
	code[cIndex].opcode = opname;
	code[cIndex].r = reg;
	code[cIndex].l = level;
	code[cIndex].m = mvalue;
	cIndex++;
}

void addToSymbolTable(int k, char n[], int s, int l, int a, int m)
{
	table[tIndex].kind = k;
	strcpy(table[tIndex].name, n);
	table[tIndex].size = s;
	table[tIndex].level = l;
	table[tIndex].addr = a;
	table[tIndex].mark = m;
	tIndex++;
}

void mark()
{
	int i;
	for (i = tIndex - 1; i >= 0; i--)
	{
		if (table[i].mark == 1)
			continue;
		if (table[i].level < level)
			return;
		table[i].mark = 1;
	}
}

int multipledeclarationcheck(char name[])
{
	int i;
	for (i = 0; i < tIndex; i++)
		if (table[i].mark == 0 && table[i].level == level && strcmp(name, table[i].name) == 0)
			return i;
	return -1;
}

int findsymbol(char name[], int kind)
{
	int i;
	int max_idx = -1;
	int max_lvl = -1;
	for (i = 0; i < tIndex; i++)
	{
		if (table[i].mark == 0 && table[i].kind == kind && strcmp(name, table[i].name) == 0)
		{
			if (max_idx == -1 || table[i].level > max_lvl)
			{
				max_idx = i;
				max_lvl = table[i].level;
			}
		}
	}
	return max_idx;
}

void printparseerror(int err_code)
{
	switch (err_code)
	{
		case 1:
			printf("Parser Error: Program must be closed by a period\n");
			break;
		case 2:
			printf("Parser Error: Symbol names must be identifiers\n");
			break;
		case 3:
			printf("Parser Error: Confliciting symbol declarations\n");
			break;
		case 4:
			printf("Parser Error: Array sizes must be given as a single, nonzero number\n");
			break;
		case 5:
			printf("Parser Error: [ must be followed by ]\n");
			break;
		case 6:
			printf("Parser Error: Multiple symbols in var declaration must be separated by commas\n");
			break;
		case 7:
			printf("Parser Error: Symbol declarations should close with a semicolon\n");
			break;
		case 8:
			printf("Parser Error: Procedure declarations should contain a semicolon before the body of the procedure begins\n");
			break;
		case 9:
			printf("Parser Error: Procedures may not be assigned to, read, or used in arithmetic\n");
			break;
		case 10:
			printf("Parser Error: Undeclared identifier\n");
			break;
		case 11:
			printf("Parser Error: Variables cannot be indexed\n");
			break;
		case 12:
			printf("Parserr Error: Arrays must be indexed\n");
			break;
		case 13:
			printf("Parser Error: Assignment operator missing\n");
			break;
		case 14:
			printf("Parser Error: Register Overflow Error\n");
			break;
		case 15:
			printf("Parser Error: call must be followed by a procedure identifier\n");
			break;
		case 16:
			printf("Parser Error: Statements within begin-end must be separated by a semicolon\n");
			break;
		case 17:
			printf("Parser Error: begin must be followed by end\n");
			break;
		case 18:
			printf("Parser Error: if must be followed by ?\n");
			break;
		case 19:
			printf("Parser Error: do must be followed by while\n");
			break;
		case 20:
			printf("Parser Error: read must be followed by a var or array identifier\n");
			break;
		case 21:
			printf("Parser Error: Relational operator missing from condition\n");
			break;
		case 22:
			printf("Parser Error: Bad arithmetic\n");
			break;
		case 23:
			printf("Parser Error: ( must be followed by )\n");
			break;
		case 24:
			printf("Parser Error: Arithmetic expressions may only contain arithmetic operators, numbers, parentheses, and variables\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
			break;
	}

	free(code);
	free(table);
	exit(0);
}

void printsymboltable()
{
	int i;
	printf("Symbol Table:\n");
	printf("Kind | Name        | Size | Level | Address | Mark\n");
	printf("---------------------------------------------------\n");
	for (i = 0; i < tIndex; i++)
		printf("%4d | %11s | %5d | %4d | %5d | %5d\n", table[i].kind, table[i].name, table[i].size, table[i].level, table[i].addr, table[i].mark);

	free(table);
	table = NULL;
}

void printassemblycode()
{
	int i;
	printf("Line\tOP Code\tOP Name\tR\tL\tM\n");
	for (i = 0; i < cIndex; i++)
	{
		printf("%d\t", i);
		printf("%d\t", code[i].opcode);
		switch (code[i].opcode)
		{
			case 1:
				printf("LIT\t");
				break;
			case 2:
				printf("RET\t");
				break;
			case 3:
				printf("LOD\t");
				break;
			case 4:
				printf("STO\t");
				break;
			case 5:
				printf("CAL\t");
				break;
			case 6:
				printf("INC\t");
				break;
			case 7:
				printf("JMP\t");
				break;
			case 8:
				printf("JPC\t");
				break;
			case 9:
				printf("WRT\t");
				break;
			case 10:
				printf("RED\t");
				break;
			case 11:
				printf("HLT\t");
				break;
			case 12:
				printf("NEG\t");
				break;
			case 13:
				printf("ADD\t");
				break;
			case 14:
				printf("SUB\t");
				break;
			case 15:
				printf("MUL\t");
				break;
			case 16:
				printf("DIV\t");
				break;
			case 17:
				printf("MOD\t");
				break;
			case 18:
				printf("EQL\t");
				break;
			case 19:
				printf("NEQ\t");
				break;
			case 20:
				printf("LSS\t");
				break;
			case 21:
				printf("LEQ\t");
				break;
			case 22:
				printf("GTR\t");
				break;
			case 23:
				printf("GEQ\t");
				break;
			default:
				printf("err\t");
				break;
		}
		printf("%d\t%d\t%d\n", code[i].r, code[i].l, code[i].m);
	}

	if (table != NULL)
		free(table);
}
