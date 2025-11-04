#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serv.sin_addr);

    connect(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    printf("Connected to server %s:%d\n", ip, port);

    char buf[100];
    while (1) {
        printf("Enter message: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0; // remove newline
        write(sockfd, buf, strlen(buf));

        ssize_t n = read(sockfd, buf, sizeof(buf)-1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("Server echo: %s\n", buf);
    }

    close(sockfd);
}
