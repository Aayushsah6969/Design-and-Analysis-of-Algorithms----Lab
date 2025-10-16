#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_socket;
    struct sockaddr_in server_addr;

    // Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("Server socket creation failed.\n");
        exit(1);
    } else {
        printf("Server socket created successfully.\n");
    }

    // Configure server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // Port 8080
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Or inet_addr("127.0.0.1")

    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Server bind failed.\n");
        close(server_socket);
        exit(1);
    } else {
        printf("Server bind successful.\n");
    }

    close(server_socket);
    return 0;
}