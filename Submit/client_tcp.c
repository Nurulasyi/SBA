#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_SIZE 1024
#define TCP_SERVER_IP "127.0.0.1"
#define TCP_SERVER_PORT 6001

int main() {
    int sockfd;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in server_addr;

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(TCP_SERVER_IP);
    server_addr.sin_port = htons(TCP_SERVER_PORT);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connect");
        exit(EXIT_FAILURE);
    }

    // Receive the random number from the server
    ssize_t recv_len = recv(sockfd, buffer, sizeof(buffer), 0);
    if (recv_len < 0) {
        perror("Error in recv");
        exit(EXIT_FAILURE);
    }

    buffer[recv_len] = '\0';
    int random_number = atoi(buffer);

    printf("TCP Client: Received random number: %d\n", random_number);

    // Close the socket
    close(sockfd);

    return 0;
}

