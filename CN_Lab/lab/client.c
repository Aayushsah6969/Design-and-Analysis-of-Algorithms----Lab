#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int client_socket;

    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) {
        printf("Client socket creation failed.\n");
        exit(1);  // Exit with error
    } else {
        printf("Client socket created successfully.\n");
    }

    close(client_socket);

    return 0;
}