#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

#define MYPORT 5679
#define BUFLEN 512

// Function to check Armstrong number
int isArmstrong(int num) {
    int original = num, sum = 0, digits = 0, temp;

    temp = num;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, digits);
        temp /= 10;
    }

    return (sum == original);
}

int main() {
    int sockfd, new_fd;
    struct sockaddr_in my_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[BUFLEN];

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
    if (listen(sockfd, 1) == -1) {
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for TCP connection...\n");

    // Accept connection
    new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
    if (new_fd == -1) {
        perror("accept");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive number from client
    ssize_t recv_len = recv(new_fd, buf, BUFLEN - 1, 0);
    if (recv_len == -1) {
        perror("recv");
        close(new_fd);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buf[recv_len] = '\0';
    int number = atoi(buf);
    printf("Received number: %d\n", number);

    // Check Armstrong
    char result[BUFLEN];
    if (isArmstrong(number)) {
        snprintf(result, sizeof(result), "%d is an Armstrong number", number);
    } else {
        snprintf(result, sizeof(result), "%d is NOT an Armstrong number", number);
    }

    // Send result to client
    if (send(new_fd, result, strlen(result), 0) == -1) {
        perror("send");
    } else {
        printf("Result sent to client: %s\n", result);
    }

    close(new_fd);
    close(sockfd);
    return 0;
}
