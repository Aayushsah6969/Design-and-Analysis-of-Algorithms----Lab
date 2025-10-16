#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MYPORT 5678
#define BUFLEN 512

int main() {
	int sockfd, new_fd;
	struct sockaddr_in my_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);
	char buf[BUFLEN];

	// Create TCP socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), '\0', 8);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) == -1) {
		perror("bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 1) == -1) {
		perror("listen");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	printf("Waiting for TCP connection...\n");

	new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
	if (new_fd == -1) {
		perror("accept");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	ssize_t recv_len = recv(new_fd, buf, BUFLEN - 1, 0);
	if (recv_len == -1) {
		perror("recv");
		close(new_fd);
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	buf[recv_len] = '\0';  // Null-terminate the received string
	printf("Received message: %s\n", buf);

	close(new_fd);
	close(sockfd);
	return 0;
}
