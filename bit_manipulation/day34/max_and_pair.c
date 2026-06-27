#include <stdio.h>

int main()
{
    int arr[] = {16,9,6,13};
    int n = sizeof(arr)/sizeof(arr[0]);

    int result = 0;

    for(int i = 31; i >= 0; i--)
    {
        int pattern = result | (1 << i);
        int count = 0;

        for(int j = 0; j < n; j++)
        {
            if((arr[j] & pattern) == pattern)
            {
                count++;
            }
        }

        if(count >= 2)
        {
            result = pattern;
        }
    }

    printf("Result is %d\n", result);

    return 0;
}