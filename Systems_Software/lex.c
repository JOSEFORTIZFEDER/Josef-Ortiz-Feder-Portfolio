// Josef Ortiz-Feder
// COP 3402 Almalki
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 1000
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5

lexeme *list;
int lex_index;

int alphatoken();
int numbertoken();
int symboltoken();
int comment();
int reservedcheck(char *buffer);
void printlexerror(int type);
void printtokens();
token_type isReservedWord(char* word);



lexeme *lexanalyzer(char *input, int printFlag)
{
	// Declaring variables to be used
	list = malloc(sizeof(lexeme) * MAX_NUMBER_TOKENS);
	char* tempList;
	lexeme newItem;
	lex_index = 0;
	int tempList_index = 0;
	int input_index = 0;
	int temp=0;
	int isComment=0;
	int reservedTemp=0;

	// Big while loop that runs through the given input array
	while(input_index != MAX_NUMBER_TOKENS)
	{
		// tempList to store the identifiers before being passed into the lexeme list
		tempList = malloc(sizeof(char) * MAX_IDENT_LEN);
		tempList_index = 0;
		temp = 0;

		// Check if we are currently in a comment block
		if(isComment == 1)
		{
			//printf("%c", input[input_index]);
			if(input[input_index] == '\n' || input[input_index] == '\0')
			{
				isComment = 0;
			}
			input_index++;
			continue;
		}
		// Check if the current element is a number
		if(isdigit(input[input_index]) != 0)
		{
			temp = 0;
			tempList_index = input_index;

			// Another while loop that runs until the end of the number
			while(isdigit(input[input_index]) != 0)
			{
				temp++;
				input_index++;
			}
			// Test for a number length error
			if(temp > 5)
			{
				printlexerror(2);
				exit(0);
			}

			// Copy the necessary substring from input into the temp list
			strncpy(tempList, &input[tempList_index], temp);

			// Store the numbers into the value and assign the type
			newItem.value = atoi(tempList);
			newItem.type = numbersym;
			list[lex_index] = newItem;

			lex_index++;
			continue;
		}

		// Check if the current element is a letter
		if(isalpha(input[input_index]) != 0)
		{
			temp = 0;
			tempList_index = input_index;

			// Another while loop that runs until the end of the word
			while(isalpha(input[input_index]) != 0)
			{
				temp++;
				input_index++;
			}

			// Check for an identifier length error
			if(temp > 11)
			{
				printlexerror(3);
				exit(0);
			}

			// Copy the necessary info into the name of the new lexeme
			strncpy(tempList, &input[tempList_index], temp);
			strcpy(newItem.name, tempList);
			newItem.type = identsym;

			// isReservedWord function returns the type of the identifier i.e. procsym, ifsym or just identsym
			newItem.type = isReservedWord(tempList);
			list[lex_index] = newItem;
			lex_index++;
			continue;
		}
		// Check for comments
		if(input[input_index] == '/' && input[input_index+1] == '/')
		{
			isComment = 1;
			input_index = input_index + 2;
			continue;
		}

		// A bunch of if statements that check for the special symbols
		if(input[input_index] == ',')
		{
			strcpy(newItem.name, ",");
			newItem.value = 7;
			newItem.type = commasym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == ';')
		{
			strcpy(newItem.name, ";");
			newItem.value = 9;
			newItem.type = semicolonsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == ':' && input[input_index+1] == '=')
		{
			strcpy(newItem.name, ":=");
			newItem.value = 11;
			newItem.type = assignsym;
			list[lex_index] = newItem;
			lex_index++;
			input_index = input_index+2;
			continue;
		}
		if(input[input_index] == ':')
		{
			strcpy(newItem.name, ":");
			newItem.value = 15;
			newItem.type = colonsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '[')
		{
			strcpy(newItem.name, "[");
			newItem.value = 3;
			newItem.type = lbracketsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == ']')
		{
			strcpy(newItem.name, "]");
			newItem.value = 5;
			newItem.type = rbracketsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '(')
		{
			strcpy(newItem.name, "(");
			newItem.value = 17;
			newItem.type = lparenthesissym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == ')')
		{
			strcpy(newItem.name, ")");
			newItem.value = 19;
			newItem.type = rparenthesissym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '*')
		{
			strcpy(newItem.name, "*");
			newItem.value = 28;
			newItem.type = multsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '/' && input[input_index+1] != '/')
		{
			strcpy(newItem.name, "/");
			newItem.value = 26;
			newItem.type = divsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '+')
		{
			strcpy(newItem.name, "+");
			newItem.value = 32;
			newItem.type = addsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '-')
		{
			strcpy(newItem.name, "-");
			newItem.value = 30;
			newItem.type = subsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '%')
		{
			strcpy(newItem.name, "%");
			newItem.value = 24;
			newItem.type = modsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '?')
		{
			strcpy(newItem.name, "?");
			newItem.value = 13;
			newItem.type = questionsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '=' && input[input_index+1] == '=')
		{
			strcpy(newItem.name, "==");
			newItem.value = 21;
			newItem.type = eqlsym;
			list[lex_index] = newItem;
			lex_index++;
			input_index++;
		}
		if(input[input_index] == '<' && input[input_index+1] == '>')
		{
			strcpy(newItem.name, "<>");
			newItem.value = 23;
			newItem.type = neqsym;
			list[lex_index] = newItem;
			lex_index++;
			input_index = input_index+2;
			continue;
		}
		if(input[input_index] == '<' && input[input_index+1] == '=')
		{
			strcpy(newItem.name, "<=");
			newItem.value = 27;
			newItem.type = leqsym;
			list[lex_index] = newItem;
			lex_index++;
			input_index = input_index+2;
			continue;
		}
		if(input[input_index] == '>' && input[input_index+1] == '=')
		{
			strcpy(newItem.name, ">=");
			newItem.value = 31;
			newItem.type = geqsym;
			list[lex_index] = newItem;
			lex_index++;
			input_index = input_index+2;
			continue;
		}
		if(input[input_index] == '<')
		{
			strcpy(newItem.name, "<");
			newItem.value = 25;
			newItem.type = lsssym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '>')
		{
			strcpy(newItem.name, ">");
			newItem.value = 29;
			newItem.type = gtrsym;
			list[lex_index] = newItem;
			lex_index++;
		}
		if(input[input_index] == '.')
		{
			strcpy(newItem.name, ".");
			newItem.value = 1;
			newItem.type = periodsym;
			list[lex_index] = newItem;
			lex_index++;
		}



		input_index++;
		free(tempList);
	}

	//printf("%s", input);

	if (printFlag)
		printtokens();
	list[lex_index++].type = -1;
	return list;
}

