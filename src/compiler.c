/**
 * @file compiler.c
 *
 * @author Alex Gonzalez (blyxyas@gmail.com)
 * @brief Compiler for the performance based language HQ9+, ABSOLUTELY ESSENTIAL IN EVERY TECH STACK, from Web development to bare-bone pure ASM implementations of block-chained based AI machine learning on the cloud.
 * @warning EXECUTE COMPILER SCRIPT (compile IN UNIX), DON'T EXECUTE THIS SCRIPT DIRECTLY.
 * @version 0.0.1
 * @date 2022-08-26
 *
 * @copyright Copyright (c) 2022
 *
 * @arg
 * * 1: Filename
 * * 2: [Flags] :
 * 				 *	-o [Filename]	Output file
 * 				 *	-c [Compiler]	Compiler to use (gcc, clang or llvm)
 * 				 * 	-h [Directory]	Directory to create the cache.
 * 				 *	-b [Integer]	Number of bottles (New implementation)
 * 				 *	-v 				Verbosity?
 * 				 *	-d				Debug?
 */

#include <stdio.h>
#include <stdlib.h>

// If we're not using clang as a compiler, redefine booleans.
// #ifndef __clang__
#define true 0b11111111
#define false 0b0
#define bool __uint8_t
// #endif

#define ifnLast            \
	if i                   \
		!= (argv_size - 1) \
		{
#define ifLast(part)                  \
	}                                 \
	else                              \
	{                                 \
		printf(#part "is undefined"); \
		return 1;                     \
	}

// So we don't have to import <stdbool.h>

int main(int argc, char *argv[])
{

	const char *filename = argv[0];
	const char *output = argv[1];
	const char *compiler = argv[2];
	const int bottleno = (int)strtol(argv[3], (char **)NULL, 10);

	if (argv[4] == "true")
	{
		const bool verbosity = true;
	}
	else
	{
		const bool verbosity = false;
	}

	if (argv[5] == "true")
	{
		const bool debug = true;
	}
	else
	{
		const bool debug = false;
	}

	FILE *file = fopen(filename, "r");
	char ch;

	if (file == NULL)
	{
		printf("File is not available\n");
		return 1;
	}

	// Create temporary file
	FILE *tmp = tmpfile();
	if (tmp == NULL)
	{
		puts("Unable to create temp file");
		return 1;
	};

	puts("Temporary file was created!\n");

	while ((ch = fgetc(file)) != EOF)
	{
		// MAIN COMPILING
		switch (ch)
		{
		case 'H':
			fputc(1, tmp);
			break;

		case 'Q':
			fputc(2, tmp);
			break;

		case '9':
			fputc(3, tmp);
			break;

		case '+':
			fputc(4, tmp);
			break;

		default:
			break;
		}
	};

	if (compiler == "rust")
	{
		rustCompile(output, tmp, file, bottleno);
	}
	else if (compiler == "gcc" || compiler == "clang" || compiler == "c")
	{
		cCompile(output, tmp, bottleno);
	}

	fclose(file);
	return 0;
}

void rustCompile(char *output, FILE *tmp, FILE *source, int bottleno)
{

	// FILE TO STRING
	char *buffer = 0;
	long length;

	if (source)
	{
		fseek(source, 0, SEEK_END);
		length = ftell(source);
		fseek(source, 0, SEEK_SET);
		buffer = malloc(length);
		if (buffer)
		{
			fread(buffer, 1, length, source);
		}
		fclose(source);
	}

	rewind(tmp);
	FILE *result;

	result = fopen(strcat(output, ".rs"), "w");

	// fputs boilerplate for rust
	fputs("fn main() {\n", result);

	while (!feof(tmp))
	{
		char ch = fgetc(tmp);
		switch (ch)
		{
		case 1: // H
			fputs("println!(\"Hello world!\");\n", result);
			break;

		case 2: // Q
			if (buffer)
			{
				fputs("println!(\"%s\");\n", buffer);
			};
		
		break;
		case 3: // 9
			fputs("let mut currentBottle = 99; while currentBottle <= 1 { println!(\"{} bottles of beer\\nyou take one down, pass it around,\\n{} bottles of beer on the wall\\n\", currentBottle, currentBottle - 1); currentBottle -= 1; } println!(\"{} bottles of beer\\nyou take one down, pass it around,\\nno bottles of beer on the wall\\n\")};\n", result);
		break;

		case 4: // +
			fputs("accumulator += 1;\n", result);
		break;



		default:
			break;
		}
	}

	fputs("}\n", result); // End rust main function
	fclose(tmp);
	fclose(result);
	return 0;
}

void cCompile(char *output, FILE *file, int bottleno)
{
}