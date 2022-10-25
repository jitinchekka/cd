// Author: Jitin (CS20B1075)
#include <stdio.h>
int main()
{
	FILE *ptr;
	char ch;

	ptr = fopen("input.txt", "r");

	if (NULL == ptr)
	{
		printf("file can't be opened \n");
	}

	char arr[100][100];
	int row = 0, col = 0, flag = 0;
	while (ch != EOF)
	{
		ch = fgetc(ptr);
		if (ch != ' ' && ch != '\n' && ch != '\t')
		{
			arr[row][col] = ch;
			col++;
			flag = 0;
		}
		if (flag == 0 && (ch == ' ' || ch == '\n' || ch == '\t'))
		{
			arr[row][col] = '\0';
			col = 0;
			row++;
			flag = 1;
		}
	}
	arr[row][col] = '\0';

	for (int i = 0; i < row; i++)
	{
		int j = 0;
		while (arr[i][j] != '\0')
		{
			printf("%c", arr[i][j]);
			j++;
		}
		printf("\n");
	}

	return 0;
}