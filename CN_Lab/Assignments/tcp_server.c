#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    listen(sockfd, 5);
    printf("Server listening on port %d...\n", port);

    socklen_t len = sizeof(cli);
    int newsock = accept(sockfd, (struct sockaddr*)&cli, &len);
    printf("Client connected!\n");

    char buf[100];
    while (1) {
        ssize_t n = read(newsock, buf, sizeof(buf)-1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("Received: %s\n", buf);
        write(newsock, buf, strlen(buf));  // echo back
    }

    close(newsock);
    close(sockfd);
}

