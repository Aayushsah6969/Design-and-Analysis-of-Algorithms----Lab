#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"   // Change if server is remote
#define SERVER_PORT 5678
#define BUFLEN 512

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buf[BUFLEN];
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    memset(&(server_addr.sin_zero), '\0', 8);

    // Input numbers from user
    int a, b, c;
    printf("Enter 3 numbers: ");
    scanf("%d %d %d", &a, &b, &c);

    char message[BUFLEN];
    snprintf(message, sizeof(message), "%d %d %d", a, b, c);

    // Send message to server
    if (sendto(sockfd, message, strlen(message), 0,
               (struct sockaddr *)&server_addr, addr_len) == -1) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server: %s\n", message);

    // Receive response from server
    ssize_t recv_len = recvfrom(sockfd, buf, BUFLEN - 1, 0,
                                (struct sockaddr *)&server_addr, &addr_len);
    if (recv_len == -1) {
        perror("recvfrom");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buf[recv_len] = '\0';
    printf("Received from server: %s\n", buf);

    close(sockfd);
    return 0;
}
