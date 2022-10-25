// b mahidhar reddy
//  cs20b1091
// lab 10

#include <bits/stdc++.h>
using namespace std;


vector<string> ans1, ans2, ans3;
vector<bool> reg(100, false);

string opp(string op)
{
    if (op == "+")
        return "ADD";
    else if (op == "-")
        return "SUB";
    else if (op == "/")
        return "DIV";
    else if (op == "*")
        return "MUL";
    return "MOD";
}

int main()
{
    cout << "enter no of equations : ";
    int n;
    cin >> n;

    while (n--)
    {
        string a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        string x;
        for (int i = 0; i < reg.size(); i++)
        {
            if (!reg[i])
            {
                ans1.push_back("Mov");
                ans2.push_back("R" + to_string(i));
                ans3.push_back(c);

                ans1.push_back(opp(d));
                ans3.push_back("R" + to_string(i));
                ans2.push_back(e);

                ans1.push_back("Mov");
                ans2.push_back(a);
                ans3.push_back("R" + to_string(i));

                reg[i] = true;
                i = reg.size() + 2;
            }
        }
    }

    cout << "\nthe equivalent assembly code is : \n\n";
    for (int i = 0; i < ans1.size(); i++)
    {
        cout << ans1[i] << "  " << ans2[i] << "  " << ans3[i] << "\n";
    }
}