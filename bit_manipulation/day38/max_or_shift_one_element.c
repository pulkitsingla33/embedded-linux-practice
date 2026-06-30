#include <stdio.h>

int main()
{
    int nums[] = {12, 9, 2};
    int k = 1;
    int nums_size = sizeof(nums)/sizeof(nums[0]);

    int prefix_or[nums_size], suffix_or[nums_size];
    int current_prefix = 0, current_suffix = 0;

    int maxOr = 0;
    int currentOr = 0;

    for(int i = 0; i < nums_size; i++)
    {
        prefix_or[i] = current_prefix;
        current_prefix |= nums[i];

        suffix_or[nums_size - i - 1] = current_suffix;
        current_suffix |= nums[nums_size - i - 1];
    }

    for(int i = 0; i < nums_size; i++)
    {
        currentOr = prefix_or[i] | suffix_or[i] | (nums[i] << k);
        if(currentOr > maxOr)
            maxOr = currentOr;
    }

    printf("Max OR is: %d\n", maxOr);

    return 0;
}