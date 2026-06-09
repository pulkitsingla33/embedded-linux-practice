#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage %s <number>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    int num_copy = num;
    int count_digits = 0;
    
    while(num_copy != 0)
    {
        count_digits++;
        num_copy >>= 1;
    }

    int msb_side = count_digits - 1;
    int lsb_side = 0;
    int is_palindrome = 1;

    while(msb_side > lsb_side)
    {
        int num_msb = num & (1 << msb_side);
        int num_lsb = num & (1 << lsb_side);
        if((num_msb && num_lsb) || (num_msb == num_lsb))
        {
            msb_side--;
            lsb_side++;
        }
        else
        {
            is_palindrome = 0;
            break;
        }
    }

    if(!is_palindrome)
        printf("Not palindrome\n");
    else
        printf("Palindrome\n");

    return 0;
}