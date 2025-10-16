#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MYPORT 5678
#define BUFLEN 512

int main() {
    int sockfd;
    struct sockaddr_in my_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[BUFLEN];

    // Create UDP socket
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port and IP (use INADDR_ANY to bind to all available)
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) == -1) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting to receive message...\n");

    ssize_t recv_len = recvfrom(sockfd, buf, BUFLEN - 1, 0, (struct sockaddr *)&client_addr, &addr_len);
    if (recv_len == -1) {
        perror("recvfrom");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buf[recv_len] = '\0';  // Null-terminate the received string
    printf("Received message: %s\n", buf);

    close(sockfd);
    return 0;
}
