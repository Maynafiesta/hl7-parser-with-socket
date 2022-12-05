#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "edan_utils.h"
#include "edan_errors.h"
#include "edan_socket_utils.h"

size_t PRINT_STATUS = 2;    // 1 to list 2 to table

int main() {

    const char *ip_address = "192.168.1.115";
    const int port_num = 9100;

    int ret;
    if (PRINT_STATUS) {
        system("clear");
        if (2 == PRINT_STATUS) {
            print_result_header();
        }
    }

    Results *my_result;
    ret = allocate_result_package(&my_result);
    if (INSUFFICIENT_MEMORY_ERROR == ret) {
        printf("Insufficient memory!");
        exit(EXIT_FAILURE);
    }
    create_message_packet(my_result);

    for (size_t i = 0; i < 1000; ++i) {
//        clock_t clock_start = clock();
        ret = get_socket_package(my_result, ip_address, &port_num);
        if (CONNECTION_ERROR == ret) {
            printf("Connection Error!\n");
            exit(EXIT_FAILURE);
        } else if (EMPTY_PACKAGE_ERROR == ret) {
            printf("Empty Package taken!\n");
            continue;
        } else if (NO_ROUTE_ERROR == ret) {
            printf("No route to address, check ip address!\n");
            exit(EXIT_FAILURE);
        }
        if (2 == PRINT_STATUS)
            print_result_package_2(my_result);
        else if (1 == PRINT_STATUS)
            print_result_package_1(my_result);
        else {
            printf("Invalid print status: Only 1 or 2!");
            exit(EXIT_FAILURE);
        }

//        printf("total time: %lf \n", (double) (clock() - clock_start) / CLOCKS_PER_SEC);

    }
    free(my_result);

    return 0;
}

