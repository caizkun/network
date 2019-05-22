#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLEN 1024


void setup_server() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[MAXLEN] = {0};
    char message[] = "Hello from server";

    // create a server socket
    // AF_INET: IPv4
    // SOCKET_DGRAM: UDP protocol
    printf("[SERVER] creates a socket\n");
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("[SERVER] socket creatation failed");
        exit(EXIT_FAILURE);
    }

    // configure server
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // bind
    printf("[SERVER] binds to IP and port\n");
    if (bind(server_fd, (struct sockaddr *) &server_addr, 
                            sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Receive and send message
    int msg_len = 0;
    socklen_t addr_len = 0;
    msg_len = recvfrom(server_fd, buffer, MAXLEN, MSG_WAITALL,
                       (struct sockaddr *) &client_addr, &addr_len);
    buffer[msg_len] = '\0';
    printf("[SERVER] received message: %s\n", buffer);
    sendto(server_fd, (const char*) message, strlen(message), 
            0, (const struct sockaddr *) &client_addr, addr_len);
    printf("[SERVER] message sent from server\n");
}


int main() {
    setup_server();
    return 0;
}
