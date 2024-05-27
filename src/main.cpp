#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

bool isOperator(char token)
{
    const char operators[]{'^', '*', '/', '+', '-'};
    for (auto &op : operators)
        if (token == op)
            return true;
    return false;
}

inline bool isNumber(const char &n)
{
    return n >= '0' and n <= '9';
}

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

stack<string> infixToPostfix(string &s)
{
    stack<char> operators;
    stack<string> revPostfix, answer;
    string token, op;
    int i = 0;

    while (i < (int)s.length())
    {
        token.clear();
        while (s[i] == ' ')
            i++;

        if (isNumber(s[i]))
        {
            while (isNumber(s[i]) or s[i] == '.')
                token += s[i++];
            revPostfix.push(token);
        }
        else if (isOperator(s[i]))
        {
            token = s[i++];
            int precedence = val(token[0]);

            while (!operators.empty() and precedence <= val(operators.top()))
                op = operators.top(), revPostfix.push(op), operators.pop();

            operators.push(token[0]);
        }
        else
        {
            cerr << "Invalid expression!\n";
            exit(-99);
        }
    }
    while (!operators.empty())
        op = operators.top(), revPostfix.push(op), operators.pop();
    while (!revPostfix.empty())
        answer.push(revPostfix.top()), revPostfix.pop();
    return answer;
}

double evaluate(double lhs, char op, double rhs)
{
    switch (op)
    {
    case '^':
        return (double)pow(lhs, rhs);
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

double calculateExpr(stack<string> &postfix)
{
    stack<double> t;
    while (!postfix.empty())
    {
        auto token = postfix.top();
        postfix.pop();

        if (isOperator(token.back()))
        {
            if (t.size() < 2)
            {
                cerr << "Invalid expression!\n";
                exit(-99);
            }

            double rhs = t.top();
            t.pop();
            double lhs = t.top();
            t.pop();
            t.push(evaluate(lhs, token[0], rhs));
        }
        else
            t.push(stod(token));
    }
    if (t.empty())
        cerr << "Wrong expression!\n";
    return t.top();
}

void formatPrint(const string &infix)
{
    for (int i = 0; i < (int)infix.length(); ++i)
    {
        if (infix[i] == ' ')
            continue;
        else if (isOperator(infix[i]))
            cout << infix[i] << ' ';
        else
        {
            cout << infix[i];
            if (i + 1 < (int)infix.length() and !isNumber(infix[i + 1]) and infix[i + 1] != '.')
                cout << ' ';
        }
    }
    cout << " = ";
}

int main()
{
    string infix;
    cout << "Valid operators: [^, *, /, +, -]\nEnter an expression to calculate: ";
    getline(cin, infix);
    cout << '\n';

    auto postfix = infixToPostfix(infix);

    formatPrint(infix);

    cout << calculateExpr(postfix);
}
