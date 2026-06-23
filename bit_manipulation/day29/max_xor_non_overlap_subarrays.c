#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define INT_BITS 30

// Trie Node definition
typedef struct TrieNode {
    struct TrieNode* children[2];
} TrieNode;

// Helper to create a new Trie Node
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->children[0] = NULL;
    node->children[1] = NULL;
    return node;
}

// Insert a number into the Trie bit by bit
void insert(TrieNode* root, int num) {
    TrieNode* curr = root;
    for (int i = INT_BITS; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (curr->children[bit] == NULL) {
            curr->children[bit] = createNode();
        }
        curr = curr->children[bit];
    }
}

// Query the Trie to find the maximum XOR possible for a given number
int getMaxXor(TrieNode* root, int num) {
    TrieNode* curr = root;
    int maxXor = 0;
    for (int i = INT_BITS; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int toggledBit = 1 - bit;
        
        // Greedily pick the opposite bit if it exists
        if (curr->children[toggledBit] != NULL) {
            maxXor |= (1 << i);
            curr = curr->children[toggledBit];
        } else if (curr->children[bit] != NULL) {
            curr = curr->children[bit];
        } else {
            break; // Should not happen if 0 is inserted initially
        }
    }
    return maxXor;
}

// Free memory allocated for the Trie
void freeTrie(TrieNode* root) {
    if (root == NULL) return;
    freeTrie(root->children[0]);
    freeTrie(root->children[1]);
    free(root);
}

int maxXorTwoSubarrays(int* nums, int numsSize) {
    if (numsSize < 2) return 0;

    int* maxLeft = (int*)malloc(numsSize * sizeof(int));
    int* maxRight = (int*)malloc(numsSize * sizeof(int));

    // 1. Forward Pass: Compute max left subarray XORs
    TrieNode* trieLeft = createNode();
    insert(trieLeft, 0); // Base case for prefix XOR
    
    int currentXor = 0;
    int runningMax = 0;
    for (int i = 0; i < numsSize; i++) {
        currentXor ^= nums[i];
        runningMax = MAX(runningMax, getMaxXor(trieLeft, currentXor));
        maxLeft[i] = runningMax;
        insert(trieLeft, currentXor);
    }
    freeTrie(trieLeft);

    // 2. Backward Pass: Compute max right subarray XORs
    TrieNode* trieRight = createNode();
    insert(trieRight, 0); // Base case for suffix XOR
    
    currentXor = 0;
    runningMax = 0;
    for (int i = numsSize - 1; i >= 0; i--) {
        currentXor ^= nums[i];
        runningMax = MAX(runningMax, getMaxXor(trieRight, currentXor));
        maxRight[i] = runningMax;
        insert(trieRight, currentXor);
    }
    freeTrie(trieRight);

    // 3. Maximize maxLeft[i] ^ maxRight[i+1] across all splits
    int globalMaxXor = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        int combinedXor = maxLeft[i] ^ maxRight[i + 1];
        globalMaxXor = MAX(globalMaxXor, combinedXor);
    }

    // Clean up dynamic arrays
    free(maxLeft);
    free(maxRight);

    return globalMaxXor;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int size = sizeof(nums) / sizeof(nums[0]);
    
    int result = maxXorTwoSubarrays(nums, size);
    printf("Maximum XOR of two non-overlapping subarrays: %d\n", result);
    
    return 0;
}