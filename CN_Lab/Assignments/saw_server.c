#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(s, (struct sockaddr*)&serv, sizeof(serv));

    char msg[100], ack[20];
    socklen_t len = sizeof(cli);
    int expected = 0;

    while (1) {
        ssize_t n = recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&cli, &len);
        if (n > 0) {
            printf("Received: %s\n", msg);
            sprintf(ack, "%d", expected);
            sendto(s, ack, strlen(ack)+1, 0, (struct sockaddr*)&cli, len);
            expected++;
        }
    }
}
