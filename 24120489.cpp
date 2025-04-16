#include "ProcessExpression.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;
void Input()
{
    ifstream in("24120489.txt");
    int t;
    in >> t;
    in.ignore();
    string s;
    while (getline(in, s))
    {
        Process(s);
    }
}

int priority(char c)
{
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;

    return 0;
}
bool isSign(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int Compute(int a, int b, char c)
{
    if (c == '+')
        return a + b;
    else if (c == '-')
        return a - b;
    else if (c == '*')
        return a * b;
    else if (c == '/')
        return a / b;
}

void Process(std::string expression)
{
    stack<char> Operator;
    stack<int> Operand;
    int n = expression.size();
    //(124 * 46 + 2) * 2 + 7;
    //(124 * (56 + 4))
    for (int i = 0; i < n; i++)
    {
        char c = expression[i];
        if (c == '(')
        {
            Operator.push(c);
        }
        else if (c == ')')
        {
            Operator.pop();
        }
        else if (isSign(c) && priority(Operator.top()) >= priority(c))
        {
            int o2 = Operand.top();
            Operand.pop();
            int o1 = Operand.top();
            Operand.pop();
            Operand.push(Compute(o1, o2, Operator.top()));

            Operator.push(c);
        }
        else if (isdigit(c))
        {
            int j = i;
            int sum = 0;
            while (j < n && !isdigit(expression[j]))
            {
                sum = sum * 10 + (expression[j] - '0');
                j++;
            }
            i = j - 1;
        }
    }

    while (!Operator.empty())
    {
        int o2 = Operand.top();
        Operand.pop();
        int o1 = Operand.top();
        Operand.pop();
        Operand.push(Compute(o1, o2, Operator.top()));
    }

    cout << Operand.top() << ' ';
}
