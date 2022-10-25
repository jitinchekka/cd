// Write a simple C code to remove spaces and new line enter characters and comment lines of a given input C program.
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
		if (isgraph(ch) && ch != '/')
		{
			fputc(ch, fp1);
		}
		//multi line comment
		if (ch == '/' && fgetc(fp) == '*')
		{
			while ((ch = fgetc(fp)) != EOF)
			{
				if (ch == '*' && fgetc(fp) == '/')
				{
					break;
				}
			}
		}
		else if (ch == '/' )
		{
			while (ch != '\n')
			{
				ch = fgetc(fp);
			}
		}
	}
	fclose(fp);
	fclose(fp1);
	return 0;
}