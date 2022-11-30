#include "edan_utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
//      MACROS
//

//#define     PORT    9100
#define PUBLIC
#define PRIVATE static

//
//      LOCAL VARIABLES
//

PRIVATE const char *const ip_address = "192.168.1.46";

PRIVATE const char *const height_header = "HEIGHT";
PRIVATE const char *const weight_header = "WEIGHT";
PRIVATE const char *const spo2_header = "SpO2";
PRIVATE const char *const temperature_header = "T1";
PRIVATE const char *const heart_rate_header = "HR";
PRIVATE const char *const pulse_rate_header = "PR";
PRIVATE const char *const nibp_sys_header = "NIBP_SYS";
PRIVATE const char *const nibp_dia_header = "NIBP_DIA";
PRIVATE const char *const nibp_map_header = "NIBP_MAP";
PRIVATE const char *const nibp_pr_header = "NIBP_PR";

PRIVATE const char *const rr_header = "RR";
PRIVATE const char *const pi_header = "PI";

PRIVATE const char *const type_header = "<OBX.3>";
PRIVATE const char *const value_header = "<OBX.5>";
PRIVATE const char *const unit_header = "<OBX.6>";
PRIVATE const char *const interval_header = "<OBX.7>";

PRIVATE const char *const value_endcode = "</OBX.5>";

PRIVATE const char *const observation_date_header = "<OBR.7>";

PRIVATE const char *const full_name_header = "<PID.5>";
PRIVATE const char *const full_name_endcode = "</PID.5>";


//
//      PRIVATE FUNCTIONS
//

