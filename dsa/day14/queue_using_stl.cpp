#include <bits/stdc++.h>
using namespace std;

void my_enqueue(queue<int>& my_queue, int x)
{
    my_queue.push(x);
}

void my_dequeue(queue<int>& my_queue)
{
    my_queue.pop();
}

int my_front(queue<int>& my_queue)
{
    return my_queue.front();
}

bool my_empty(queue<int>& my_queue)
{
    return my_queue.empty();
}


int main()
{
    queue<int> my_queue;

    my_enqueue(my_queue, 1);
    my_enqueue(my_queue, 6);

    cout << my_front(my_queue) << endl;

    return 0;
}