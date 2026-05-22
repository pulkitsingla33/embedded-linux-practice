#include <stdio.h>

int next_power_of_two(int num)
{
    if(num == 0)
        return 1;
    else if(!(num & (num-1)))
        return num;
    else
    {
        while(1)
        {
            num &= (num - 1);   
            if((num & (num - 1)) == 0)
                return (num << 1);
        }
    }

    return 0;
}

int main()
{
    for(int i = 0; i< 200; i+=10)
    {
        printf("Next power of two for %d is %d\n", i, next_power_of_two(i));
    }
    
    return 0;
}