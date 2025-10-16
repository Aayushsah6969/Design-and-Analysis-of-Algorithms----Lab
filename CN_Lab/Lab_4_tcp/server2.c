#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MYPORT 5678
#define BUFLEN 512

int main() {
    int sockfd, client1_fd, client2_fd;
    struct sockaddr_in my_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf1[BUFLEN], buf2[BUFLEN];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(sockfd, 2) == -1) {
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for 2 clients...\n");

    // Accept first client
    client1_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
    if (client1_fd == -1) {
        perror("accept client1");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Client 1 connected!\n");

    // Accept second client
    client2_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
    if (client2_fd == -1) {
        perror("accept client2");
        close(client1_fd);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Client 2 connected!\n");

    // Receive number from client 1
    ssize_t recv_len1 = recv(client1_fd, buf1, BUFLEN - 1, 0);
    if (recv_len1 <= 0) {
        perror("recv client1");
        close(client1_fd);
        close(client2_fd);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buf1[recv_len1] = '\0';
    printf("Received from Client 1: %s\n", buf1);

    // Receive number from client 2
    ssize_t recv_len2 = recv(client2_fd, buf2, BUFLEN - 1, 0);
    if (recv_len2 <= 0) {
        perror("recv client2");
        close(client1_fd);
        close(client2_fd);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buf2[recv_len2] = '\0';
    printf("Received from Client 2: %s\n", buf2);

    // Exchange numbers
    if (send(client1_fd, buf2, strlen(buf2), 0) == -1) {
        perror("send to client1");
    } else {
        printf("Sent to Client 1: %s\n", buf2);
    }

    if (send(client2_fd, buf1, strlen(buf1), 0) == -1) {
        perror("send to client2");
    } else {
        printf("Sent to Client 2: %s\n", buf1);
    }

    close(client1_fd);
    close(client2_fd);
    close(sockfd);

    return 0;
}
