#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // Change if server is remote
#define SERVER_PORT 5678
#define BUFLEN 512

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buf[BUFLEN];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    memset(&(server_addr.sin_zero), '\0', 8);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Input roll number
    int roll;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    char message[BUFLEN];
    snprintf(message, sizeof(message), "%d", roll);

    // Send roll number to server
    if (send(sockfd, message, strlen(message), 0) == -1) {
        perror("send");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Roll number sent: %s\n", message);

    // Receive student details from server
    ssize_t recv_len = recv(sockfd, buf, BUFLEN - 1, 0);
    if (recv_len <= 0) {
        perror("recv");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buf[recv_len] = '\0';
    printf("Received from server: %s\n", buf);

    close(sockfd);
    return 0;
}
