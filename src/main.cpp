#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

class ExpressionCalculator
{
private:
    stack<string> postfix;
    string errorMessage;

    void infixToPostfix(string &s)
    {
        stack<char> operators;
        stack<string> revPostfix;
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
                errorMessage = "Invalid operator { ";
                errorMessage.push_back(s[i]), errorMessage.append(" }!\n");
                throw runtime_error(errorMessage);
            }
        }
        while (!operators.empty())
            op = operators.top(), revPostfix.push(op), operators.pop();
        while (!revPostfix.empty())
            postfix.push(revPostfix.top()), revPostfix.pop();
    }

    long double evaluate(long double lhs, char op, long double rhs) const
    {
        switch (op)
        {
        case '^':
            return (long double)pow(lhs, rhs);
        case '*':
            return lhs * rhs;
        case '/':
            return lhs / rhs;
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        default:
            throw runtime_error("Invalid operator!\n");
        }
    }

    long double calculateExpr(stack<string> &postfix)
    {
        stack<long double> t;
        while (!postfix.empty())
        {
            auto token = postfix.top();
            postfix.pop();

            if (isOperator(token.back()))
            {
                if (t.size() < 2)
                {
                    string errorMessage = "No enough operands for operator { ";
                    errorMessage.push_back(token.back()), errorMessage.append(" }!\n");
                    throw runtime_error(errorMessage);
                }

                long double rhs = t.top();
                t.pop();
                long double lhs = t.top();
                t.pop();
                t.push(evaluate(lhs, token[0], rhs));
            }
            else
                t.push(stod(token));
        }
        if (t.empty())
            throw runtime_error("Invalid expression!\n");
        return t.top();
    }

    int val(char op) const
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
            throw runtime_error("Invalid operator!\n");
        }
    }

    bool isOperator(char token) const
    {
        const char operators[]{'^', '*', '/', '+', '-'};
        for (auto &op : operators)
            if (token == op)
                return true;
        return false;
    }

    inline bool isNumber(const char &n) const
    {
        return n >= '0' and n <= '9';
    }

public:
    ExpressionCalculator() = default;

    ExpressionCalculator(string &infix)
    {
        calculate(infix);
    }

    void calculate(string &infix)
    {
        infixToPostfix(infix);
    }

    long double getAnswer()
    {
        return calculateExpr(postfix);
    }

    void formatPrint(const string &infix) const
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
};

int main()
{
    string infix;
    cout << "Valid operators: [^, *, /, +, -]\nEnter an expression to calculate: ";
    getline(cin, infix);
    cout << '\n';

    ExpressionCalculator calculator;

    calculator.calculate(infix);

    calculator.formatPrint(infix);

    cout << calculator.getAnswer() << '\n';
}
