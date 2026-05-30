#include <stdio.h>

int count_set_bits(int num)
{
    int count = 0;
    if(num == 0)
        return 0;
    else
    {
        do
        {
            count++;
        }
        while(num = (num & (num-1)));
    }

    return count;
}

int main()
{
    int N = 5;
    int set_bit_count = 0;

    for(int i = 1; i <= N; i++)
    {
        set_bit_count += count_set_bits(i);
    }

    printf("Total set bit count: %d\n", set_bit_count);

}