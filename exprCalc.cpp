#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

int val(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        cerr << "Invalid operator!\n";
        exit(-99);
    }
}

string infixToPostfix(string &s)
{
    stack<char> ops;
    stringstream ans;
    for (int i = 0; i < (int)s.length(); ++i)
    {
        if (s[i] == ' ')
            continue;

        if (s[i] >= '0' and s[i] <= '9')
            ans << s[i];
        else if (s[i] == '*' or s[i] == '/' or s[i] == '+' or s[i] == '-' or
                 s[i] == '^')
        {
            int temp = val(s[i]);
            while (!ops.empty() and temp <= val(ops.top()))
                ans << ops.top(), ops.pop();
            ops.push(s[i]);
        }
        else
        {
            cerr << "Invalid expression!\n";
            exit(-99);
        }
    }
    while (!ops.empty())
        ans << ops.top(), ops.pop();

    return ans.str();
}

double evaluate(double lhs, char op, double rhs)
{
    switch (op)
    {
    case '^':
        return pow(lhs, rhs);
    case '*':
        return lhs * rhs;
    case '/':
        return lhs / rhs;
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    default:
        cerr << "wrong operator!\n";
        exit(-99);
    }
}

double calculateExpr(stack<char> &s)
{
    stack<double> t;
    while (!s.empty())
    {
        auto token = s.top();
        s.pop();
        if (token == '*' or token == '/' or token == '+' or token == '-' or
            token == '^')
        {
            double rhs = t.top();
            t.pop();
            double lhs = t.top();
            t.pop();
            t.push(evaluate(lhs, token, rhs));
        }
        else
            t.push(token - '0');
    }
    if (!s.empty() or t.empty())
        cerr << "Wrong expression!\n";
    return t.top();
}

int main()
{
    string in, post;
    cout << "Valid operators: [^, *, /, +, -] only single digit numbers\n";
    cout << "Enter an expression to calculate: ";
    getline(cin, in);

    post = infixToPostfix(in);
    cout << /* "Postfix: " << post <<*/ "\n\n";

    stack<char> s;
    for (int i = (int)post.length() - 1; i >= 0; --i)
        s.push(post[i]);

    cout << in << " = " << calculateExpr(s);
}