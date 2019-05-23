#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define IP_ADDR "127.0.0.1"
#define PORT 8080
#define MAXLEN 1024


void setup_client() {
    int client_fd;
    struct sockaddr_in server_addr; 
    char buffer[MAXLEN];
    char message[] = "Hello from client";

    // creates a client socket
    printf("[CLIENT] creates a socket\n");
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // configure server information
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = INADDR_ANY; // any interfaces
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
    server_addr.sin_port = htons(PORT);
    //if (inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr) <= 0) {
    //    perror("invalid address");
    //    exit(EXIT_FAILURE);
    //}
    //printf("%d\n", server_addr.sin_addr.s_addr);
    
    // send and receive message
    int msg_len = 0;
    socklen_t addr_len = sizeof(server_addr); // size is important!!
    sendto(client_fd, (const char *) message, strlen(message),
            0, (const struct sockaddr *) &server_addr, addr_len);
    printf("[CLIENT] message sent from client\n");
    msg_len = recvfrom(client_fd, buffer, MAXLEN, MSG_WAITALL, 
                        (struct sockaddr *) &server_addr, &addr_len);   
    //printf("%d\n", server_addr.sin_addr.s_addr);
    buffer[msg_len] = '\0';
    printf("[CLIENT] received message: %s\n", buffer);

    close(client_fd);
    return;
}


int main() {
    setup_client();
    return 0;
}
