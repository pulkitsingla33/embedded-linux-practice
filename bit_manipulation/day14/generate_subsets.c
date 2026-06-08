#include <stdio.h>

// Function to generate all subsets using bitmasks
void generateSubsets(int arr[], int n) {
    int total_subsets = 1 << n; 

    // Iterate from mask = 0 to (2^n) - 1
    for (int mask = 0; mask < total_subsets; mask++) {
        printf("[");
        int first = 1; // Flag to handle clean comma formatting

        for (int i = 0; i < n; i++) {
            // Check if the i-th bit of 'mask' is set to 1
            if ((mask & (1 << i)) != 0) {
                if (!first) {
                    printf(",");
                }
                printf("%d", arr[i]);
                first = 0; // Subsequent elements in this subset will need a comma
            }
        }
        printf("]\n");
    }
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Generated Subsets:\n");
    generateSubsets(arr, n);

    return 0;
}