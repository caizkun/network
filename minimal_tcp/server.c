#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define MAXLEN 1024

void setup_server() {
    int server_fd, client_fd, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    char buffer[MAXLEN] = {0};
    char message[] = "Hello from server";

    // create a server socket
    // AF_INET: IPv4 
    // SOCK_STREAM: TCP protocol
    printf("[SERVER] creates a socket\n");
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set socket option
//    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
//                                                &opt, sizeof(opt))) {
//        perror("setsockopt failed");
//        exit(EXIT_FAILURE);
//    }
    address.sin_family = AF_INET;           // IPv4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind
    printf("[SERVER] binds to IP and port\n");
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen
    printf("[SERVER] listens for connections\n");
    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // accept
    printf("[SERVER] accepts connection ...\n");
    if ((client_fd = accept(server_fd, (struct sockaddr *) &address, 
                                    (socklen_t *) &addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // send response
    valread = read(client_fd, buffer, 1024);
    printf("[SERVER] received message: ");
    printf("%s\n", buffer);
    send(client_fd, message, strlen(message), 0);
    printf("[SERVER] message sent from server\n");
    return;
}


int main(int argc, char const* argv[]) {
    setup_server();
    return 0;
}
