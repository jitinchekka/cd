// b mahidhar reddy
//  cs20b1091
// lab 9
//Write a C program for constructing of LL (1) parsing.
// http://www.cs.ecu.edu/karl/5220/spr16/Notes/Top-down/LL1.html

#include <bits/stdc++.h>
using namespace std;

map<pair<string, string>, string> table, table1;
map<string, vector<string>> productions;
map<string, vector<string>> ter, nter; // Terminals and non-terminals
map<pair<string, string>, string> mp;

stack<string> print(stack<string> s)
{
    vector<string> p;
    while (!s.empty())
    {
        p.push_back(s.top());
        s.pop();
    }

    for (int i = p.size() - 1; i >= 0; i--)
    {
        cout << p[i];
        s.push(p[i]);
    }
    cout << "       ";
    return s;
}
int main()
{
    int n;
    cout << "enter no of productions : ";
    cin >> n;
    while (n--)
    {
        string x, y;
        cin >> x >> y;

        if (productions.find(x) != productions.end())
        {
            vector<string> p = productions[x];
            p.push_back(y);
            productions[x] = p;
        }
        else
        {
            vector<string> p = {y};
            productions[x] = p;
        }

        if (y[0] >= 'A' && y[0] <= 'Z') //Non-terminal
        {
            string k = "";
            k += y[0];
            if (nter.find(k) != nter.end())
            {
                vector<string> p = nter[k];
                p.push_back(x);
                nter[k] = p;
            }
            else
            {
                vector<string> p = {x};
                nter[k] = p;
            }
        }
        else //Terminal
        {
            string k = "";
            k += y[0];
            if (ter.find(k) != ter.end())
            {
                ter[k].push_back(x);
                mp[{k, x}] = y;
            }
            else
            {
                vector<string> p;
                p.push_back(x);
                ter[k] = p;
                mp[{k, x}] = y;
            }
        }
    }
    stack<string> prod, input;
    string check;
    cout << "enter the string need to check : ";
    cin >> check;

    for (int i = check.size() - 1; i >= 0; i--) //	Input stack (reverse string and push into stack)
    {
        string p = "";
        p += check[i];
        input.push(p);
    }

    prod.push("Q");
	cout << "The productions map is:\n";
	for (auto c : productions)
	{
        cout << c.first << " == ";
        for (auto b : c.second)
        {
            cout << b << " ";
        }
        cout << "\n";
    }

    for (auto c : ter)
    {
        // cout << c.first << "\n";
        for (int i = 0; i < c.second.size(); i++)
        {
            auto x1 = c.second[i];
            if (x1 >= "A" && x1 <= "Z")
            {
                if (nter.find(x1) != nter.end())
                {
                    vector<string> p = ter[c.first];
                    for (auto k : nter[x1])
                    {
                        p.push_back(k);
                        string zz = "";
                        zz += c.first;
                        for (int j = 0; j < productions[c.second[i]].size(); j++)
                        {
                            if (productions[c.second[i]][j][0] == zz[0])
                            {
                                mp[{c.first, k}] = productions[c.second[i]][j];
                            }
                        }
                    }
                    ter[c.first] = p;
                }
            }
        }
    }

    cout << "terminals : \n";

    for (auto c : ter)
    {
        cout << c.first << "-----> ";
        for (auto x : c.second)
        {
            cout << x << " ";
        }
        cout << "\n";
    }

    cout << "non terminals : \n";

    for (auto c : nter)
    {
        cout << c.first << "-----> ";
        for (auto x : c.second)
        {
            cout << x << " ";
        }
        cout << "\n";
    }
	cout << "parse table mp:\n";
	for (auto c : mp)
	{
        cout << c.first.first << " " << c.first.second << "--->" << c.second << "\n";
    }

    while (!prod.empty() && !input.empty())
    {

        prod = print(prod);
        input = print(input);
        cout << "\n";
        string x = input.top();
        string y = prod.top();
        if (x == y)
        {
            input.pop();
            prod.pop();
            continue;
        }
        else if (mp.find({x, y}) != mp.end())
        {
            string k = mp[{x, y}];
            reverse(k.begin(), k.end());
            prod.pop();
            for (int i = 0; i < k.size(); i++)
            {
                string p = "";
                p += k[i];
                prod.push(p);
            }
        }
        else
        {
            cout << "not a ll(1) grammer\n";
            exit(0);
        }
    }
}