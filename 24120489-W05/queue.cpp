#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct NODE
{
    int key;
    NODE *p_next;
};

struct Queue
{
    NODE *head;
    NODE *tail;
};
Queue initializeQueue();
void enqueue(Queue &q, int key);
int dequeue(Queue &q);
int size(Queue q);
bool isEmpty(Queue q);
void Display(Queue q, ofstream &out);
Queue initializeQueue()
{
    Queue newQueue;
    newQueue.head = newQueue.tail = nullptr;
    return newQueue;
}

void enqueue(Queue &q, int key)
{
    NODE *tmp = new NODE();
    tmp->key = key;
    tmp->p_next = nullptr;
    if (q.head == nullptr)
    {
        q.head = q.tail = tmp;
        return;
    }

    q.tail->p_next = tmp;
    q.tail = tmp;
}

int dequeue(Queue &q)
{
    if (q.head == nullptr)
        return 0;
    int value = q.tail->key;
    NODE *tmp = q.head;
    q.head = q.head->p_next;
    delete tmp;
    return value;
}

int size(Queue q)
{
    int size = 0;
    NODE *tmp = q.head;
    while (tmp)
    {
        size++;
        tmp = tmp->p_next;
    }
    return size;
}

bool isEmpty(Queue q)
{
    return q.head == nullptr;
}

void Display(Queue q, ofstream &out)
{
    if (isEmpty(q))
    {
        out << "EMPTY\n";
        return;
    }
    NODE *tmp = q.head;
    while (tmp)
    {
        out << tmp->key << ' ';
        tmp = tmp->p_next;
    }
    out << '\n';
}

int main()
{
    ifstream in("input.txt");
    if (!in)
    {
        std::cout << "Dont Open File input.txt";
        return 0;
    }
    ofstream out("output.txt");
    if (!out)
    {
        std::cout << "Dont Open File output.txt";
        return 0;
    }

    string s;
    Queue q;
    while (getline(in, s))
    {
        vector<string> v;
        stringstream ss(s);
        string word;
        while (ss >> word)
        {
            v.push_back(word);
        }
        if (v[0] == "init")
        {
            q = initializeQueue();
        }
        else if (v[0] == "enqueue")
        {
            enqueue(q, stoi(v[1]));
        }
        else if (v[0] == "dequeue")
        {
            dequeue(q);
        }
        Display(q, out);
    }
    in.close();
    out.close();
    return 0;
}
