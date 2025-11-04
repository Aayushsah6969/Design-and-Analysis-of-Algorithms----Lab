#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define N 4  // window size

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    char msg[100], ack[20];
    socklen_t len = sizeof(serv);
    int base = 0, nextseq = 0;

    while (1) {
        // send packets in window
        while (nextseq < base + N) {
            sprintf(msg, "Packet %d", nextseq);
            sendto(s, msg, strlen(msg)+1, 0, (struct sockaddr*)&serv, len);
            printf("Sent: %s\n", msg);
            nextseq++;
        }

        // receive ACK
        ssize_t n = recvfrom(s, ack, sizeof(ack), 0, (struct sockaddr*)&serv, &len);
        if (n > 0) {
            int acknum = atoi(ack);
            if (acknum >= base) {
                base = acknum + 1;
                printf("Received ACK: %d\n", acknum);
            }
        }

        sleep(1);  // simulate delay
    }
}
