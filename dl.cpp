#include <iostream>
using namespace std;

class node
{
private:
    int data;
    node *prev;
    node *next;

public:
    node(int data)
    {
        this->data = data;
        prev = nullptr;
        next = nullptr;
    }

    int Data() const { return data; }

    node *&Prev() { return prev; }
    node *&Next() { return next; }

    node *Prev() const { return prev; }
    node *Next() const { return next; }
};

class dll
{
private:
    node *head;

public:
    dll() { head = nullptr; }
    void create(int A[], int n);
    int length();
    void display();
    void insert(int index, int data);
    int deletekey(int key);
    void reverse();
    void displayreverse();
    void makecircular();
    int findmid();
    int findmid1();
    int findmid2();
};

void dll::create(int A[], int n)
{
    if (n <= 0)
        return;

    head = new node(A[0]);
    node *last = head;

    for (int i = 1; i < n; i++)
    {
        node *temp = new node(A[i]);
        temp->Prev() = last;
        last->Next() = temp;
        last = temp;
    }
}

void dll::display()
{
    node *p = head;
    while (p)
    {
        cout << p->Data() << " ";
        p = p->Next();
    }
    cout << endl;
}

int dll::length()
{
    if (head == nullptr)
        return 0;
    node *p = head;
    int l = 0;
    while (p)
    {
        l++;
        p = p->Next();
    }
    return l;
}

void dll::insert(int index, int data)
{
    if (index < 0 || index > length())
    {
        return;
    }

    if (head == nullptr)
    {
        head = new node(data);
        return;
    }

    node *temp = new node(data);
    node *p = head;
    node *q = nullptr;

    if (index == 0)
    {
        temp->Next() = head;
        head->Prev() = temp;
        head = temp;
        return;
    }

    for (int i = 1; (i < index + 1); i++)
    {
        q = p;
        p = p->Next();
    }

    q->Next() = temp;
    temp->Prev() = q;
    temp->Next() = p;
    if (p)
        p->Prev() = temp;
}

int dll::deletekey(int key)
{
    if (head == nullptr)
    {
        return -1;
    }

    int data = 0;
    node *p = head;
    node *q = nullptr;

    if (head->Data() == key)
    {
        data = head->Data();
        if (p->Next())
        {
            head = p->Next();
        }
        if (head)
        {
            head->Prev() = nullptr;
        }
        delete p;
        return data;
    }

    while (p)
    {
        if (p->Data() == key)
        {
            data = p->Data();
            p->Prev()->Next() = p->Next();
            if (p->Next())
            {
                p->Next()->Prev() = p->Prev();
            }
            delete p;
            p = nullptr;
            return data;
        }
        else
        {
            q = p;
            p = p->Next();
        }
    }

    return -1; // key not found
}

void dll::reverse()
{
    node *p = head;
    node *temp = nullptr;

    while (p != nullptr)
    {
        temp = p->Next();      // null for the head node
        p->Prev() = p->Next(); // 1st pointer swap
        p->Next() = temp;      // final node p->next() made null

        p = p->Prev(); // p shifted forward
    }

    if (temp != nullptr)
        head = temp->Prev(); // p will become null but temp stays 1 node back and temp's prev would be the final node and the new head
}

void dll::displayreverse()
{
    if (head == nullptr)
    {
        return;
    }

    node *p = head;
    node *q = nullptr;

    while (p->Next())
    {
        p = p->Next();
    }
    while (p)
    {
        cout << p->Data() << " ";
        p = p->Prev();
    }
    cout << endl;
}

void dll::makecircular()
{
    if (head == nullptr)
    {
        return;
    }

    if (head->Next() == nullptr)
    {
        head->Next() = head;
        return;
    }

    if (head->Prev() && head->Prev()->Next() == head)
    {
        return;
    }

    node *p = head;
    while (p->Next())
        p = p->Next();

    head->Prev() = p;
    p->Next() = head;
}

int dll::findmid()
{
    if (head == nullptr)
        return -1;

    node *p = head;
    int mid = length() / 2;
    while (mid--)
        p = p->Next();

    return p->Data();
}

int dll::findmid1()
{
    if (head == nullptr)
    {
        return -1;
    }

    node *p = head;
    node *q = head;

    while (p && p->Next())
    {
        p = p->Next()->Next();
        q = q->Next();
    }
    return q->Data();
}

int dll::findmid2()
{
    if (head == nullptr)
        return -1;

    node *slow = head;
    node *fast = head;

    while (fast && fast->Next())
    {
        fast = fast->Next()->Next();
        slow = slow->Next();
    }

    return slow->Data();
}

int main()
{
    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    dll a;
    a.create(A, 10);
    cout << a.findmid() << endl;
    cout << a.findmid1() << endl;
    cout << a.findmid2() << endl;
    return 0;
}