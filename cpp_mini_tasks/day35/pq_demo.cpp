#include <bits/stdc++.h>
using namespace std;

int main()
{
    priority_queue<int> maxHeap;
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(5);

    cout << "Elements are extracted from highest to lowest:\n";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " "; // Look at the top element
        maxHeap.pop();                     // Remove the top element
    }
    cout << "\n\n";

    // 2. Custom Priority Queue: Min-Heap (Lowest number has highest priority)
    // Formula: priority_queue<Type, Container, Comparator>
    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(20);
    minHeap.push(5);

    cout << "--- Min-Heap ---\n";
    cout << "Elements are extracted from lowest to highest:\n";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << "\n";

    return 0;
}