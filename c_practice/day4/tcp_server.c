#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket bound successfully.\n");

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0)
    {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }
    printf("Listening for connections...\n");

    // Accept incoming connections
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Receive data from client
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0)
    {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }
    printf("Received data: %s\n", buffer);

    // Close socket
    close(client_fd);
    close(server_fd);

    return 0;
}