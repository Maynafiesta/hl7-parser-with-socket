cmake_minimum_required(VERSION 3.23)
project(VitalSignMonitoring C)

set(CMAKE_C_STANDARD 99)

add_executable(VitalSignMonitoring
        main.c
        edan_utils.c    edan_utils.h)
