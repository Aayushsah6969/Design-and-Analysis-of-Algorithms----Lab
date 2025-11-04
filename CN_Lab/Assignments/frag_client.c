#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER 1024  // total data to send
#define HEADER_SIZE 20   // our simulated header length

typedef struct {
    int id;
    int flag;       // 1 = more fragments, 0 = last fragment
    int offset;     // offset in payload
    int hl;         // header length
    int tl;         // total length (header+payload)
    char payload[512];
} fragment_t;

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Usage: %s <server_ip> <port> <data_size>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int data_size = atoi(argv[3]);
    if(data_size > MAX_BUFFER) data_size = MAX_BUFFER;

    // Prepare data
    char data[MAX_BUFFER];
    for(int i=0;i<data_size;i++) data[i]='A'+(i%26);

    // Detect MTU (simulate)
    int mtu = 100;  // small for demonstration
    printf("Client MTU size: %d\n", mtu);

    int max_payload = mtu - HEADER_SIZE;
    int n_fragments = (data_size + max_payload - 1)/max_payload;
    if(n_fragments > 1)
        printf("Data requires fragmentation. Total fragments: %d\n", n_fragments);
    else
        printf("Data fits in single packet.\n");

    // Socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serv.sin_addr);
    connect(sock, (struct sockaddr*)&serv, sizeof(serv));
    printf("Connected to server\n");

    // Send fragments
    int offset=0;
    for(int i=0;i<n_fragments;i++){
        fragment_t frag;
        frag.id = 1;
        frag.offset = offset;
        frag.hl = HEADER_SIZE;
        frag.tl = HEADER_SIZE + ((data_size-offset>max_payload)?max_payload:(data_size-offset));
        frag.flag = (i==n_fragments-1)?0:1;
        int payload_size = frag.tl - HEADER_SIZE;
        memcpy(frag.payload, data+offset, payload_size);

        printf("Sending Fragment %d: id=%d flag=%d offset=%d hl=%d tl=%d payload_size=%d\n",
            i+1, frag.id, frag.flag, frag.offset, frag.hl, frag.tl, payload_size);

        send(sock, &frag, sizeof(fragment_t), 0);
        offset += payload_size;
    }

    close(sock);
    printf("All fragments sent.\n");
    return 0;
}
