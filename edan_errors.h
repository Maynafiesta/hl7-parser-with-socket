#ifndef EDAN_ERRORS_H
#define EDAN_ERRORS_H

typedef enum {
    SUCCESS_VAL = 0,
    INSUFFICIENT_MEMORY_ERROR = 100,
    CONNECTION_ERROR = 101,
    EMPTY_PACKAGE_ERROR = 102,
    NO_ROUTE_ERROR = 103,       // Can't find a valid device uses this ip address.
    ARG_NOT_FOUND_ERROR = 104,      // Can't find related argument in message buffer.
    INVALID_ARG_ERROR = 105,        // Invalid message that, can't find related value after header.
} Error_Types;


#endif // EDAN_ERRORS_H