// isReservedWord function that takes in a word to be checked.
// Returns the token_type of the input
token_type isReservedWord(char* word)
{
	if(strcmp(word, "var")==0)
	{
		return varsym;
	}
	if(strcmp(word, "procedure")==0)
	{
		return procsym;

	}

	if(strcmp(word, "call")==0)
		return callsym;

	if(strcmp(word, "begin")==0)
		return beginsym;

	if(strcmp(word, "end")==0)
		return endsym;

	if(strcmp(word, "if")==0)
		return ifsym;

	if(strcmp(word, "do")==0)
		return dosym;

	if(strcmp(word, "while")==0)
		return whilesym;

	if(strcmp(word, "read")==0)
		return readsym;

	if(strcmp(word, "write")==0)
		return writesym;

	return identsym;
}

void printtokens()
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
	for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case lbracketsym:
				printf("%11s\t%d", "[", lbracketsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case rbracketsym:
				printf("%11s\t%d", "]", rbracketsym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case questionsym:
				printf("%11s\t%d", "?", questionsym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case colonsym:
				printf("%11s\t%d", ":", colonsym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case lparenthesissym:
				printf("%11s\t%d", "(", lparenthesissym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case rparenthesissym:
				printf("%11s\t%d", ")", rparenthesissym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
			case neqsym:
				printf("%11s\t%d", "<>", neqsym);
				break;
			case modsym:
				printf("%11s\t%d", "%", modsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case subsym:
				printf("%11s\t%d", "-", subsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case addsym:
				printf("%11s\t%d", "+", addsym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			default:
				printf("%11s\t%s", "err", "err");
				break;
		}
		printf("\n");
	}
	printf("\n");
}

void printlexerror(int type)
{
	if (type == 1)
		printf("Lexical Analyzer Error: Invalid Identifier\n");
	else if (type == 2)
		printf("Lexical Analyzer Error: Number Length\n");
	else if (type == 3)
		printf("Lexical Analyzer Error: Identifier Length\n");
	else if (type == 4)
		printf("Lexical Analyzer Error: Invalid Symbol\n");
	else
		printf("Implementation Error: Unrecognized Error Type\n");

	free(list);
	return;
}
