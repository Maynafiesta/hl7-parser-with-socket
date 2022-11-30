#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include "edan_utils.h"

#define     PORT        9100


static const char *const ip_address = "192.168.1.46";
int PRINT_STATUS = 1;


int main(int argc, char const *argv[]) {

    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[4096] = {0};



    while (1) {
        system("clear");

        Results *my_result = (Results *) malloc(sizeof(Results));
        if (!my_result) {
            printf("Insufficient memory!\n");
            exit(EXIT_FAILURE);
        }

        create_message_packet(my_result);

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

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

        valread = read(sock, buffer, 4096);

        // Close the socket.
        close(client_fd);

        //Message parser to parse HL7 message.
        message_parser(buffer, my_result);

        if (PRINT_STATUS) {
            printf("%s\n", buffer);
            printf(" message length is : %lu\n", strlen(buffer));
            print_result_package(my_result);
        }

        free(my_result);

//        sleep(0.1);
    }

    printf("Connection Failed.\n");
    return 0;
}
