// Lab exercise 7
// Write a C program to recognize strings under 'a*', 'a*b+', 'abb'. 
// You can use C or C++ or any other language..
// Pseudo code without syntax...use as guidelines..also search in web.
// Author: Jitin (CS20B1075)
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
int main()
{
	string s;
	char c;
	int state = 0, i = 0;
	printf("\n Enter a string:");
	cin >> s;
	while (s[i] != '\0')
	{
		switch (state)
		{
		case 0:
			c = s[i++];
			if (c == 'a')
				state = 1;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 1:
			c = s[i++];
			if (c == 'a')
				state = 3;
			else if (c == 'b')
				state = 4;
			else
				state = 6;
			break;
		case 2:
			c = s[i++];
			if (c == 'a')
				state = 6;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 3:
			c = s[i++];
			if (c == 'a')
				state = 3;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 4:
			c = s[i++];
			if (c == 'a')
				state = 6;
			else if (c == 'b')
				state = 5;
			else
				state = 6;
			break;
		case 5:
			c = s[i++];
			if (c == 'a')
				state = 6;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 6:
			cout << s << " is not recognized\n";
			exit(0);
		}
	}
	if (state == 1 || state == 3)
		cout << s << " is accepted under rule a*";
	else if ((state == 2) || (state == 4))
		cout << s << " is accepted under rule a*b+";
	else if (state == 5)
		cout << s << " is accepted under rule 'abb'";
	return 0;
}