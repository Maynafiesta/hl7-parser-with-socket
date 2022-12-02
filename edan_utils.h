#ifndef EDAN_UTILS_H
#define EDAN_UTILS_H

#include "edan_errors.h"

typedef enum {
    CM = 1, INCH = 2
} height_units;
typedef enum {
    KG = 1, LB = 2
} weight_units;

typedef struct {
    int nibp_sys;
    int nibp_dia;
    int nibp_map;
    int nibp_pr;
}Nibp;

typedef struct {
    float height_val;
    height_units height_unit;
} Height;

typedef struct {
    float weight_val;
    weight_units weight_unit;
} Weight;


typedef struct{
    int heart_rate_in_bpm;
    int pulse_rate_in_bpm;
    int spo2_in_percentage;
    int perfusion_index;        // PI
    int rr_interval_in_bpm;
    float temperature_in_celcius;
    char full_name[40];
    Height height_res;
    Weight weight_res;
    Nibp nibp_res;
}Results;

Results *message_parser(char *message_addr, Results *result_package);
Results *create_message_packet(Results* result_package);

void print_result_package_1(Results* result_package);
void print_result_package_2(Results* result_package);
int allocate_result_package(Results **result_package) ;

#endif //EDAN_UTILS_H
