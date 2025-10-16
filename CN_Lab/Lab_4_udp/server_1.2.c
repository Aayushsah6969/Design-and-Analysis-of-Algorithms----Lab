#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MYPORT 5678
#define BUFLEN 512

// Function to reverse a string in place
void reverse_string(char *str) {
    int i, j;
    char temp;
    int len = strlen(str);

    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in my_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[BUFLEN];

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

    // Receive string from client
    ssize_t recv_len = recvfrom(sockfd, buf, BUFLEN - 1, 0,
                                (struct sockaddr *)&client_addr, &addr_len);
    if (recv_len == -1) {
        perror("recvfrom");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buf[recv_len] = '\0';
    printf("Received string: %s\n", buf);

    // Reverse the string
    reverse_string(buf);

    // Send reversed string back to client
    if (sendto(sockfd, buf, strlen(buf), 0,
               (struct sockaddr *)&client_addr, addr_len) == -1) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Reversed string sent back: %s\n", buf);

    close(sockfd);
    return 0;
}
