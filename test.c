#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "edan_utils.h"
#include "edan_errors.h"
#include "edan_socket_utils.h"


int main(int argc, char const *argv[]) {

    const char* ip_address = "192.168.1.46";
    const int port_num = 9100;

    int ret;

    system("clear");

    Results *my_result;
    ret = allocate_result_package(&my_result);
    if (INSUFFICIENT_MEMORY_ERROR == ret || 0 != ret) {
        printf("Insufficient memory!");
        exit(EXIT_FAILURE);
    }
    create_message_packet(my_result);

    for(size_t i = 0; i < 10; ++i) {
        clock_t clock_start = clock();

    get_socket_package(my_result, ip_address, port_num);

//    print_result_package(my_result);

    printf("total time: %lf \n", (double)(clock() - clock_start) / CLOCKS_PER_SEC);

    }
    free(my_result);

    return 0;
}
