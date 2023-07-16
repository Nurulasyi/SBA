#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9999
#define BUFFER_SIZE 1024

int main() {
    // Create a UDP socket
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
    if (inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr)) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    // Send a request to the server
    char buffer[BUFFER_SIZE] = "Random number request";
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Receive the random number from the server
    int random_number;
    socklen_t server_len = sizeof(server_addr);
    ssize_t num_bytes = recvfrom(sockfd, &random_number, sizeof(random_number), 0,
                                 (struct sockaddr*)&server_addr, &server_len);
    if (num_bytes < 0) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }

    // Display the received random number
    printf("Random number received: %d\n", random_number);

    // Close the socket
    close(sockfd);

    return 0;
}

