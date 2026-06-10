#include <stdio.h>

int main()
{
    int num = 0;
    int gap = 0;
    int max_gap = 0;
    int start_gap_count = 0;

    while(num!= 0)
    {
        if((!start_gap_count) && (num & 1))
        {
            start_gap_count++;
            gap++;
            num >>=1;
            continue;
        }

        if(start_gap_count)
        {
            if(num & 1)
            {   
                max_gap = gap > max_gap ? gap : max_gap;
                gap = 0;
            }
            gap++;
        }
        num >>= 1;
    }

    printf("Max Gap is: %d\n", max_gap);

    return 0;
}