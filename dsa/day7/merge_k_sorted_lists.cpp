#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
        int data;
        Node *next;
        Node(int x)
        {
            data = x;
            next = nullptr;
        }
};

class Compare
{
    public:
    bool operator()(Node *a, Node *b)
    {
        return a->data > b->data;
    }
};

Node* mergeKLists(vector<Node*>& arr)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (Node *head:arr)
    {
        if(head != nullptr)
            pq.push(head);
    }

    Node* dummy = new Node(-1);
    Node* tail = dummy;

    while(!pq.empty())
    {
        Node* top = pq.top();
        pq.pop();

        tail->next = top;
        tail = top;

        if(top->next != nullptr)
        {
            pq.push(top->next);
        }

    }
    return dummy->next;
}

void printList(Node *node)
{
    while (node != nullptr)
    {
        cout << node->data;
        if(node->next)
            cout << "->";
        node = node->next;
    }
    cout << endl;
}

int main() {
    int k = 3; 
  
    vector<Node*> arr(k);

    arr[0] = new Node(1);
    arr[0]->next = new Node(3);
    arr[0]->next->next = new Node(5);
    arr[0]->next->next->next = new Node(7);

    arr[1] = new Node(2);
    arr[1]->next = new Node(4);
    arr[1]->next->next = new Node(6);
    arr[1]->next->next->next = new Node(8);

    arr[2] = new Node(0);
    arr[2]->next = new Node(9);
    arr[2]->next->next = new Node(10);
    arr[2]->next->next->next = new Node(11);
    
    Node* head = mergeKLists(arr);

    printList(head);

    return 0;
}