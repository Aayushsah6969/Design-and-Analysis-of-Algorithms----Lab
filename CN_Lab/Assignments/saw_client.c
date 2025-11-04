#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    char msg[100], ack[20];
    socklen_t len = sizeof(serv);
    int seq = 0;

    while (1) {
        sprintf(msg, "Packet %d", seq);
        sendto(s, msg, strlen(msg)+1, 0, (struct sockaddr*)&serv, len);
        ssize_t n = recvfrom(s, ack, sizeof(ack), 0, (struct sockaddr*)&serv, &len);
        if (n > 0 && atoi(ack) == seq) {
            printf("Received ACK %s\n", ack);
            seq++;
        }
        sleep(1);
    }
}
