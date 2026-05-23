#include <stdio.h>

int main()
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int size = sizeof(arr)/sizeof(arr[0]);

    int target = 5;

    int low = 0;
    int high = size - 1;

    while(low <= high)
    {
        int mid = low + (high - low)/2;

        if(arr[mid] == target)
        {
            printf("Element found at index %d\n", mid);
            return 0;
        }
        else if(arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    printf("Element not found in the array\n");
    
    return 0;
}