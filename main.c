#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS 1
	#define restrict __restrict
#endif

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "expression.h"
#include "utils.h"
#include "exitcodes.h"
#include "nodestack.h"
#include "debugs.h"

#define INPUT_ARG_FLAG "/i"
#define OUTPUT_ARG_FLAG "/o"

#define MAX_NUM_EXPRESSIONS 100

int64_t my_getline(char **restrict line, size_t *restrict len, FILE *restrict fp) {
	int origPointer = ftell(fp);
	
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, origPointer, SEEK_SET);
     // Check if either line, len or fp are NULL pointers
     if(line == NULL || len == NULL || fp == NULL) {
         errno = EINVAL;
         return -1;
     }
     
     // Use a chunk array of 128 bytes as parameter for fgets
     char chunk[128];
 
     // Allocate a block of memory for *line if it is NULL or smaller than the chunk array
     if(*line == NULL || *len < sizeof(chunk)) {
         *len = sizeof(chunk);
         if((*line = malloc(*len)) == NULL) {
             errno = ENOMEM;
             return -1;
         }
     }
 
     // "Empty" the string
     (*line)[0] = '\0';
 
     while(fgets(chunk, sizeof(chunk), fp) != NULL) {
         // Resize the line buffer if necessary
         size_t len_used = strlen(*line);
         size_t chunk_used = strlen(chunk);
 
         if(*len - len_used < chunk_used) {
             // Check for overflow
             if(*len > SIZE_MAX / 2) {
                 errno = EOVERFLOW;
                 return -1;
             } else {
                 *len *= 2;
             }
             
             if((*line = realloc(*line, *len)) == NULL) {
                 errno = ENOMEM;
                return -1;
             }
         }
 
         // Copy the chunk to the end of the line buffer
         memcpy(*line + len_used, chunk, chunk_used);
         len_used += chunk_used;
         (*line)[len_used] = '\0';
 
         // Check if *line contains '\n', if yes, return the *line length
         if((*line)[len_used - 1] == '\n' || ftell(fp) == sz) {
             return len_used;
         }
     }
 
     return -1;
 }


int main(int argc, char* argv[])
{
	char* inputFilePath = NULL;
	char* outputFilePath = NULL;

	FILE* inputFile = NULL;
	FILE* outputFile = NULL;

	int isReadingFromFile = 0;
	int isWritingToFile = 0;

	EXPRESSION* expressionDatabase[MAX_NUM_EXPRESSIONS] = { 0 };
	int numExpressions = 0;

	if (argc != 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (!strcmp(INPUT_ARG_FLAG,argv[i]))
			{
				if (i == argc-1 || !strcmp(argv[i+1], OUTPUT_ARG_FLAG))
				{
					error("Empty input file parameter!");
					exit(BAD_ARG_ERR_CODE);
				}

				inputFilePath = calloc(strlen(argv[i+1]) + 1,sizeof(char));
				strcpy_s(inputFilePath, strlen(argv[i+1]) + 1, argv[i+1]);
				isReadingFromFile = 1;
				i++;
				continue;
			}

			if (!strcmp(OUTPUT_ARG_FLAG, argv[i]))
			{
				if (i == argc - 1 || !strcmp(argv[i + 1], INPUT_ARG_FLAG))
				{
					error("Empty output file parameter!");
					exit(BAD_ARG_ERR_CODE);
				}

				outputFilePath = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
				strcpy_s(outputFilePath, strlen(argv[i + 1]) + 1, argv[i + 1]);
				isWritingToFile = 1;
				i++;
				continue;
			}
		}
	}

	printf("Output file path: %s\n",outputFilePath);
	printf("Input file path: %s\n",inputFilePath);

	inputFile = fopen(inputFilePath,"r");
	if (inputFile == NULL && isReadingFromFile == 1)
	{
		printf("Error opening file: %s\n", inputFilePath);
		exit(INVALID_FILE_PATH_ERR_CODE);
	}

	outputFile = fopen(outputFilePath, "w");
	if (outputFile == NULL && isWritingToFile == 1)
	{
		printf("Error opening file: %s\n", inputFilePath);
		exit(INVALID_FILE_PATH_ERR_CODE);
	}

	char* line = NULL;
	size_t len = 0;

	if (isReadingFromFile)
	{
		while (my_getline(&line,&len,inputFile)!= -1)
		{
			if (line[0] == '\n')
			{
				continue;
			}
			expressionDatabase[numExpressions] = initExpressionFromString(line);
			numExpressions++;
			//printf("Line: %s\n",line);
		}
	}

	for (int i = 0; i < numExpressions; i++ )
	{
		if(expressionDatabase[i]->isRoot != 1)
		{
			printf("%s = %s\n", expressionDatabase[i]->varName, expressionDatabase[i]->expression);
			fprintf(outputFile,"%s = %s\n", expressionDatabase[i]->varName, expressionDatabase[i]->expression);
		}
	}

	printf("\nSolving roots: \n\n");
	fprintf(outputFile,"\nSolving roots: \n\n");

	for (int i = 0; i < numExpressions; i++)
	{
		if (expressionDatabase[i]->isRoot == 1)
		{
			printf("%s = ",expressionDatabase[i]->expression);
			fprintf(outputFile,"%s = ", expressionDatabase[i]->expression);
			complexDouble result = solve(expressionDatabase[i],&expressionDatabase,numExpressions);
			expressionDatabase[i]->result = result;
			printf("%lf + %lfi\n",result._Val[0],result._Val[1]);
			fprintf(outputFile,"%lf + %lfi\n", result._Val[0], result._Val[1]);
		}
	}
}