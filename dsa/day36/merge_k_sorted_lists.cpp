#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val; // Min-heap: smallest element stays on top
    }
};

// ONE FUNCTION TO MERGE THE LISTS
ListNode* mergeKLists(vector<ListNode*>& lists) {
    // Priority queue to store the heads of the lists, sorted by their values
    priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;

    // Push the head of each non-empty list into the min-heap
    for (ListNode* list : lists) {
        if (list != nullptr) {
            minHeap.push(list);
        }
    }

    // Dummy node to help easily build the new merged list
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;

    // Process the elements in the heap
    while (!minHeap.empty()) {
        // Get the node with the smallest value
        ListNode* smallest = minHeap.top();
        minHeap.pop();

        // Append it to our merged list
        tail->next = smallest;
        tail = tail->next;

        // If the chosen node has a next node, push it into the heap
        if (smallest->next != nullptr) {
            minHeap.push(smallest->next);
        }
    }

    ListNode* mergedHead = dummy->next;
    delete dummy; // Clean up memory for the dummy node
    return mergedHead;
}

// MAIN FUNCTION
int main() {
    // Creating 3 sorted linked lists for testing:
    // List 1: 1 -> 4 -> 5
    ListNode* l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    // List 2: 1 -> 3 -> 4
    ListNode* l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    // List 3: 2 -> 6
    ListNode* l3 = new ListNode(2, new ListNode(6));

    vector<ListNode*> lists = {l1, l2, l3};

    // Call the single merge function
    ListNode* result = mergeKLists(lists);

    // Print the merged list
    cout << "Merged List: ";
    while (result != nullptr) {
        cout << result->val;
        if (result->next != nullptr) cout << " -> ";
        result = result->next;
    }
    cout << endl;

    // (Optional) Memory cleanup could be added here, but for a quick 
    // demonstration script, letting the OS handle exit cleanup is fine.

    return 0;
}