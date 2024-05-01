#ifndef ADD_H
#define ADD_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <limits.h>
#include "pthread.h"

uint64_t MultModulo(uint64_t a, uint64_t b, uint64_t mod);

#endif