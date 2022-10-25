// Author: Jitin (CS20B1075)
// This code is written in C++ and is used to create a symbol table for C code in input.txt file.
// The symbol table is created in a file named symbol_table.txt.
// Works for codes indented with tabs only or no indentation. "Does not" work for codes indented with spaces.
// Works only for declarative and assignment statements.
#include <bits/stdc++.h>
using namespace std;

// Declare table
map<string, vector<pair<string, string>>> table; // <datatype, <vector of variable name and value>>
// Remove all spaces newlines and tabs from the input file
void lexical_analysis(string filename)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
	{
		cout << "Cannot open file " << filename << endl;
		return;
	}
	string line;
	int line_number = 1;
	int column_number = 1;
	while (getline(file, line))
	{
		// remove #Includes and #Defines
		if (line.find("#") != string::npos)
		{
			line = "";
			cout << "Line " << line_number << "contains #Includes or #Defines" << endl;
		}

		// remove main function
		if (line.find("main") != string::npos)
		{
			line = "";
			cout << "Line " << line_number << "contains main function" << endl;
		}
		// remove comments
		if (line.find("//") != string::npos)
		{
			line = line.substr(0, line.find("//"));
		}
		// remove indentation
		if (line.find("\t") != string::npos)
		{
			line = line.substr(line.find("\t") + 1);
			// cout << "Line " << line_number << "contains tab" << endl;
			// cout << "Line = " << line << endl;
		}
		if (line.length() == 0)
		{
			line_number++;
			column_number = 1;
			continue;
		}
		// remove ; from the end of the line
		if (line.find(";") != string::npos)
		{
			line = line.substr(0, line.find(";"));
		}
		// If the line contains a keyword, add it to the table
		if (line.find("int") != string::npos || line.find("char") != string::npos || line.find("float") != string::npos || line.find("double") != string::npos || line.find("bool") != string::npos)
		{
			// Find the variable type
			string type = "";
			if (line.find("int") != string::npos)
			{
				type = "int";
			}
			else if (line.find("char") != string::npos)
			{
				type = "char";
			}
			else if (line.find("float") != string::npos)
			{
				type = "float";
			}
			else if (line.find("double") != string::npos)
			{
				type = "double";
			}
			else if (line.find("bool") != string::npos)
			{
				type = "bool";
			}
			// Find the variable name
			string name = "";
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					name = line.substr(i + 1, line.length() - i - 1);
					break;
				}
			}
			cout << "Line " << line_number << "contains " << type << " " << name << endl;
			// If name is empty, then it is a declaration without a name
			if (name == "")
			{
				cout << "Line " << line_number << "contains a declaration without a name" << endl;
			}
			// If name contains , then it is a declaration with multiple variables
			else if (name.find(",") != string::npos)
			{
				cout << "Line " << line_number << "contains a declaration with multiple variables" << endl;
				// handle multiple variables
				string temp = name;
				while (temp.find(",") != string::npos)
				{
					string temp1 = temp.substr(0, temp.find(","));
					temp = temp.substr(temp.find(",") + 1, temp.length() - temp.find(",") - 1);
					table[type].push_back(make_pair(temp1, ""));
					cout << "Line " << line_number << "contains " << type << " " << temp1 << endl;
				}
				table[type].push_back(make_pair(temp, ""));
				cout << "Line " << line_number << "contains " << type << " " << temp << endl;
			}
			else
			{
				table[type].push_back(make_pair(name, ""));
			}
		}
		// If the line is an assignment of variable to value
		else if (line.find("=") != string::npos)
		{
			// remove all spaces and tabs from the line
			line.erase(remove(line.begin(), line.end(), ' '), line.end());
			line.erase(remove(line.begin(), line.end(), '\t'), line.end());
			// Find the variable name
			// substring from 0 to the first = sign
			string name = line.substr(0, line.find("="));
			// Find the value
			// substring from the first = sign to the end of the line
			string value = line.substr(line.find("=") + 1, line.length() - line.find("=") - 1);
			// For each variable in the table, if the variable name matches the name in the line, then set the value
			for (auto it = table.begin(); it != table.end(); ++it)
			{
				for (int i = 0; i < it->second.size(); i++)
				{
					if (it->second[i].first == name)
					{
						it->second[i].second = value;
						cout << "Line " << line_number << "contains " << it->first << " " << name << " = " << value << endl;
					}
				}
			}
		}
		line_number++;
		// cout << line << endl;
	}
}
int main()
{
	lexical_analysis("input.txt");
	// Print the table in symbol_table.txt file
	ofstream outfile;
	outfile.open("symbol_table.txt");

	outfile << "Symbol Table:" << endl;
	outfile << "Type\tName\tValue" << endl;
	for (auto it = table.begin(); it != table.end(); ++it)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			outfile << it->first << "\t" << it->second[i].first << "\t" << it->second[i].second << endl;
		}
	}
	return 0;
}