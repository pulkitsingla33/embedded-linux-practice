#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int hasCycle(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;

    while (slow != NULL && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1; // Cycle detected
        }
    }

    return 0; // No cycle
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = head; // Creating a cycle

    if (hasCycle(head)) {
        printf("Cycle detected in the linked list.\n");
    } else {
        printf("No cycle detected in the linked list.\n");
    }

    return 0;
}