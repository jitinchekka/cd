//b mahidhar reddy
// cs20b1091
//lab 8

#include <bits/stdc++.h>
using namespace std;
map<string, vector<vector<string>>> mp;
unordered_map<string, pair<string, string>> st;

int main()
{

    unordered_map<string, pair<string, string>> arthemtic, logical, relational, unary_operator, ternary_operator;
    arthemtic = {{"+", {"addition", "arthemtic"}}, {"-", {"subraction", "arthemtic"}}, {"/", {"division", "arthemtic"}}, {"*", {"multiplication", "arthemtic"}}, {"%", {"modulo", "arthemtic"}}};
    logical = {{"&", {"bitwise AND", "logical"}}, {"^", {"bitwise XOR", "logical"}}, {"|", {"bitwise OR", "logical"}}, {"~", {"inverse operator", "logical"}}};
    relational = {{"<", {"less than", "relational"}}, {">", {"greater than", "relational"}}, {"!", {"not", "relational"}}, {"=", {"equal operator", "relational"}}};
    ternary_operator = {{"?", {"question", "ternary"}}, {":", {": operator", "ternary"}}};
    unary_operator = {{"+=", {"add assign", "unary"}}, {"++", {"increment", "unary"}}, {"!=", {"not equal", "unary"}}, {"--", {"decrement", "unary"}}, {"/=", {"divide assign", "unary"}}, {"-=", {"subract assign", "unary"}}, {"*=", {"multiplication assign", "unary"}}, {"%=", {"modulo assign operator", "unary"}}, {">=", {"greater than equal", "unary"}}, {"<=", {"lesser than equal", "unary"}}};
    st.merge(arthemtic);
    st.merge(logical);
    st.merge(ternary_operator);
    st.merge(relational);
    st.merge(unary_operator);

    cout << "enter the strings of operator : ";
    string temp;
    while (cin >> temp)
    {
        if (st.find(temp) != st.end())
        {
            cout << temp << " :" << st[temp].first << "--->" << st[temp].second << "\n";
        }
        else
        {
            cout << temp << " : not a operator\n";
        }
    }
    return (0);
}