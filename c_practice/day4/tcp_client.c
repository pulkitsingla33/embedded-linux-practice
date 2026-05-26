#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in server_addr;
    const char *message = "Hello, Server!";

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
    {
        perror("Invalid server IP address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");

    int message_len = strlen(message);
    ssize_t bytes_sent = send(sock_fd, message, message_len, 0);
    if (bytes_sent < 0)
    {
        perror("Error sending message");
        exit(EXIT_FAILURE);
    }
    printf("Message sent to server: %s\n", message);

    close(sock_fd);

    return 0;
}