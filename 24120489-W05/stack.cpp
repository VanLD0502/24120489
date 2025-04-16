#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct NODE {
    int key ;
    NODE * p_next ;
};

struct Stack {
    NODE * top;
    Stack(){};
};

Stack initializeStack();
void push(Stack &s, int key);
int pop(Stack &s);
int size(Stack s);
bool isEmpty(Stack s);
void Display(Stack s, ofstream& out);
Stack initializeStack()
{
    Stack newState;
    newState.top = nullptr;
    return newState;   
}

void push(Stack &s, int key)
{
    NODE* tmp = new NODE();
    tmp->key = key;
    tmp->p_next = nullptr;
    if (s.top == nullptr) {
        s.top = tmp;
        return;
    }

    tmp->p_next = s.top;
    s.top = tmp;
}

int pop(Stack &s)
{
    if (s.top == nullptr) {
        std::cout << "Empty Stack. Don't Pop" << '\n';
        return 0;
    }

    NODE* tmp = s.top;
    int value = tmp->key;
    s.top = s.top->p_next;
    delete tmp;
    return value;
}

int size(Stack s)
{
    NODE* tmp = s.top;
    int size = 0;
    while (tmp) {
        size ++;
        tmp = tmp->p_next;
    }
    return size;
}

bool isEmpty(Stack s)
{
    return s.top == nullptr;
}

void Display(Stack s, ofstream& out) {
    NODE* tmp = s.top;
    while(tmp) {
        out << tmp->key << ' ';
        tmp = tmp->p_next;
    }
    out << '\n';   
}


int main() {
    // string s;
    // Stack* st = nullptr;
    // while (getline(cin,s)) {
    //     if (s == "OK") break;
    //     stringstream ss(s);
    //     string word;
    //     while (ss >> word) {
    //         v.push_back(word);
    //     }
    //     if (v[0] == "init") {
    //         st = initializeStack();
    //     }
    //     else if (v[0] == "push") {
    //         push(*st , stoi(v[1]));
    //     }
    //     else if (v[0] == "pop") {
    //         pop(*st);
    //     }
    // }

    ifstream in("input.txt");
    if (!in) {
        std::cout << "Dont Open File input.txt";
        return 0;
    }
    ofstream out("output.txt");
    if (!out) {
        std::cout << "Dont Open File output.txt";
        return 0;
    }
    string s;
    Stack st;
    while (getline(in,s)) {
        vector<string> v;
        stringstream ss(s);
        string word;
        while (ss >> word) {
            v.push_back(word);
        }
        if (v[0] == "init") {
            st = initializeStack();
        }
        else if (v[0] == "push") {
            push(st , stoi(v[1]));
        }
        else if (v[0] == "pop") {
            pop(st);
        }
        
        if (isEmpty(st)) {
            out << "EMPTY\n";
        }
        else {
            Display(st, out);
        }
    }
    in.close();
    out.close();
    return 0;
}