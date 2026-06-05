#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    char file_name[100];

    snprintf(file_name, sizeof(file_name), "/proc/%s/status", argv[1]);

    FILE *file = fopen(file_name, "r");
    if(file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char line[512];
    char pid_str[64] = "";
    char ppid_str[64] = "";
    char state_str[256] = "";

    while(fgets(line, sizeof(line), file))
    {
        if(strncmp(line, "Pid:", 4) == 0)
            strcpy(pid_str, line);
        else if(strncmp(line, "PPid:", 5) == 0)
            strcpy(ppid_str, line);
        else if(strncmp(line, "State:", 6) == 0)
            strcpy(state_str, line);
    }

    fclose(file);

    printf("%s%s%s", pid_str, ppid_str, state_str);

    return 0;
}