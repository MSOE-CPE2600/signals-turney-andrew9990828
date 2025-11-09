/**
 * Author: biebera@msoe.edu <Andrew Bieber>
 * Class: CPE 2600
 * Professor: Turney
 *
 * @file recv_signal.c
 * @brief Uses sigaction() to receive SIGUSR1 with integer data via sigqueue().
 * 
 * Note: AI (GPT-5) was used to generate skeletons and Javadoc-style comments
 * to explain my work thoroughly. All code written and verified by Andrew Bieber.
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/** @brief Handler prints integer value and sender PID. */
void handler(int sig, siginfo_t *info, void *context) {
    (void)context;
    printf("Received SIGUSR1 (%d) with value %d from PID %d\n",
           sig, info->si_value.sival_int, info->si_pid);
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Receiver PID: %d\n", getpid());
    while (1) pause();
}
