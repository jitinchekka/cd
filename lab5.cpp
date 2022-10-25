// Generate symbol table for C++ program
#include <bits/stdc++.h>
using namespace std;
// Token types
enum TokenType
{
	IDENT,
	NUMBER,
	STRING,
	OPERATOR,
	KEYWORD,
	PUNCTUATOR,
	END_OF_FILE
};
// Token class
class Token
{
public:
	TokenType type;
	string value;
	int line;
	int column;
	Token(TokenType type, string value, int line, int column)
	{
		this->type = type;
		this->value = value;
		this->line = line;
		this->column = column;
	}
};
// Symbol class
class Symbol
{
public:
	string name;
	TokenType type;
	int line;
	int column;
	Symbol(string name, TokenType type, int line, int column)
	{
		this->name = name;
		this->type = type;
		this->line = line;
		this->column = column;
	}
};
// Symbol table class
class SymbolTable
{
public:
	map<string, Symbol> table;
	SymbolTable()
	{
		table.clear();
	}
	void add(string name, TokenType type, int line, int column)
	{
		table[name] = Symbol(name, type, line, column);
	}
	Symbol *find(string name)
	{
		if (table.find(name) != table.end())
		{
			return &table[name];
		}
		return NULL;
	}
	void print()
	{
		for (map<string, Symbol>::iterator it = table.begin(); it != table.end(); ++it)
		{
			cout << it->second.name << " " << it->second.type << " " << it->second.line << " " << it->second.column << endl;
		}
	}
};
// Lexical analyzer class
class LexicalAnalyzer
{
public:
	vector<Token> tokens;
	SymbolTable table;
	LexicalAnalyzer()
	{
		tokens.clear();
	}
	void add_1(TokenType type, string value, int line, int column)
	{
		tokens.push_back(Token(type, value, line, column));
	}
	void add(TokenType type, int line, int column)
	{
		tokens.push_back(Token(type, "", line, column));
	}
	void add(TokenType type, string value, int line, int column, SymbolTable *table)
	{
		tokens.push_back(Token(type, value, line, column));
		table->add(value, type, line, column);
	}
	void add(TokenType type, int line, int column, SymbolTable *table)
	{
		tokens.push_back(Token(type, "", line, column));
		table->add("", type, line, column);
	}
	void print()
	{
		for (vector<Token>::iterator it = tokens.begin(); it != tokens.end(); ++it)
		{
			cout << it->type << " " << it->value << " " << it->line << " " << it->column << endl;
		}
	}
	void print(SymbolTable *table)
	{
		table->print();
	}
};
// Lexical analyzer for C++ program
void lexicalAnalyzer(string fileName)
{
	LexicalAnalyzer lexicalAnalyzer;
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "Cannot open file " << fileName << endl;
		return;
	}
	string line;
	int lineNumber = 1;
	int columnNumber = 1;
	while (getline(file, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			char c = line[i];
			if (c == ' ' || c == '\t')
			{
				columnNumber++;
			}
			else if (c == '\n')
			{
				lineNumber++;
				columnNumber = 1;
			}
			else if (c == '"')
			{
				string value = "";
				for (int j = i + 1; j < line.length(); j++)
				{
					char c = line[j];
					if (c == '"')
					{
						i = j;
						lexicalAnalyzer.add(STRING, value, lineNumber, columnNumber);
						break;
					}
					else
					{
						value += c;
					}
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>' || c == '&' || c == '|' || c == '!')
			{
				lexicalAnalyzer.add_1(OPERATOR, c, lineNumber, columnNumber);
			}
			else if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == ',' || c == '.')
			{
				lexicalAnalyzer.add_1(PUNCTUATOR, c, lineNumber, columnNumber);
			}
			else if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			{
				string value = "";
				for (int j = i; j < line.length(); j++)
				{
					char c = line[j];
					if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
					{
						value += c;
					}
					else
					{
						i = j - 1;
						lexicalAnalyzer.add(IDENT, value, lineNumber, columnNumber);
						break;
					}
				}
			}
			else if (c >= '0' && c <= '9')
			{
				string value = "";
				for (int j = i; j < line.length(); j++)
				{
					char c = line[j];
					if (c >= '0' && c <= '9')
					{
						value += c;
					}
					else
					{
						i = j - 1;
						lexicalAnalyzer.add(NUMBER, value, lineNumber, columnNumber);
						break;
					}
				}
			}
			else
			{
				cout << "Invalid character " << c << " at line " << lineNumber << " column " << columnNumber << endl;
			}
		}
	}
	lexicalAnalyzer.print();
	lexicalAnalyzer.print(&lexicalAnalyzer.table);
}
// Lexical analyzer for C program
void lexicalAnalyzerC(string fileName)
{
	LexicalAnalyzer lexicalAnalyzer;
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "Cannot open file " << fileName << endl;
		return;
	}
	string line;
	int lineNumber = 1;
	int columnNumber = 1;
	while (getline(file, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			char c = line[i];
			if (c == ' ' || c == '\t')
			{
				columnNumber++;
			}
			else if (c == '\n')
			{
				lineNumber++;
				columnNumber = 1;
			}
			else if (c == '"')
			{
				string value = "";
				for (int j = i + 1; j < line.length(); j++)
				{
					char c = line[j];
					if (c == '"')
					{
						i = j;
						lexicalAnalyzer.add(STRING, value, lineNumber, columnNumber);
						break;
					}
					else
					{
						value += c;
					}
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>' || c == '&' || c == '|' || c == '!')
			{
				lexicalAnalyzer.add(OPERATOR,c, lineNumber, columnNumber);
			}
			else if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == ',' || c == '.')
			{
				lexicalAnalyzer.add(PUNCTUATOR, c, lineNumber, columnNumber);
			}
			else if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			{
				string value = "";
				for (int j = i; j < line.length(); j++)
				{
					char c = line[j];
					if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
					{
						value += c;
					}
					else
					{
						i = j - 1;
						lexicalAnalyzer.add(IDENT, value, lineNumber, columnNumber);
						break;
					}
				}
			}
			else if (c >= '0' && c <= '9')
			{
				string value = "";
				for (int j = i; j < line.length(); j++)
				{
					char c = line[j];
					if (c >= '0' && c <= '9')
					{
						value += c;
					}
					else
					{
						i = j - 1;
						lexicalAnalyzer.add(NUMBER, value, lineNumber, columnNumber);
						break;
					}
				}
			}
			else
			{
				cout << "Invalid character " << c << " at line " << lineNumber << " column " << columnNumber << endl;
			}
		}
	}
	lexicalAnalyzer.print();
	lexicalAnalyzer.print(&lexicalAnalyzer.table);
}
int main()
{
	lexicalAnalyzerC("input.txt");
	return 0;
}