PRIVATE Results *get_weight_package(char *message_addr, Results *result_package) {
    // Find related header
    char *weight_start_addr = strstr(message_addr, weight_header);
    if (!weight_start_addr) {
        printf("Invalid argument: %s\n", weight_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *weight_val_start_addr = strstr(weight_start_addr, value_header);
    if (!weight_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *weight_val_end_addr = strstr(weight_val_start_addr, value_endcode);
    if (!weight_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *weight_val_str = (char *) malloc((weight_val_end_addr - weight_val_start_addr) * sizeof(char));
    if (!weight_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(weight_val_str, weight_val_start_addr + strlen(value_header),
            (weight_val_end_addr - weight_val_start_addr));
    // Str to float conversion.
    (*result_package).weight_res.weight_val = strtof(weight_val_str, NULL);
    /*
     * todo
     * Part gets unit will be added
     */
    (*result_package).weight_res.weight_unit = KG;
    // Release allocated string memory.
    free(weight_val_str);
    return result_package;
}

PRIVATE Results *get_height_package(char *message_addr, Results *result_package) {

    // Find related header
    char *height_start_addr = strstr(message_addr, height_header);
    if (!height_start_addr) {
        printf("Invalid argument: %s\n", weight_header);
        return 0;
    }

    // Find value header => "<OBX.5>"
    char *height_val_start_addr = strstr(height_start_addr, value_header);
    if (!height_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }

    // Find the address of numeric value end => "</OBX.5>"
    char *height_val_end_addr = strstr(height_val_start_addr, value_endcode);
    if (!height_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }

    // Allocate the memory block to handle conversion operation.
    char *height_val_str = (char *) malloc((height_val_end_addr - height_val_start_addr) * sizeof(char));
    if (!height_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }

    // Get the exact floating value as char array.
    strncpy(height_val_str, height_val_start_addr + strlen(value_header),
            (height_val_end_addr - height_val_start_addr));

    // Str to float conversion.
    (*result_package).height_res.height_val = strtof(height_val_str, NULL);
    /*
     * todo
     * Part gets unit will be added
     */
    (*result_package).height_res.height_unit = CM;
    // Release allocated string memory.
    free(height_val_str);
    return result_package;
}

PRIVATE Results *get_heart_rate(char *message_addr, Results *result_package) {
    // Find related header
    char *heart_rate_start_addr = strstr(message_addr, heart_rate_header);
    if (!heart_rate_start_addr) {
        printf("Invalid argument: %s\n", heart_rate_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *heart_rate_val_start_addr = strstr(heart_rate_start_addr, value_header);
    if (!heart_rate_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *heart_rate_val_end_addr = strstr(heart_rate_val_start_addr, value_endcode);
    if (!heart_rate_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *heart_rate_val_str = (char *) malloc((heart_rate_val_end_addr - heart_rate_val_start_addr) * sizeof(char));
    if (!heart_rate_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(heart_rate_val_str, heart_rate_val_start_addr + strlen(value_header),
            (heart_rate_val_end_addr - heart_rate_val_start_addr));
    // Str to float conversion.
    (*result_package).heart_rate_in_bpm = (int)strtol(heart_rate_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(heart_rate_val_str);
    return result_package;
}

PRIVATE Results *get_pulse_rate(char *message_addr, Results *result_package) {
    // Find related header
    char *pulse_rate_start_addr = strstr(message_addr, pulse_rate_header);
    if (!pulse_rate_start_addr) {
        printf("Invalid argument: %s\n", pulse_rate_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *pulse_rate_val_start_addr = strstr(pulse_rate_start_addr, value_header);
    if (!pulse_rate_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *pulse_rate_val_end_addr = strstr(pulse_rate_val_start_addr, value_endcode);
    if (!pulse_rate_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *pulse_rate_val_str = (char *) malloc((pulse_rate_val_end_addr - pulse_rate_val_start_addr) * sizeof(char));
    if (!pulse_rate_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(pulse_rate_val_str, pulse_rate_val_start_addr + strlen(value_header),
            (pulse_rate_val_end_addr - pulse_rate_val_start_addr));
    // Str to float conversion.
    (*result_package).pulse_rate_in_bpm = (int)strtol(pulse_rate_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(pulse_rate_val_str);
    return result_package;
}

PRIVATE Results *get_nibp_sys(char *message_addr, Results *result_package) {
    // Find related header
    char *nibp_sys_start_addr = strstr(message_addr, nibp_sys_header);
    if (!nibp_sys_start_addr) {
        printf("Invalid argument: %s\n", nibp_sys_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *nibp_sys_val_start_addr = strstr(nibp_sys_start_addr, value_header);
    if (!nibp_sys_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *nibp_sys_val_end_addr = strstr(nibp_sys_val_start_addr, value_endcode);
    if (!nibp_sys_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *nibp_sys_val_str = (char *) malloc((nibp_sys_val_end_addr - nibp_sys_val_start_addr) * sizeof(char));
    if (!nibp_sys_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(nibp_sys_val_str, nibp_sys_val_start_addr + strlen(value_header),
            (nibp_sys_val_end_addr - nibp_sys_val_start_addr));
    // Str to float conversion.
    (*result_package).nibp_res.nibp_sys = (int)strtol(nibp_sys_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(nibp_sys_val_str);
    return result_package;
}

PRIVATE Results *get_nibp_dia(char *message_addr, Results *result_package) {
    // Find related header
    char *nibp_dia_start_addr = strstr(message_addr, nibp_dia_header);
    if (!nibp_dia_start_addr) {
        printf("Invalid argument: %s \n", nibp_dia_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *nibp_dia_val_start_addr = strstr(nibp_dia_start_addr, value_header);
    if (!nibp_dia_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *nibp_dia_val_end_addr = strstr(nibp_dia_val_start_addr, value_endcode);
    if (!nibp_dia_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *nibp_dia_val_str = (char *) malloc((nibp_dia_val_end_addr - nibp_dia_val_start_addr) * sizeof(char));
    if (!nibp_dia_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(nibp_dia_val_str, nibp_dia_val_start_addr + strlen(value_header),
            (nibp_dia_val_end_addr - nibp_dia_val_start_addr));
    // Str to float conversion.
    (*result_package).nibp_res.nibp_dia = (int)strtol(nibp_dia_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(nibp_dia_val_str);
    return result_package;
}

PRIVATE Results *get_nibp_map(char *message_addr, Results *result_package) {
    // Find related header
    char *nibp_map_start_addr = strstr(message_addr, nibp_map_header);
    if (!nibp_map_start_addr) {
        printf("Invalid argument: %s\n", nibp_map_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *nibp_map_val_start_addr = strstr(nibp_map_start_addr, value_header);
    if (!nibp_map_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *nibp_map_val_end_addr = strstr(nibp_map_val_start_addr, value_endcode);
    if (!nibp_map_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *nibp_map_val_str = (char *) malloc((nibp_map_val_end_addr - nibp_map_val_start_addr) * sizeof(char));
    if (!nibp_map_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(nibp_map_val_str, nibp_map_val_start_addr + strlen(value_header),
            (nibp_map_val_end_addr - nibp_map_val_start_addr));
    // Str to float conversion.
    (*result_package).nibp_res.nibp_map = (int)strtol(nibp_map_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(nibp_map_val_str);
    return result_package;
}

PRIVATE Results *get_nibp_pr(char *message_addr, Results *result_package) {
    // Find related header
    char *nibp_pr_start_addr = strstr(message_addr, nibp_pr_header);
    if (!nibp_pr_start_addr) {
        printf("Invalid argument: %s\n", nibp_pr_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *nibp_pr_val_start_addr = strstr(nibp_pr_start_addr, value_header);
    if (!nibp_pr_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *nibp_pr_val_end_addr = strstr(nibp_pr_val_start_addr, value_endcode);
    if (!nibp_pr_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *nibp_pr_val_str = (char *) malloc((nibp_pr_val_end_addr - nibp_pr_val_start_addr) * sizeof(char));
    if (!nibp_pr_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(nibp_pr_val_str, nibp_pr_val_start_addr + strlen(value_header),
            (nibp_pr_val_end_addr - nibp_pr_val_start_addr));
    // Str to float conversion.
    (*result_package).nibp_res.nibp_pr = (int)strtol(nibp_pr_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(nibp_pr_val_str);
    return result_package;
}

PRIVATE Results *get_spo2(char *message_addr, Results *result_package) {
    // Find related header
    char *spo2_start_addr = strstr(message_addr, spo2_header);
    if (!spo2_start_addr) {
        printf("Invalid argument: %s\n", spo2_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *spo2_val_start_addr = strstr(spo2_start_addr, value_header);
    if (!spo2_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *spo2_val_end_addr = strstr(spo2_val_start_addr, value_endcode);
    if (!spo2_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *spo2_val_str = (char *) malloc((spo2_val_end_addr - spo2_val_start_addr) * sizeof(char));
    if (!spo2_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(spo2_val_str, spo2_val_start_addr + strlen(value_header),
            (spo2_val_end_addr - spo2_val_start_addr));
    // Str to float conversion.
    (*result_package).spo2_in_percentage = (int)strtol(spo2_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(spo2_val_str);
    return result_package;
}

PRIVATE Results *get_perfusion_index(char *message_addr, Results *result_package) {
    // Find related header
    char *perfusion_index_start_addr = strstr(message_addr, pi_header);
    if (!perfusion_index_start_addr) {
        printf("Invalid argument: %s\n", pi_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *perfusion_index_val_start_addr = strstr(perfusion_index_start_addr, value_header);
    if (!perfusion_index_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *perfusion_index_val_end_addr = strstr(perfusion_index_val_start_addr, value_endcode);
    if (!perfusion_index_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *perfusion_index_val_str = (char *) malloc((perfusion_index_val_end_addr - perfusion_index_val_start_addr) * sizeof(char));
    if (!perfusion_index_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(perfusion_index_val_str, perfusion_index_val_start_addr + strlen(value_header),
            (perfusion_index_val_end_addr - perfusion_index_val_start_addr));
    // Str to float conversion.
    (*result_package).perfusion_index = (int)strtol(perfusion_index_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(perfusion_index_val_str);
    return result_package;
}

PRIVATE Results *get_rr_interval(char *message_addr, Results *result_package) {
    // Find related header
    char *rr_interval_start_addr = strstr(message_addr, rr_header);
    if (!rr_interval_start_addr) {
        printf("Invalid argument: %s\n", rr_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *rr_interval_val_start_addr = strstr(rr_interval_start_addr, value_header);
    if (!rr_interval_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *rr_interval_val_end_addr = strstr(rr_interval_val_start_addr, value_endcode);
    if (!rr_interval_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *rr_interval_val_str = (char *) malloc((rr_interval_val_end_addr - rr_interval_val_start_addr) * sizeof(char));
    if (!rr_interval_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(rr_interval_val_str, rr_interval_val_start_addr + strlen(value_header),
            (rr_interval_val_end_addr - rr_interval_val_start_addr));
    // Str to float conversion.
    (*result_package).rr_interval_in_bpm = (int)strtol(rr_interval_val_str, NULL, 10);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(rr_interval_val_str);
    return result_package;
}

PRIVATE Results *get_temperature(char *message_addr, Results *result_package) {
    // Find related header
    char *temperature_start_addr = strstr(message_addr, temperature_header);
    if (!temperature_start_addr) {
        printf("Invalid argument: %s\n", temperature_header);
        return 0;
    }
    // Find value header => "<OBX.5>"
    char *temperature_val_start_addr = strstr(temperature_start_addr, value_header);
    if (!temperature_val_start_addr) {
        printf("Invalid argument: %s\n", value_header);
        return 0;
    }
    // Find the address of numeric value end => "</OBX.5>"
    char *temperature_val_end_addr = strstr(temperature_val_start_addr, value_endcode);
    if (!temperature_val_end_addr) {
        printf("Invalid argument: %s\n", value_endcode);
        return 0;
    }
    // Allocate the memory block to handle conversion operation.
    char *temperature_val_str = (char *) malloc((temperature_val_end_addr - temperature_val_start_addr) * sizeof(char));
    if (!temperature_val_str) {
        printf("Insufficient memory at value parsing!");
        return 0;
    }
    // Get the exact floating value as char array.
    strncpy(temperature_val_str, temperature_val_start_addr + strlen(value_header),
            (temperature_val_end_addr - temperature_val_start_addr));
    // Str to float conversion.
    (*result_package).temperature_in_celcius = strtof(temperature_val_str, NULL);
    /*
     * todo
     * Part gets unit will be added
     */
    // Release allocated string memory.
    free(temperature_val_str);
    return result_package;
}

PRIVATE Results *get_full_name(char *message_addr, Results *result_package) {
    // Find value header => "<PID.5>"
    char *full_name_start_addr = strstr(message_addr, full_name_header);
    if (!full_name_start_addr) {
        printf("Invalid argument: %s\n", full_name_header);
        return 0;
    }
    // Find the address of name end => "</PID.5>"
    char *full_name_end_addr = strstr(full_name_start_addr, full_name_endcode);
    if (!full_name_end_addr) {
        printf("Invalid argument: %s\n", full_name_endcode);
        return 0;
    }
    // Copy the name to the result package.
    strncpy((*result_package).full_name, full_name_start_addr + strlen(full_name_header),
            (full_name_end_addr - full_name_start_addr) - strlen(full_name_endcode) + 1);

    return result_package;
}

//
//      PUBLIC FUNCTIONS
//

PUBLIC Results *create_message_packet(Results *result_package) {
    (*result_package).heart_rate_in_bpm = 0;
    (*result_package).spo2_in_percentage = 0;
    (*result_package).perfusion_index = 0;
    (*result_package).nibp_res.nibp_sys = 0;
    (*result_package).nibp_res.nibp_dia = 0;
    (*result_package).nibp_res.nibp_map = 0;
    (*result_package).nibp_res.nibp_pr = 0;
    (*result_package).temperature_in_celcius = 0;
    (*result_package).height_res.height_val = 0;
    (*result_package).height_res.height_unit = CM;
    (*result_package).weight_res.weight_val = 0;
    (*result_package).weight_res.weight_unit = KG;
    return result_package;
}

PUBLIC Results *print_result_package(Results *result_package) {
    printf("Full Name\t:\t%s\n", (*result_package).full_name);
    printf("HR in bpm\t:\t%d\n", (*result_package).heart_rate_in_bpm);
    printf("PR in bpm\t:\t%d\n", (*result_package).pulse_rate_in_bpm);
    printf("Nibp Sys\t:\t%d\n", (*result_package).nibp_res.nibp_sys);
    printf("Nibp Dia\t:\t%d\n", (*result_package).nibp_res.nibp_dia);
    printf("Nibp Map\t:\t%d\n", (*result_package).nibp_res.nibp_map);
    printf("Nibp Pr\t\t:\t%d\n", (*result_package).nibp_res.nibp_pr);
    printf("SpO2 in %%\t:\t%d\n", (*result_package).spo2_in_percentage);
    printf("PI non-unit\t:\t%d\n", (*result_package).perfusion_index);
    printf("RR in rpm\t:\t%d\n", (*result_package).rr_interval_in_bpm);
    printf("Weight in kg\t:\t%.1f\n", (*result_package).weight_res.weight_val);
    printf("Height in cm\t:\t%.1f\n", (*result_package).height_res.height_val);
    printf("Temp. in C\t:\t%.1f\n", (*result_package).temperature_in_celcius);
    return result_package;
}

PUBLIC Results *message_parser(char *message_addr, Results *result_package) {
    (void) get_weight_package(message_addr, result_package);
    (void) get_height_package(message_addr, result_package);
    (void) get_heart_rate(message_addr, result_package);
    (void) get_pulse_rate(message_addr, result_package);
    (void) get_nibp_sys(message_addr, result_package);
    (void) get_nibp_dia(message_addr, result_package);
    (void) get_nibp_map(message_addr, result_package);
    (void) get_nibp_pr(message_addr, result_package);
    (void) get_spo2(message_addr, result_package);
    (void) get_perfusion_index(message_addr, result_package);
    (void) get_rr_interval(message_addr, result_package);
    (void) get_temperature(message_addr, result_package);
    (void) get_full_name(message_addr, result_package);
    return result_package;
};



