#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_SIZE 1024
#define TCP_PORT 6001

int main() {
    int sockfd, client_sockfd;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(TCP_PORT);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in bind");
        exit(EXIT_FAILURE);
    }

    // Listen for client connections
    if (listen(sockfd, 1) < 0) {
        perror("Error in listen");
        exit(EXIT_FAILURE);
    }

    printf("TCP Server is running and waiting for a client...\n");

    while (1) {
        client_len = sizeof(client_addr);

        // Accept a client connection
        client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
        if (client_sockfd < 0) {
            perror("Error in accept");
            exit(EXIT_FAILURE);
        }

        // Generate a random number within the range of 100 to 999
        int random_number = rand() % 900 + 100;

        // Convert the random number to a string
        sprintf(buffer, "%d", random_number);

        // Send the random number to the client
        ssize_t send_len = send(client_sockfd, buffer, strlen(buffer), 0);
        if (send_len < 0) {
            perror("Error in send");
            exit(EXIT_FAILURE);
        }

        // Close the client socket
        close(client_sockfd);
    }

    // Close the server socket
    close(sockfd);

    return 0;
}

