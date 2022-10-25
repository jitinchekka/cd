// Write a simple C code to remove spaces and new line enter characters of a given input C program.
// Author: Jitin (CS20B1075)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
	// Take stdin from input.txt
	FILE *fp = fopen("input.txt", "r");
	// Take stdout to output.txt
	FILE *fp1 = fopen("output.txt", "w");
	char ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch != ' ' && ch != '\n' && ch != '\t')
		{
			fputc(ch, fp1);
		}
		// if (isgraph(ch))
		// {
		// 	fputc(ch, fp1);
		// }
	}
	fclose(fp);
	fclose(fp1);
	return 0;
}