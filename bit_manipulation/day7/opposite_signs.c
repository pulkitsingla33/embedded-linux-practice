#include <stdio.h>

void haveOppositeSigns(int a, int b)
{
    if((a^b) >> 31)
        printf("Opposite Signs\n");
    else
        printf("Same signs\n");
}

int main(int args, char *argv[])
{
    int a = 10, b = 100;

    haveOppositeSigns(a, b);
}