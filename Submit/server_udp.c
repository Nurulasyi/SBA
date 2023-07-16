#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>

#define SERVER_PORT 9999
#define BUFFER_SIZE 1024

int main() {
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Generate a random number between 100 and 999
    srand(time(NULL));
    int random_number = rand() % 900 + 100;

    // Loop to handle client requests
    while (1) {
        // Receive data from client
        char buffer[BUFFER_SIZE];
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        ssize_t num_bytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                     (struct sockaddr*)&client_addr, &client_len);
        if (num_bytes < 0) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        // Send the random number to the client
        sendto(sockfd, &random_number, sizeof(random_number), 0,
               (struct sockaddr*)&client_addr, client_len);
    }

    // Close the socket
    close(sockfd);

    return 0;
}

