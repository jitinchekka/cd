// Lab Exercise 10: C program to implement Simple Machine Code Generator.
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;

// Operator to operation
string op(char oper)
{
	if (oper == '+')
	{
		return "ADD";
	}
	else if (oper == '-')
	{
		return "SUB";
	}
	else if (oper == '*')
	{
		return "MUL";
	}
	else if (oper == '/')
	{
		return "DIV";
	}
	else // if (oper == '%')
	{
		return "MOD";
	}
}

vector<bool> reg(100, false); // Registers
int main()
{
	int n;
	cout << "Enter the number of equations\n";
	cin >> n;
	cout << "Enter the equation without spaces\n";
	vector<string> ans1, ans2, ans3;
	for (int j = 0; j < n; j++)
	{
		string eq; // size of string is 5
		cin >> eq;
		for (int i = 0; i < reg.size(); i++)
		{
			if (!reg[i])
			{
				ans1.push_back("MOV");
				ans2.push_back("R" + to_string(i));
				ans3.push_back(eq.substr(2, 1)); //eq[2]

				ans1.push_back(op(eq[3]));
				ans2.push_back("R" + to_string(i));
				ans3.push_back(eq.substr(4, 1)); //eq[4]

				ans1.push_back("MOV");
				ans2.push_back(eq.substr(0, 1)); //eq[0]
				ans3.push_back("R" + to_string(i));

				reg[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < ans1.size(); i++)
	{
		cout << ans1[i] << "  " << ans2[i] << "  " << ans3[i] << "\n";
	}
	return 0;
}