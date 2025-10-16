#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MYPORT 5678
#define BUFLEN 512

// Define student structure
struct Student {
    int rollno;
    char name[50];
    int marks;
};

// Demo student database
struct Student database[] = {
    {1, "Alice", 85},
    {2, "Bob", 90},
    {3, "Charlie", 78},
    {4, "David", 88},
    {5, "Eve", 92}
};
int db_size = 5;

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

    // Receive roll number from client
    ssize_t recv_len = recv(new_fd, buf, BUFLEN - 1, 0);
    if (recv_len <= 0) {
        perror("recv");
        close(new_fd);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buf[recv_len] = '\0';
    int roll = atoi(buf);
    printf("Received roll no: %d\n", roll);

    // Search student in database
    char result[BUFLEN];
    int found = 0;
    for (int i = 0; i < db_size; i++) {
        if (database[i].rollno == roll) {
            snprintf(result, sizeof(result), "Roll: %d, Name: %s, Marks: %d",
                     database[i].rollno, database[i].name, database[i].marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        snprintf(result, sizeof(result), "Roll no %d not found!", roll);
    }

    // Send response to client
    if (send(new_fd, result, strlen(result), 0) == -1) {
        perror("send");
    } else {
        printf("Sent to client: %s\n", result);
    }

    close(new_fd);
    close(sockfd);
    return 0;
}
