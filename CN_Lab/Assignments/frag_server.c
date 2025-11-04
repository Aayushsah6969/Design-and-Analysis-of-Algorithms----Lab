#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HEADER_SIZE 20
#define MAX_BUFFER 1024

typedef struct {
    int id;
    int flag;
    int offset;
    int hl;
    int tl;
    char payload[512];
} fragment_t;

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr*)&serv, sizeof(serv));
    listen(sock,5);
    printf("Server listening on port %d\n", port);

    socklen_t len = sizeof(cli);
    int newsock = accept(sock,(struct sockaddr*)&cli,&len);
    printf("Client connected\n");

    fragment_t frags[20]; // store fragments
    int count=0;
    int total_size=0;
    int fragmented = 0;

    while(1){
        fragment_t frag;
        ssize_t n = recv(newsock, &frag, sizeof(fragment_t), 0);
        if(n<=0) break;

        if(frag.flag==1) fragmented=1;

        printf("Received Fragment %d: id=%d flag=%d offset=%d hl=%d tl=%d payload_size=%d\n",
            count+1, frag.id, frag.flag, frag.offset, frag.hl, frag.tl, frag.tl - frag.hl);

        frags[count++] = frag;
        total_size += frag.tl - frag.hl;

        if(frag.flag==0) break; // last fragment
    }

    if(fragmented) printf("Data was fragmented. Reassembling...\n");
    else printf("Data was not fragmented.\n");

    // Reassembly
    char assembled[MAX_BUFFER];
    for(int i=0;i<count;i++){
        memcpy(assembled+frags[i].offset, frags[i].payload, frags[i].tl - frags[i].hl);
    }

    assembled[total_size]='\0';
    printf("Reassembled Data (%d bytes): %s\n", total_size, assembled);

    close(newsock);
    close(sock);
    return 0;
}
