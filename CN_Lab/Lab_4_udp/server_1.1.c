#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MYPORT 5678
#define BUFLEN 512

int main() {
    int sockfd;
    struct sockaddr_in my_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[BUFLEN];
    int num1, num2, num3, sum;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("UDP Server is waiting for data...\n");

    // Receive message from client
    ssize_t recv_len = recvfrom(sockfd, buf, BUFLEN - 1, 0,
                                (struct sockaddr *)&client_addr, &addr_len);
    if (recv_len == -1) {
        perror("recvfrom");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buf[recv_len] = '\0';
    printf("Received message: %s\n", buf);

    // Parse numbers and compute sum
    sscanf(buf, "%d %d %d", &num1, &num2, &num3);
    sum = num1 + num2 + num3;

    // Send result back to client
    char result[BUFLEN];
    snprintf(result, sizeof(result), "Sum = %d", sum);

    if (sendto(sockfd, result, strlen(result), 0,
               (struct sockaddr *)&client_addr, addr_len) == -1) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Result sent to client: %s\n", result);

    close(sockfd);
    return 0;
}
