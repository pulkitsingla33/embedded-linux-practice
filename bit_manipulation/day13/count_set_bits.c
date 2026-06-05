#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);

    int result[N];
    result[0] = 0;
    printf("0 -> 0\n");

    for(int i = 1; i < N; i++)
    {
        result[i] = result[i>>1] + (i & 1);
        printf("%d -> %d\n", i, result[i]);
    }

    return 0;
}