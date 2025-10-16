#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAXDATASIZE 100
#define STDIN 0

int main(int argc, char *argv[]) {
    int fd, numbytes;
    char buf[MAXDATASIZE], input[1000];
    struct sockaddr_in server;
    fd_set rset, master;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    connect(fd, (struct sockaddr*)&server, sizeof(server));

    FD_ZERO(&master);
    FD_SET(fd, &master);
    FD_SET(STDIN, &master);

    while (1) {
        rset = master;
        select(fd + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(fd, &rset)) {
            numbytes = recv(fd, buf, MAXDATASIZE, 0);
            buf[numbytes] = '\0';
            printf("Server: %s\n", buf);
            if (strncmp(buf, "exit", 4) == 0) break;
        }
        if (FD_ISSET(STDIN, &rset)) {
            fgets(input, sizeof(input), stdin);
            send(fd, input, strlen(input), 0);
        }
    }
    close(fd);
}
