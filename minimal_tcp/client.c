#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


#define PORT 8080
#define IP_ADDR "127.0.0.1"


void setup_client() {
    struct sockaddr_in address;
    struct sockaddr_in server_addr;
    int client_fd = 0, valread;
    char message[] = "Hello from client";
    char buffer[1024] = {0};
    
    // create a client socket
    printf("[CLIENT] creates a socket\n");
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("client socket failed");
        exit(EXIT_FAILURE);
    }

    // set server_addr
    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // convert IP address from text to binary from
    if (inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr) <= 0) {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    // connect
    printf("[CLIENT] connects to server\n");
    if (connect(client_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // send request
    send(client_fd, message, strlen(message), 0);
    printf("[CLIENT] message sent from client\n");
    valread = read(client_fd, buffer, 1024);
    printf("[CLIENT] received message: ");
    printf("%s\n", buffer);
    return;
}


int main(int argc, char *argv[]) {
    setup_client();
    return 0;
}
