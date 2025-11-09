/**
 * Author: biebera@msoe.edu <Andrew Bieber>
 * Class: CPE 2600
 * Professor: Turney
 *
 * @file signal_segfault.c
 * @brief Installs a handler for SIGSEGV (segmentation fault).
 * 
 * Note: AI (GPT-5) was used to generate skeletons and Javadoc-style comments
 * to explain my work thoroughly. All code written and verified by Andrew Bieber.
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>

/** @brief Handles segmentation faults and prints a message. */
void handle_segv(int sig) {
    printf("Caught SIGSEGV (%d): segmentation fault occurred!\n", sig);
}

int main(void) {
    signal(SIGSEGV, handle_segv);

    int *i = NULL; // null pointer
    printf("Dereferencing null pointer...\n");

    // This line triggers SIGSEGV repeatedly since the handler returns.
    printf("Value of i: %d\n", *i);

    return 0;
}
