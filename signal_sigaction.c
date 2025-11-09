/**
 * Author: biebera@msoe.edu <Andrew Bieber>
 * Class: CPE 2600
 * Professor: Turney
 *
 * @file signal_sigaction.c
 * @brief Registers SIGUSR1 handler using sigaction() to display sender PID.
 * 
 * Note: AI (GPT-5) was used to generate skeletons and Javadoc-style comments
 * to explain my work thoroughly. All code written and verified by Andrew Bieber.
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/** @brief Handler prints PID of process that sent SIGUSR1. */
void handler(int sig, siginfo_t *info, void *context) {
    (void)context; // unused
    printf("Received SIGUSR1 from PID %d\n", info->si_pid);
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("PID: %d waiting for SIGUSR1...\n", getpid());
    while (1) pause();
}
