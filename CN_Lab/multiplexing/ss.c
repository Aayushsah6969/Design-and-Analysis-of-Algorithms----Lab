#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define BACKLOG 2
#define MAXDATASIZE 1000

int main(int argc, char *argv[]) {
    int listen_fd, conn_fd, client_fd[FD_SETSIZE], max_fd, max_index = 0;
    struct sockaddr_in server, client;
    fd_set all_set, read_set;
    char buf[MAXDATASIZE];

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bind(listen_fd, (struct sockaddr*)&server, sizeof(server));
    listen(listen_fd, BACKLOG);

    for (int i = 0; i < FD_SETSIZE; i++) client_fd[i] = -1;
    FD_ZERO(&all_set);
    FD_SET(listen_fd, &all_set);
    max_fd = listen_fd;

    while (1) {
        read_set = all_set;
        select(max_fd + 1, &read_set, NULL, NULL, NULL);

        if (FD_ISSET(listen_fd, &read_set)) {
            socklen_t len = sizeof(client);
            conn_fd = accept(listen_fd, (struct sockaddr*)&client, &len);
            client_fd[max_index++] = conn_fd;
            FD_SET(conn_fd, &all_set);
            if (conn_fd > max_fd) max_fd = conn_fd;
            printf("New connection: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        }

        for (int i = 0; i < max_index; i++) {
            int fd = client_fd[i];
            if (fd != -1 && FD_ISSET(fd, &read_set)) {
                int n = recv(fd, buf, MAXDATASIZE, 0);
                if (n > 0) {
                    buf[n] = '\0';
                    printf("Client: %s", buf);
                    fgets(buf, MAXDATASIZE, stdin);
                    send(fd, buf, strlen(buf), 0);
                }
            }
        }
    }
}
