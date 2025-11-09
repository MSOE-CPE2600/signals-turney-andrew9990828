/**
 * Author: biebera@msoe.edu <Andrew Bieber>
 * Class: CPE 2600
 * Professor: Turney
 *
 * @file send_signal.c
 * @brief Sends SIGUSR1 with integer data using sigqueue().
 * 
 * Note: AI (GPT-5) was used to generate skeletons and Javadoc-style comments
 * to explain my work thoroughly. All code written and verified by Andrew Bieber.
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** @brief Generates a random integer and sends it with SIGUSR1. */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    pid_t pid = (pid_t)atoi(argv[1]);
    srand(time(NULL));
    int n = rand() % 100;

    printf("Sending SIGUSR1 with value %d to PID %d\n", n, pid);

    union sigval val;
    val.sival_int = n;
    if (sigqueue(pid, SIGUSR1, val) == -1)
        perror("sigqueue");

    return 0;
}
