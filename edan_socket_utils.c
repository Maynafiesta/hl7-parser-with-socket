#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "edan_socket_utils.h"

#define MESSAGE_SIZE 4096

int get_socket_package(Results* result_package, const char *const ip_address, const int port) {
    char* message_buffer = (char*)malloc(sizeof(char) * MESSAGE_SIZE);
    if (!message_buffer) {
        printf("Insufficient memory!");
        return INSUFFICIENT_MEMORY_ERROR;
    }
    int sock, valread, client_fd;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    if ((client_fd = connect(sock, (struct sockaddr *) &serv_addr,sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }

//        send(sock, hello, strlen(hello), 0);

    valread = (int)read(sock, message_buffer, 4096);
    if (-1 == valread) {
        printf("\nEmpty package read.\n");
        return -1;
    }
    close(client_fd);

    //Message parser to parse HL7 message.
    message_parser(message_buffer, result_package);
    free(message_buffer);
}
