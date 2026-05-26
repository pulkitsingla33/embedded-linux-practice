#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main()
{
    char *str = "bcdabpqacfg";
    uint8_t visited[26];
    memset(visited, 0, 26);

    int left = 0, right = 0;
    int total_count = 0, max = 0;
    int str_length = strlen(str);

    if(str_length == 1)
    {
        printf("Longest substring is 1");
        return 0;
    }

    while(right <= str_length)
    {
        if(right == str_length)
        {
            total_count = right - left;
            if(total_count > max)
            {
                max = total_count;
            }
            break;
        }
        else if(!(visited[str[right] - 'a']))
        {
            visited[str[right] - 'a'] = 1;
            right++;
        }
        else
        {
            total_count = right - left;
            if(total_count > max)
            {
                max = total_count;
            }
            while(visited[str[right] - 'a'])
            {
                visited[str[left] - 'a'] = 0;
                left++;
            }
        }

    }

    printf("Longest substring is %d\n", max);

    return 0;
}