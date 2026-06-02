#include <stdio.h>

int main()
{
    int num = 42;

    int num_masked = (num & (-num)) - 1;

    int count = 0;
    while(num_masked != 0)
    {
        count++;
        num_masked >>= 1;
    }

    printf("%d\n", count);
}