#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "10.7.227.79"  // Change as needed
#define SERVER_PORT 5678

int main() {
	int sockfd;
	struct sockaddr_in server_addr;
	char *message = "Hello from TCP client!";

	// Create TCP socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	memset(&(server_addr.sin_zero), '\0', 8);

	// Connect to server
	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	// Send message to server
	ssize_t sent_len = send(sockfd, message, strlen(message), 0);
	if (sent_len == -1) {
		perror("send");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	printf("Message sent to server: %s\n", message);

	close(sockfd);
	return 0;
}
